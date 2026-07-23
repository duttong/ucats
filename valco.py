#! /usr/bin/env python

import re
import sys
import argparse
import logging
import serial
import threading
from time import sleep
from datetime import datetime

import autodetect

""" Driver for Valco VICI multi-position and two-position valves over RS-485.

    All valve objects on the same RS-485 bus should share a single
    serial.Serial instance (pass ser= at construction) so the class-level
    threading.Lock serialises every command/response transaction.  This
    prevents concurrent threads from interleaving commands on the shared bus.

    Typical usage in UCATS:
        v = Valco_Valve_Commands()          # autodetects port
        gsvs = {add: GSV(add, ser=v.ser) for add in config.gsv_adds}
        ssvs = {add: SSV(add, ser=v.ser) for add in config.ssv_adds}

    References:
        Two-position (GSV): https://www.vici.com/support/tn/tn413.pdf
        Multi-position (SSV): https://www.vici.com/support/tn/tn415.pdf

    Ported from FE3_acquisition/valco.py for UCATS (drivers/valve/valco.c
    confirms the same address+command+'\\n' protocol at 9600 baud, so this
    driver is used unmodified). GSD 260722
"""

VERSION = '2.0'

DELAYsend = 0.01


class Valco_Valve_Commands:
    """ Commands that work on all Valco valves.

        Not all of the commands are programmed.
        See https://www.vici.com/support/tn/tn413.pdf for two position valve
        See https://www.vici.com/support/tn/tn415.pdf for multi-position valve
        commands.

        Thread safety: all valve objects that share a physical RS-485 bus must be
        constructed with the same serial.Serial instance (pass ser=).  The class-level
        _lock then serialises every send/read transaction across threads, preventing
        concurrent commands from corrupting each other on the shared bus.
        Use cp(blocking=False) for background polling so that critical go commands
        are never delayed waiting for a position read to finish.
    """

    _lock = threading.Lock()   # one lock for the entire bus; shared by all instances

    def __init__(self, add=None, port=None, baud=9600, ser=None):
        """ If ser is provided the existing serial connection is reused and no
            new port is opened.  Otherwise the port is autodetected (port=None)
            or taken from the port argument. """
        self.baud = baud
        if ser is not None:
            self.ser = ser
            self.port = ser.port
        else:
            self.port = self.autodetect_serial('valco') if port is None else port
            self.ser = self.connect()
        self.add = add

    @staticmethod
    def autodetect_serial(device):
        auto = autodetect.SerialAutoDetect({device: None})
        if auto.devices[device] is None:
            raise RuntimeError(f'Could not determine valid serial port for {device}')
        print(f'Autodetecting port.\nUsing port: {auto.devices[device]} for {device}')
        logging.info('Autodetected %s serial port %s', device, auto.devices[device])
        return auto.devices[device]

    def connect(self):
        """ Open a new serial connection to the Valco valve bus. """
        try:
            ser = serial.Serial(self.port, timeout=0.05, baudrate=self.baud,
                bytesize=8, parity='N', stopbits=1)
        except serial.serialutil.SerialException as exc:
            raise serial.serialutil.SerialException(
                f'Could not connect to serial port: {self.port}'
            ) from exc
        return ser

    def send_cmd(self, add, cmd):
        """ Send a command to valco valve via serial port.
            Always called from within a _lock block (via cp(), id(), or with self._lock). """
        if add is None:
            cmd = f'{cmd}\n'
        else:
            cmd = f'{add}{cmd}\n'
        self.ser.reset_input_buffer()
        self.ser.write(cmd.encode())
        sleep(DELAYsend)

    def read_cmd(self, nbytes=100):
        """ Read a complete response from the bus.
            Must be called while holding _lock, immediately after send_cmd.
            Collects straggling bytes with an idle-poll loop. """
        r = bytearray(self.ser.read(nbytes))

        idle_polls = 0
        while len(r) < nbytes and idle_polls < 2:
            waiting = self.ser.in_waiting
            if waiting:
                r.extend(self.ser.read(min(waiting, nbytes - len(r))))
                idle_polls = 0
                continue
            idle_polls += 1
            sleep(DELAYsend)
        try:
            data = r.decode()
        except UnicodeDecodeError:
            data = ''
        return data

    def cp(self, add, blocking=True):
        """ Send a cp command and return the parsed position.
            blocking=False returns None immediately if the serial bus is busy. """
        if not self._lock.acquire(blocking=blocking):
            return None
        try:
            self.send_cmd(add, 'cp')
            r = self.read_cmd()
            return self.__parse_cp(r)
        finally:
            self._lock.release()

    def __parse_cp(self, response):
        # cp for GSV
        m = re.search(r'"(\w)"', response)
        if m is None:
            # search for ssv instead
            m = re.search(r'= (\d+)', response)
            if m is None:
                return None
        return m.group(1)

    def id(self):
        """ Return the valve's address/id as reported by the hardware. """
        with self._lock:
            self.send_cmd(self.add, 'id')
            r = self.read_cmd()
        m = re.search(r'= (\d)', r)
        if m is None:
            return None
        return m.group(1)


