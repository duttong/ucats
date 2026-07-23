#! /usr/bin/env python

VERSION = '0.1'
""" UCATS instrument orchestrator -- replaces the QNX PANTHER flight
    software's main loop (flight/src/uav.tma and gc.tmc) with a standalone
    Python acquisition system.

    Modeled on FE3_acquisition's Instrument_FE3 (fe3.py) for the GC/valve/
    ITX-output shape, and on ucats-b's per-tick collect/merge/telemetry loop
    (instrument.py) for engineering data and telemetry. Two differences from
    both:

    - Detectors are custom smart electrometers (smart.py), not a commercial
      GC streaming continuously -- see smart.py's GCChannels for the once-
      per-second polling model that replaces FE3's gc7890.py socket threads.
    - There is no fixed SSV sequence string like FE3. flight/src/uav.tma's
      real state machine just alternates "Sample Air"/"Sample Cal" on an
      air:cal injection counter (see setup.yaml's injection_ratio). It also
      has no software-visible chromatogram duration: the legacy GCstate that
      drove Injecting1/Injection/Injecting2 was read directly off a solenoid
      driver board register (flight/src/basecol.tmc's GCstatePtr/SOLDRV_A),
      not derived in software. This orchestrator now owns that timing
      itself via setup.yaml's chromduration, since the hardware register
      that used to own it isn't part of what's being ported. GSD 260722
"""

import os
import sys
import logging
import logging.handlers
from argparse import ArgumentParser
from pathlib import Path
from time import time, gmtime, localtime, sleep
from datetime import datetime
import pandas as pd
import yaml

import valco
import omega
import adr2000
import smart
from scheduler import Scheduler
from telemetry import Telemetry

logger = logging.getLogger(__name__)

INSTRUMENT_CODE = 'uca'    # station code used in ITX filenames -- TODO: confirm real HATS code
DETECTOR_HZ = 16            # smart electrometer points per second (MAXPOINTS in smart.h)


def setup_logging(log_dir, verbose=False):
    """ Configure root logger: rotating file at <log_dir>/ucats.log + stdout. """
    os.makedirs(log_dir, exist_ok=True)

    root = logging.getLogger()
    root.setLevel(logging.DEBUG if verbose else logging.INFO)
    for h in list(root.handlers):
        root.removeHandler(h)

    fmt = logging.Formatter('%(asctime)s [%(levelname)s] %(name)s: %(message)s')

    file_handler = logging.handlers.RotatingFileHandler(
        os.path.join(log_dir, 'ucats.log'), maxBytes=20 * 1024 * 1024, backupCount=5)
    file_handler.setFormatter(fmt)
    root.addHandler(file_handler)

    stream_handler = logging.StreamHandler(sys.stdout)
    stream_handler.setFormatter(fmt)
    root.addHandler(stream_handler)


