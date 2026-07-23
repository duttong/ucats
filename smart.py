#! /usr/bin/env python

VERSION = '1.0'
""" Python3 driver for the NOAA/GML 'Smart' Electrometer.
    Translated from C source (drivers/smart/smart.c). GSD 220722

    The original C driver ran as a QNX message-passing server for PANTHER.
    That IPC layer doesn't translate to a standalone script, so this version
    keeps the serial protocol and command-line behavior (-p/-b/-d/-R/-A/-h from
    init_opt()/usage()) and replaces the QNX server loop with a simple polling
    loop over the addresses listed in hardware.cfg.
"""

import sys
from time import sleep
from math import floor
import serial

STX = chr(2)
ETX = chr(3)
NIBBLE = '0123456789ABCDEF'

BAUD = 9600
RCV_MSG_SIZE = 150
RAIL = 200000.0
BIT24 = 16777216.0
MAXDET = 8              # maximum number of detectors (addresses 0 to 7)
MAXPOINTS = 16           # maximum number of data points received from electrometer
NOELECDATA = -999
HARDWARE_CFG = 'hardware.cfg'


class SmartElectrometer:
    """ Driver for one or more NOAA/GML Smart Electrometers on a shared serial bus.

        port is the serial device the electrometers are connected to.
        hardware_cfg, if given, is parsed for 'smart: address: N' lines that
        list the valid electrometer addresses (0-7) to scan/reset.
    """

    def __init__(self, port, hardware_cfg=None):
        self.port = port
        self.valid = [False] * MAXDET
        self.chrom = [{'numpnts': 0, 'resp': [NOELECDATA] * MAXPOINTS} for _ in range(MAXDET)]

        try:
            self.ser = serial.Serial(self.port, timeout=2, baudrate=BAUD,
                bytesize=8, parity='N', stopbits=1)
        except serial.serialutil.SerialException:
            sys.stderr.write(f"smart: Can't connect to serial port: {self.port}\n")
            quit()

        if hardware_cfg:
            self.load_config(hardware_cfg)

    def load_config(self, path):
        """ Parse hardware.cfg for 'smart: address: N' lines to find valid electrometer addresses. """
        try:
            with open(path) as f:
                tokens = f.read().lower().split()
        except OSError:
            sys.stderr.write(f'smart: Could not open {path}\n')
            return

        for i, tok in enumerate(tokens):
            if tok == 'smart:' and tokens[i + 1:i + 2] == ['address:']:
                add = int(tokens[i + 2])
                if 0 <= add < MAXDET:
                    self.valid[add] = True
                    print(f'hardware.cfg: smart valid address {add} configured.')

    def send_command(self, detnum, cmd):
        """ Build and send a checksummed command frame to electrometer detnum.

            cmd[0] == '2' is the PROGDAC command and carries extra data bytes;
            every other command is a single character (only cmd[0] is used).
        """
        if cmd[0] == '2':
            trans = f'LD{detnum:x}{cmd}'
        else:
            trans = f'LD{detnum:x}{cmd[0]}'

        checksum = sum(ord(c) for c in trans[1:])
        chksumH = (checksum & 0xF0) >> 4
        chksumL = checksum & 0x0F

        frame = f'{STX}{trans}{chksumH:X}{chksumL:X}{ETX}'

        self.ser.reset_input_buffer()
        self.ser.reset_output_buffer()
        n = self.ser.write(frame.encode('latin-1'))
        self.ser.flush()
        if n != len(frame):
            sys.stderr.write('send_command: Failed to send all data to port.\n')

    def flush_chrom(self, detnum):
        self.chrom[detnum] = {'numpnts': 0, 'resp': [NOELECDATA] * MAXPOINTS}

    def parse_chrom(self, buffer):
        """ Parse a response frame received from an electrometer into self.chrom. """
        if not buffer or buffer[0] != STX:
            return

        detnum = ord(buffer[3]) - ord('0')
        numchars = int(buffer[4:6], 16)

        checksum = sum(ord(c) for c in buffer[1:6 + numchars])
        chksmH = NIBBLE[(checksum & 0xF0) >> 4]
        chksmL = NIBBLE[checksum & 0x0F]

        if buffer[6 + numchars] == chksmH and buffer[7 + numchars] == chksmL:
            resp = [int(floor(int(buffer[i:i + 6], 16) * RAIL / BIT24))
                for i in range(6, numchars + 1, 6)]
            self.chrom[detnum]['resp'][:len(resp)] = resp
            self.chrom[detnum]['numpnts'] = len(resp)

    def read_electrometer(self, det_num):
        """ Request and parse a data snapshot from electrometer det_num. """
        self.send_command(det_num, '4')
        self.flush_chrom(det_num)

        raw = self.ser.read(RCV_MSG_SIZE)
        if raw:
            self.parse_chrom(raw.decode('latin-1'))

        return self.chrom[det_num]['numpnts']

    def send_reset(self, det):
        self.send_command(det, '0')
        sleep(0.1)

    def send_ADCresets(self, det):
        self.send_command(det, '7')
        sleep(1)
        self.send_command(det, '7')
        sleep(1)

    def change_dac(self, det, setpoint):
        """ Set the electrometer bias DAC. setpoint is clamped to 0-255. """
        setpoint = max(0, min(255, setpoint))
        self.send_command(det, f'2{setpoint:02X}')

    def init_smart(self):
        """ Reset then ADC-reset every electrometer address marked valid in hardware.cfg. """
        for det, ok in enumerate(self.valid):
            if ok:
                print(f'Sending reset to electrometer {det}')
                self.send_reset(det)

        for det, ok in enumerate(self.valid):
            if ok:
                print(f'Sending ADC reset to electrometer {det}')
                self.send_ADCresets(det)