class GSV(Valco_Valve_Commands):
    """ Commands specific to 2 position valves, Gas Sample Valve.

        Position A = inject, position B = load -- true for most GSVs, but
        not all: flight/src/uav.cmd's grammar has a separate
        &GSVVALVEPOS_Inv rule used only for UCATS's channel 3 GSV, where
        Inject maps to position B and Load to position A (confirmed real
        plumbing difference, not a typo -- drivers/valve/valco.c's
        switch_valve() maps position 1/2 to GOA/GOB identically for every
        valve ID, so the inversion is channel-3-specific wiring, not a
        driver-level quirk). Pass inverted=True for that valve.
        Tracks last known position in self.pos and is tolerant of occasional
        bad cp reads (one automatic retry on garbled data).

        Pass ser= (a shared serial.Serial instance) so this valve shares the
        bus lock with all other valve objects.
    """

    def __init__(self, add, port=None, baud=9600, ser=None, inverted=False):
        super().__init__(port=port, baud=baud, ser=ser)
        self.add = add
        self.pos = 'Unknown'
        self.verbose = True
        self.inverted = inverted

    def _go_position(self, cmd, pos):
        """ Send a two-position move command twice (double-tap for reliability). """
        with self._lock:
            self.send_cmd(self.add, cmd)
            sleep(DELAYsend)
            self.send_cmd(self.add, cmd)
        self.pos = pos

    def cp(self, blocking=True):
        """ Return current valve position (A or B), with one retry on failure.

        blocking=False returns self.pos immediately if the serial bus is busy. """
        new_pos = Valco_Valve_Commands.cp(self, self.add, blocking=blocking)
        logging.debug(f'GSV{self.add} cp first read: {new_pos!r}')

        if new_pos is None and not blocking:
            return self.pos

        if new_pos not in ('A', 'B'):
            logging.debug(f'GSV{self.add} cp read invalid ({new_pos!r}); retrying...')
            sleep(DELAYsend)

            new_pos_retry = Valco_Valve_Commands.cp(self, self.add)
            logging.debug(f'GSV{self.add} cp second read: {new_pos_retry!r}')

            if new_pos_retry in ('A', 'B'):
                self.pos = new_pos_retry
                return self.pos

            logging.error(
                f'GSV{self.add} cp failed twice; keeping last known position = {self.pos!r}'
            )
            return self.pos

        self.pos = new_pos
        return self.pos

    def tog(self):
        """ Valco 'to' command.  Toggles position. """
        with self._lock:
            self.send_cmd(self.add, 'to')

    def goa(self):
        """ Go to position A """
        self._go_position('goa', 'A')

    def gob(self):
        """ Go to position B """
        self._go_position('gob', 'B')

    def load(self):
        """ 'load' command is position B (position A if inverted) """
        self.goa() if self.inverted else self.gob()
        if self.verbose:
            print(f'{datetime.now()} load {self.add}')
            logging.info(f'load {self.add}')

    def inject(self):
        """ 'inject' command is position A (position B if inverted) """
        self.gob() if self.inverted else self.goa()
        if self.verbose:
            print(f'{datetime.now()} inject {self.add}')
            logging.info(f'inject {self.add}')

    def pos_txt(self):
        """ Returns the valve position as load/inject instead of A/B """
        if self.pos not in ('A', 'B'):
            self.cp()
        inject_pos = 'B' if self.inverted else 'A'
        load_pos = 'A' if self.inverted else 'B'
        if self.pos == inject_pos:
            return 'inject'
        elif self.pos == load_pos:
            return 'load'
        else:
            logging.warning(f'GSV{self.add} pos_txt unable to map position; self.pos={self.pos!r}')
            return f'unknown (raw={self.pos!r})'

    def realign(self):
        """ Re-aligns a valve """
        with self._lock:
            self.send_cmd(self.add, 'in')   # initialize
        sleep(DELAYsend)    # settle after init before toggling; intentionally outside lock
        for itr in range(6):
            self.tog()
            sleep(2)    # seconds