class Instrument_UCATS:
    """ Orchestrates the UCATS 3-channel GC: valve/injection sequencing,
        electrometer polling + ITX chromatogram output, Omega temperature
        monitoring, ADR2000 solenoid/analog I/O, engineering data logging,
        and telemetry. """

    def __init__(self, config_file='config.yaml', setup_file='setup.yaml', verbose=False):
        self.config_file = config_file
        self.config = self._load_yaml(config_file)
        self.setup = self._load_yaml(setup_file)
        self.verbose = verbose
        self.mode = self.config.get('mode', 'flight')     # 'flight' | 'calibration' -- see config.yaml

        setup_logging(self.config['paths']['log_dir'], verbose)

        self.scheduler = Scheduler()
        self.telemetry = (
            Telemetry(config_file) if self.config.get('telemetry', {}).get('enable') else None
        )

        self.gc_state = 'idle'     # 'idle' | 'air' | 'cal'
        self.air_count = 0
        self.cal_count = 0
        # ch1's column takes two 75s cycles (150s) to separate, so its GSV
        # program alternates 'A'/'B' each cycle -- see setup.yaml's
        # gsv_phase_channels, and inject_all_channels()/
        # _schedule_injection_timing() below. Other channels are
        # phase-invariant (same program every cycle).
        self.gsv_phase = 'A'
        self.injection_t0 = None
        self.injection_ssv_pos = None
        self.eng_df = pd.DataFrame()
        self._adr_started = False

        self._connect_hardware()

    # ------------------------------------------------------------------
    # setup
    # ------------------------------------------------------------------
    @staticmethod
    def _load_yaml(path):
        with open(path) as f:
            return yaml.safe_load(f)

    def _connect_hardware(self):
        devices = self.config['devices']

        logger.info('Connecting to Valco valve bus')
        self.valco_bus = valco.Valco_Valve_Commands(port=devices['valco'].get('port'))
        self.gsvs = {
            ch['name']: valco.GSV(ch['gsv_address'], ser=self.valco_bus.ser)
            for ch in self.config['gc_channels']
        }

        # Air/cal switching hardware depends on mode (config.yaml's 'mode'):
        # flight uses the ADR2000 digital 'ssv' solenoid; calibration uses an
        # external multi-position Valco SSV, only physically present in the
        # lab. See select_air_cal()/set_mode().
        if self.mode == 'calibration':
            logger.info('Calibration mode: connecting external Valco SSV')
            self.cal_ssv = valco.SSV(self.config['ssv']['cal_add'], ser=self.valco_bus.ser)
        else:
            logger.info('Flight mode: air/cal switching via ADR2000 digital ssv solenoid')
            self.cal_ssv = None

        logger.info('Connecting to Omega temperature controllers')
        self.omegas = omega.Omega_PlatinumSeries(port=devices['omega'].get('port'))
        self.omega_zone_adds = {
            name: add for name, add in devices['omega'].get('zones', {}).items() if add is not None
        }

        logger.info('Connecting to ADR2000 board(s)')
        self.adr = adr2000.Driver.from_config(self.config_file)

        logger.info('Connecting to smart electrometers')
        self.elec = smart.SmartElectrometer(devices['smart']['port'])
        self.gc_channels = smart.GCChannels(
            self.elec,
            [(ch['name'], ch['electrometer_address']) for ch in self.config['gc_channels']],
        )

    # ------------------------------------------------------------------
    # valve control (fe3.py:124-144)
    # ------------------------------------------------------------------
    def inject_all_channels(self):
        """ Injects every channel's GSV, except a channel listed in
            setup.yaml's gsv_phase_channels whose current self.gsv_phase
            entry has inject: false -- that channel stays in Load instead
            (e.g. ch1 on a 'B' cycle, continuing separation from the prior
            'A' cycle's injection rather than injecting again). """
        phase_channels = self.setup.get('gsv_phase_channels', {})
        for name, gsv in self.gsvs.items():
            phase_cfg = phase_channels.get(name, {}).get(self.gsv_phase, {})
            if phase_cfg.get('inject', True):
                gsv.inject()
            else:
                gsv.load()

    def load_all_channels(self):
        for gsv in self.gsvs.values():
            gsv.load()

    def valves_cp(self, blocking=False):
        """ Non-blocking snapshot of every channel GSV's last known position. """
        return {name: gsv.cp(blocking=blocking) for name, gsv in self.gsvs.items()}

    # ------------------------------------------------------------------
    # air/cal switching -- flight uses the ADR2000 digital 'ssv' solenoid,
    # calibration uses an external multi-position Valco SSV. See
    # config.yaml's 'mode' setting and _connect_hardware().
    # ------------------------------------------------------------------
    def select_air_cal(self, inj_type):
        if self.mode == 'calibration':
            port = 1 if inj_type == 'cal' else 2   # TODO: confirm real cal/ambient port numbers
            self.cal_ssv.go(port)
        else:
            state = 'high' if inj_type == 'cal' else 'low'    # TODO: confirm real solenoid polarity
            self.adr.job.put(('ssv', state))

    def current_selpos(self, inj_type):
        """ Value used for the ITX filename / eng data: the Valco SSV's
            numeric position in calibration mode, or the air/cal label
            itself in flight mode (there's no numeric position to read). """
        return self.cal_ssv.pos if self.mode == 'calibration' else inj_type

    def set_mode(self, mode):
        """ Switch air/cal hardware at runtime -- called by the GUI's
            calibration-mode toggle. Connects the external Valco SSV lazily,
            the first time calibration mode is entered. """
        if mode == self.mode:
            return
        if mode == 'calibration' and self.cal_ssv is None:
            logger.info('Switching to calibration mode: connecting external Valco SSV')
            self.cal_ssv = valco.SSV(self.config['ssv']['cal_add'], ser=self.valco_bus.ser)
        self.mode = mode
        logger.info('Air/cal hardware mode set to %s', mode)

    # ------------------------------------------------------------------
    # injection sequencing -- flight/src/uav.tma's AIRnext/CALnext/SSVtable,
    # an air:cal counter ratio rather than FE3's fixed SSV sequence string.
    # ------------------------------------------------------------------
    def next_injection_type(self):
        ratio = self.setup['injection_ratio']
        return 'cal' if self.cal_count < ratio['cal_injections'] else 'air'

    def start_injection(self):
        inj_type = self.next_injection_type()
        ratio = self.setup['injection_ratio']
        logger.info('Starting %s injection (mode=%s)', inj_type, self.mode)

        self.select_air_cal(inj_type)

        if inj_type == 'cal':
            self.cal_count += 1
            # stays >= cal_injections ("done") until the air count wraps below resets it --
            # mirrors uav.tma's CALnext, which sets CalCount to a sentinel (500) rather than 0
            self.cal_count = min(self.cal_count, ratio['cal_injections'])
        else:
            self.air_count += 1
            if self.air_count >= ratio['air_injections']:
                self.air_count = 0
                self.cal_count = 0     # cal due again -- mirrors uav.tma's AIRnext wraparound

        self.gc_state = inj_type
        self.gc_channels.reset()
        self.inject_all_channels()
        self.injection_t0 = time()
        self.injection_ssv_pos = self.current_selpos(inj_type)

        self._schedule_injection_timing()
        self.scheduler.add_task(
            delay=self.setup['chromduration'], interval=None,
            function=self.finish_injection, name='finish_injection',
        )

        # Flip for next cycle: flight/src/uav.sol's chrom140s_A/chrom140s_B
        # run back to back, alternating -- see setup.yaml's chromduration note.
        self.gsv_phase = 'B' if self.gsv_phase == 'A' else 'A'

    def _phase_events(self, events):
        """ events is either a flat [time, value] list (same every cycle)
            or a {'A': [...], 'B': [...]} dict for a channel whose program
            depends on self.gsv_phase (currently just ch1 -- see setup.yaml's
            flows/aux_pressures). Returns the list to use for this cycle. """
        return events.get(self.gsv_phase, []) if isinstance(events, dict) else events

    def _schedule_injection_timing(self):
        """ Schedule this cycle's GSV Inject->Load switches, sample-loop
            solenoid events, and flow/pressure setpoint programs, all timed
            from flight/src/uav.sol's chrom140s_A/chrom140s_B (see
            setup.yaml's backflush_times/gsv_phase_channels/solenoids/flows/
            aux_pressures -- every channel is already back in the load
            position, from its own switch, well before chromduration
            elapses). """
        for name, t in self.setup.get('backflush_times', {}).items():
            if name in self.gsvs:
                self.scheduler.add_task(
                    delay=t, interval=None,
                    function=self.gsvs[name].load, name=f'backflush_{name}')

        for name, phases in self.setup.get('gsv_phase_channels', {}).items():
            load_at = phases.get(self.gsv_phase, {}).get('load_at')
            if name in self.gsvs and load_at is not None:
                self.scheduler.add_task(
                    delay=load_at, interval=None,
                    function=self.gsvs[name].load, name=f'backflush_{name}')

        for name, events in self.setup.get('solenoids', {}).items():
            for t, state in events:
                self._schedule_adr_job(name, t, 'high' if state else 'low', f'solenoid_{name}_{t}')

        for group, dac_prefix in (('main', 'main'), ('backflush', 'backflush')):
            for ch, events in self.setup.get('flows', {}).get(group, {}).items():
                dac_name = f'{dac_prefix}_{ch}'
                for t, setpoint in self._phase_events(events):
                    self._schedule_adr_job(dac_name, t, setpoint, f'{dac_name}_{t}')

        for ch, events in self.setup.get('aux_pressures', {}).items():
            dac_name = f'bfpres_{ch}'
            for t, setpoint in self._phase_events(events):
                self._schedule_adr_job(dac_name, t, setpoint, f'{dac_name}_{t}')

    def _schedule_adr_job(self, var, delay, value, name):
        """ Queue an adr2000.py Driver dig/dac command (var, value) via
            self.adr.job, delay seconds into the current injection. """
        self.scheduler.add_task(
            delay=delay, interval=None,
            function=self.adr.job.put, args=((var, value),), name=name)

    def finish_injection(self):
        self.write_itx()
        self.gc_state = 'idle'
        self.start_injection()

    # ------------------------------------------------------------------
    # ITX chromatogram output, modeled on FE3's GC7890.resp2itx (gc7890.py:382)
    # ------------------------------------------------------------------
    def write_itx(self):
        resp_data = {name: ch.snapshot() for name, ch in self.gc_channels.channels.items()}
        if not any(resp_data.values()):
            logger.warning('write_itx: no detector data available, skipping')
            return

        itxp = Path(self.config['paths']['itx_dir'])
        itxp.mkdir(parents=True, exist_ok=True)

        t0 = self.injection_t0
        tinj = gmtime(t0)
        tinjl = localtime(t0)      # local time for chrom numbering (avoids midnight rollover)
        selpos = self.injection_ssv_pos

        itx = f'{tinj.tm_year:04}{INSTRUMENT_CODE}{tinj.tm_yday:03}{tinj.tm_hour:02}{tinj.tm_min:02}.{selpos}.itx'
        logger.info('Writing ITX file %s channels=%s', itx, sorted(resp_data.keys()))

        with open(itxp / itx, 'w') as f:
            f.write('IGOR\n')
            counter = f'{tinjl.tm_hour:03}{tinjl.tm_min:02}'
            sorted_keys = sorted(resp_data.keys())
            wave_names = [f'chr_{ch}_{counter}' for ch in sorted_keys]
            chs = ', '.join(wave_names)
            f.write('WAVES ' + chs + '\nBEGIN\n')

            # Not all channels necessarily have the same number of points; use
            # the shortest to avoid index errors. Values must be integer for GCwerks.
            min_n = min(len(resp_data[ch]) for ch in sorted_keys)
            mult = 1000
            for pt in range(min_n):
                s = ''.join(f'{round(resp_data[ch][pt] * mult)} ' for ch in sorted_keys)
                f.write(s + '\n')
            f.write('END\n')

            timestr = f'{tinj.tm_hour:02}:{tinj.tm_min:02}:{tinj.tm_sec:02}'
            datestr = f'{tinj.tm_mon:02}-{tinj.tm_mday:02}-{tinj.tm_year:04}'
            for ch in wave_names:
                note = f'X note {ch}, " 1; 0; {timestr}; {datestr}; {selpos}; {INSTRUMENT_CODE};"'
                f.write(note + '\n')

            hz = 1.0 / DETECTOR_HZ
            f.write(f'X SetScale /P x, 0, {hz:0.4}, {chs}\n')

    # ------------------------------------------------------------------
    # engineering data + telemetry, modeled on ucats-b's collect_data tick
    # (instrument.py:197-249)
    # ------------------------------------------------------------------
    def eng_row(self):
        row = {'datetime': datetime.now(), 'gc_state': self.gc_state, 'air_cal_mode': self.mode}
        if self.cal_ssv is not None:
            row['ssv_cal_pos'] = self.cal_ssv.cp(blocking=False)

        for name, pos in self.valves_cp(blocking=False).items():
            row[f'gsv_{name}'] = {'A': 'inject', 'B': 'load'}.get(pos, pos)

        if self.omega_zone_adds:
            self.omegas.scan(list(self.omega_zone_adds.values()))
        for name, add in self.omega_zone_adds.items():
            row[f'omega_{name}'] = self.omegas.temps.get(add, [None, None])[1]

        for name, ch in self.gc_channels.channels.items():
            row[f'ecdA_{name}'] = ch.last_mean()

        row.update(self.adr.data)      # flight mode's 'ssv' solenoid readback lands here

        return row

    def collect_eng(self):
        row = self.eng_row()
        self.eng_df = pd.concat([self.eng_df, pd.DataFrame([row])], ignore_index=True)

        eng_dir = Path(self.config['paths']['eng_dir'])
        eng_dir.mkdir(parents=True, exist_ok=True)
        eng_file = eng_dir / f'eng_{datetime.now():%Y%m%d}.csv'

        last = self.eng_df.tail(1)
        last.to_csv(eng_file, mode='a', index=False, header=not eng_file.exists())

        if self.telemetry is not None:
            self.telemetry.send_data(last)

        self.eng_df = self.eng_df.tail(100)    # cap memory footprint

    # ------------------------------------------------------------------
    # start/stop
    # ------------------------------------------------------------------
    def start(self):
        logger.info('Starting UCATS acquisition')
        if not self._adr_started:
            # adr2000.py's Driver is a Thread and can only be .start()ed once;
            # shutdown() doesn't kill it (it has no clean restart path), so a
            # GUI start/stop/start cycle must not call this twice.
            self.adr.start()
            self._adr_started = True
        self.scheduler.add_task(
            delay=0, interval=1.0, function=self.gc_channels.poll, name='poll_electrometers')
        self.scheduler.add_task(
            delay=0, interval=1.0, function=self.collect_eng, name='collect_eng')
        self.scheduler.start()
        self.start_injection()

    def shutdown(self):
        logger.info('Shutting down UCATS acquisition')
        self.scheduler.stop()


def main():
    parser = ArgumentParser(description='UCATS instrument acquisition.')
    parser.add_argument('--config', default='config.yaml', help='hardware/paths config file')
    parser.add_argument('--setup', default='setup.yaml', help='run parameters file')
    parser.add_argument('-v', '--verbose', action='store_true', help='enable debug logging')
    parser.add_argument('--headless', action='store_true',
        help='run without the operator GUI (starts acquisition immediately)')
    args = parser.parse_args()

    instrument = Instrument_UCATS(config_file=args.config, setup_file=args.setup, verbose=args.verbose)

    if args.headless:
        instrument.start()
        try:
            while True:
                sleep(1)
        except KeyboardInterrupt:
            instrument.shutdown()
        return

    import sys
    from PyQt5.QtWidgets import QApplication
    from display import UCATSDisplay

    app = QApplication(sys.argv)
    window = UCATSDisplay(instrument)
    window.show()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