class GCChannel:
    """ One GC channel's electrometer data, accumulated across repeated
        1 Hz polls into the running chromatogram for the current injection.

        The smart electrometer has no continuous data stream: each poll
        (read_electrometer) returns up to MAXPOINTS sub-second readings
        buffered since the previous poll (~16 Hz, see GC_Ctr_Pull in
        flight/gc.tmc). The chromatogram trace is the concatenation of
        these once-per-second snapshots over the run.
    """

    def __init__(self, name, address):
        self.name = name
        self.address = address
        self.resp = []
        self.last_points = []      # points from the most recent poll only

    def reset(self):
        """ Start a new chromatogram: clear the accumulated buffer. """
        self.resp = []
        self.last_points = []

    def append(self, points):
        self.resp.extend(points)
        self.last_points = points

    def snapshot(self):
        """ Return a copy of the points accumulated so far. """
        return list(self.resp)

    def last_mean(self):
        """ Mean of the most recent poll's points -- the 1 Hz running
            average uav.tma computes as ecdA_CH1/ecdA_CH2 (see gc.tmc's
            DetAvgCt1/ecd_sum1), not a whole-injection average. """
        if not self.last_points:
            return None
        return sum(self.last_points) / len(self.last_points)


class GCChannels:
    """ Polls a set of GC channels once per second, each backed by a smart
        electrometer address on the same shared bus, and accumulates every
        channel's points into its own GCChannel buffer. """

    def __init__(self, elec, channels):
        """ elec: a SmartElectrometer instance (owns the serial connection).
            channels: iterable of (name, address) pairs, e.g. from
            config.yaml's gc_channels list. """
        self.elec = elec
        self.channels = {name: GCChannel(name, address) for name, address in channels}

    def reset(self, name=None):
        """ Reset one channel's buffer, or all channels if name is None. """
        targets = [self.channels[name]] if name else self.channels.values()
        for ch in targets:
            ch.reset()

    def poll(self):
        """ Poll every channel's electrometer once and append any new points. """
        for ch in self.channels.values():
            num = self.elec.read_electrometer(ch.address)
            if num > 0:
                ch.append(self.elec.chrom[ch.address]['resp'][:num])

    def snapshot(self, name):
        return self.channels[name].snapshot()


EXAMPLES = """
examples:
  Run as smart driver for PANTHER on default serial port /dev/ser1
      smart.py

  Run as smart driver for PANTHER on serial port /dev/ser3
      smart.py -p /dev/ser3

  Display snapshot of electrometer 2's data from port /dev/ser2 and quit.
      smart.py -p /dev/ser2 -d 2

  Set bias to 230 on electrometer 2 connected to port /dev/ser2 and quit.
      smart.py -p /dev/ser2 -b 230 -d 2

  Send reset to electrometer 3 on /dev/ser1
      smart.py -R 3

  Send 2 ADC resets to electrometer 4 on /dev/ser2
      smart.py -p /dev/ser2 -A 4
"""


if __name__ == '__main__':

    import argparse

    opt = argparse.ArgumentParser(
        description='Software for the NOAA/GML Smart Electrometer.',
        epilog=EXAMPLES,
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    opt.add_argument('-p', action='store', dest='port', default='/dev/ser1',
        help='serial port to use (default is /dev/ser1)')
    opt.add_argument('-d', action='store', dest='det', type=int, metavar='DET',
        help='electrometer address to query, or to set bias on if -b is given')
    opt.add_argument('-b', action='store', dest='bias', type=int, metavar='BIAS',
        help='bias setpoint (0-255) to send to the electrometer given by -d')
    opt.add_argument('-R', action='store', dest='reset_det', type=int, metavar='DET',
        help='send reset to electrometer address DET, then quit')
    opt.add_argument('-A', action='store', dest='adc_det', type=int, metavar='DET',
        help='send 2 ADC resets to electrometer address DET, then quit')
    opt.add_argument('-c', action='store', dest='command', metavar='CMD',
        help='raw command string to send to the electrometer given by -d')

    options = opt.parse_args()

    if options.reset_det is not None:
        elec = SmartElectrometer(options.port)
        elec.send_reset(options.reset_det)
        quit()

    if options.adc_det is not None:
        elec = SmartElectrometer(options.port)
        print('Sending ADC resets -- this will take a few seconds.')
        elec.send_ADCresets(options.adc_det)
        quit()

    if options.det is not None:
        elec = SmartElectrometer(options.port)

        if options.command:
            elec.send_command(options.det, options.command)
            quit()

        if options.bias is not None:
            elec.change_dac(options.det, options.bias)
            print(f'Detector {options.det} BIAS changed to {options.bias}')
        else:
            num = elec.read_electrometer(options.det)
            if num > 0:
                pts = ','.join(str(p) for p in elec.chrom[options.det]['resp'][:num])
                print(f'\nDetector {options.det} response ( {num} data points follow )\n  {pts}\n')
            else:
                print(f'\nNo response from detector {options.det}')
        quit()

    elec = SmartElectrometer(options.port, hardware_cfg=HARDWARE_CFG)
    elec.init_smart()

    print('smart: running as electrometer driver, Ctrl-C to quit.')
    try:
        while True:
            for det, ok in enumerate(elec.valid):
                if ok:
                    num = elec.read_electrometer(det)
                    if num > 0:
                        pts = ','.join(str(p) for p in elec.chrom[det]['resp'][:num])
                        print(f'detector {det}: {pts}')
            sleep(1)
    except KeyboardInterrupt:
        print('\nsmart: quitting')