class SSV(Valco_Valve_Commands):
    """ Commands specific to a multi-position valve, Stream Selection Valve.

        Number of ports is queried from the hardware at construction (np command).
        Current position is tracked in self.pos (integer, 1-based); -1 until first read.

        Pass ser= (a shared serial.Serial instance) so this valve shares the
        bus lock with all other valve objects.
    """

    def __init__(self, add, port=None, baud=9600, ser=None):
        super().__init__(port=port, baud=baud, ser=ser)
        self.add = add
        self.pos = -1
        self.numports = self.np()    # num ports on the valve
        self.verbose = True

    def np(self):
        """ Returns number of positions a SSV has. """
        with self._lock:
            self.send_cmd(self.add, 'np')
            r = self.read_cmd()
        m = re.search(r'= (\d+)', r)
        if m is None:
            logging.error("Can't determine number of ports on SSV. NP command failed.")
            return 0
        return int(m.group(1))

    def cp(self, blocking=True):
        """ Current valve position.
            blocking=False returns self.pos immediately if the serial bus is busy. """
        pos = Valco_Valve_Commands.cp(self, self.add, blocking=blocking)
        logging.debug(f'SSV cp is {pos}')
        if pos is None:
            if not blocking:
                return self.pos
            logging.warning(f'SSV current position is None, keeping old cp = {self.pos}')
            return self.pos
        self.pos = int(pos)
        return self.pos

    def go(self, position):
        with self._lock:
            self.send_cmd(self.add, f'go={position}')
        self.pos = int(position)
        if self.verbose:
            print(f'{datetime.now()} SSV{self.add} to {position}')
            logging.info(f'SSV{self.add} to {position}')
        return self.pos

    def step(self):
        """ Step valve one position forward. """
        cur = self.cp()
        if cur is None:
            logging.error(f'Unknown SSV position, address = {self.add}')
            return
        new = int(cur) + 1
        new = 1 if new > self.numports else new
        self.go(new)

    def home(self):
        """ Return valve to position 1 dubbed 'home' """
        self.go(1)


class Valves(Valco_Valve_Commands):
    """ Function that apply to many valves. """

    def __init__(self, port=None):
        super().__init__(port=port)
        self.positions = dict()

    def scan(self, adds):
        """ Scans a list of addresses for valves, returns positions """
        loc = [self.cp(id) for id in adds]
        self.positions = dict(zip(adds, loc))
        return self.positions


if __name__ == '__main__':
    try:
        opt = argparse.ArgumentParser(
            description='Valco valve driver.'
        )
        opt.add_argument('-c', action='store',
            dest='command', help='command string to send to address')
        opt.add_argument('--align', action='store',
            dest='add', help='align the valve position')
        opt.add_argument('--scan', action='store_true',
            dest='scan', help='scan for valves')
        opt.add_argument('-p', action='store',
            dest='port', help='serial port to use (default is autodetect)')

        options = opt.parse_args()

        if options.command:
            v = Valco_Valve_Commands(port=options.port)
            v.send_cmd(None, options.command)
            print(v.read_cmd(2048))

        if options.add:
            v = GSV(options.add, port=options.port)
            v.realign()
            quit()

        if options.scan:
            print('Scanning for valves:')
            t = Valves(port=options.port)
            print(t.scan(range(10)))
            print('Valve addresses with their current positions.')
            quit()
    except (RuntimeError, serial.serialutil.SerialException) as exc:
        sys.stderr.write(f'{exc}\n')
        sys.exit(1)
