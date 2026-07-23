#! /usr/bin/env python

import argparse
import serial
import sys
from time import sleep, monotonic
import logging
import termios
import yaml 

import autodetect

VERSION = '2.0'         # verison 2 is for Platinum series class of controllers


class Omega_PlatinumSeries:
    """ Class to communicate to Omega Platinum Series temperature controllers via the iseries protocol.  
        The platinum series is the next gen to iseries. There are some differences in communication.
        Only one instance of this class should be created.
        Each controller can be called via its address.
        The factory default baudrate for newer controllers is 19200 bps.

        Programming Manual: https://assets.omega.com/manuals/M5452.pdf
    """

    OMEGA_WAIT = 0.02       # time to wait after a write and before a read.
    NAN = -999              # not a number

    def __init__(self, baud='19200', port=None):
        self.baud = baud
        self.port = self.autodetect_serial('omega_temp') if port is None else port
        self.ser = self.connect()
        self.sof = '*'              # Start of Frame
        self.terminator = '\r'      # Omega terminator string
        self.temps = {}

    @staticmethod
    def autodetect_serial(device):
        exclude = Omega_PlatinumSeries._water_trap_ports() if device == 'omega_temp' else []
        auto = autodetect.SerialAutoDetect({device: None}, exclude_ports=exclude)
        if auto.devices[device] is None:
            raise RuntimeError(f'Could not determine valid serial port for {device}')
        print(f'Autodetecting port.\nUsing port: {auto.devices[device]} for {device}')
        return auto.devices[device]

    @staticmethod
    def _water_trap_ports(yaml_path='water_traps.yaml'):
        """ Port reserved for the dedicated water-trap Omega bus (9600 baud),
            excluded from the 19200 baud omega_temp autodetect scan so a
            baud-mismatched reply can't be mistaken for the oven-Omega bus
            (see 2026-07-07 incident: autodetect locked onto the water-trap
            port, producing garbled reads until a reconnect corrected it). """
        try:
            with open(yaml_path) as f:
                cfg = yaml.safe_load(f) or {}
        except FileNotFoundError:
            return []
        port = cfg.get('port')
        return [port] if port else []

    def connect(self):
        """ connect to Omega temperature controllers over RS485 """
        baud = float(self.baud)
        # 0.5 s is well above the worst-case iSeries CNi response time at
        # 9600 baud (the water-trap controllers). At 19200 the controllers
        # finish much sooner, but `serial.Serial.read()` still blocks for
        # the full timeout per read, so each scan in ie3.py will pay it.
        timeout = 0.5
        try:
            ser = serial.Serial(self.port, timeout=timeout, baudrate=baud,
                                bytesize=8, parity='N', stopbits=1)
        except serial.serialutil.SerialException as exc:
            raise serial.serialutil.SerialException(
                f'Could not connect to serial port: {self.port}'
            ) from exc
        return ser

    def omega_send(self, cmd):
        """ Send a string command out the serial port. """
        try:
            self.ser.reset_input_buffer()
        except (termios.error, OSError) as e:
            logging.error(f"Omega reset_input_buffer failed: {e}")
        self.ser.write(cmd.encode())
        sleep(self.OMEGA_WAIT)

    def omega_read(self):
        """ Read from the bus until the Omega's \r terminator arrives, or
            the serial port's timeout expires (the fallback for a silent
            controller).
        """
        deadline = monotonic() + self.ser.timeout
        buf = bytearray()
        term_byte = self.terminator.encode()
        while monotonic() < deadline:
            waiting = self.ser.in_waiting
            if waiting:
                chunk = self.ser.read(waiting)
                buf.extend(chunk)
                if term_byte in chunk:
                    break
            else:
                sleep(0.005)
        raw = bytes(buf)
        logging.debug('omega_read raw (%d bytes): %r', len(raw), raw)
        try:
            # Take only the first terminator-delimited reply; anything past
            # it is a late straggler from a prior transaction and would
            # otherwise be concatenated into a value that won't parse.
            decoded = raw.decode('utf-8').split(self.terminator, 1)[0]
        except UnicodeDecodeError:
            logging.warning('UnicodeDecodeError on omega_read: %r', raw)
            return ''
        return decoded
    
    def omega_command(self, cmd):
        if cmd[0] != self.sof:
            cmd = f'{self.sof}{cmd}{self.terminator}'
        self.omega_send(cmd)
        rt = self.omega_read()
        return rt

    def get_omega_temp(self, add):
        """ Returns temperature reading from an Omega with address: add
            Typical command *01X01\r
        """
        rt = self.omega_command(f'{add:02d}X01')
        try:
            return float(rt)
        except ValueError:
            return self.NAN

    def get_omega_sp1(self, add):
        """ Returns setpoint1 from an Omega with address: add
            Typical command *01R01\r """
        rt = self.omega_command(f'{add:02d}R01')
        rt = self.decode_omega_temp(rt)
        return rt

    def set_omega_sp1(self, add, value):
        """ Sets setpoint1 to value on an Omega with address: add """
        hex_sp = self.encode_omega_temp(float(value))
        self.omega_command(f'{int(add):02d}W01{hex_sp}')
        return value

    def decode_omega_temp(self, hexstring):
        """ Function will decode a string returned by the
            return setpoint commands (R01 or R02).
            The value returned is a floating point number.
        """
        if len(hexstring) == 0:
            return self.NAN
        hexstring = hexstring.replace(self.terminator, '')
        try:
            binary = f'{int(hexstring,16):0>24b}'       # 24 bit number
        except ValueError:
            return self.NAN
        sign = 1 if binary[0] == '0' else -1
        div_key = {'001':0, '010':10, '011':100, '101':1000}
        try:
            div = div_key[binary[1:4]]
        except KeyError:
            return self.NAN
        value = int(binary[5:],2) / div * sign
        return value

    def encode_omega_temp(self, value, dec=1):
        """ Encodes a setpoint value into a hexidecimal representation for
            an Omega temperature controller.
            dec is for number of characters after the decimal point. Usually 1.
        """
        dec_key = {0:'001', 1:'010', 2:'011', 3:'101'}  # decimal place encoding
        if value > 360:
            print('Omega setpoint is too large > 360 C. Setting to 25 C')
            value = 25
        sign_bit = '0'
        # handle negative setpoint
        if value < 0:
            sign_bit = '1'
            value *= -1
        valueint = int(value * 10**dec)
        valuestr = f'{valueint:04d}'             # zero padded 4 chars.
        binary = f'{int(valuestr):0>20b}'        # binary representation
        full = sign_bit + dec_key[dec] + binary  # 24 bit number
        hex_sp = f'{int(full,2):x}'              # convert binary string to hex
        return hex_sp.upper()

    def scan(self, addresses):
        """ Scans sp1 and current temp from a list of Omega addresses and
            stores data in dictionary: self.temps
        """
        for add in addresses:
            sp = self.get_omega_sp1(add)
            val = self.get_omega_temp(add)
            self.temps[add] = [sp, val]
        return self.temps
    
    def set_rtd(self, add):
        """ command to tell the Omega a '385 Curve, 100 ohms' is used. """
        cmd = f'{add:02d}W100 110'
        self.omega_command(cmd)
        print(f'Omega address {add} is using a 385 Curve, 100 ohms RTD.')

    def set_add(self, current_add, new_add):
        cmd = f'{current_add:02d}W300 {new_add:02d}'
        self.omega_command(cmd)
        print(f'Omega at address {current_add} changed to address {new_add}')

    def set_serial(self, add, baud=19200, mode='rs485'):
        baud = int(baud)
        mode = mode.lower()
        # these values are from the manual
        b = {300:0, 600:1, 1200:2, 2400:3, 4800:4, 9600:5, 19200:6, 38400:7, 57600:8, 115200:9}
        m = {'rs232':0, 'rs485':1}
        if baud not in b:
            print('Invalid baudrate.')
            return -1
        if mode not in m:
            print('Invalid serial mode (select rs232 or rs485)')
            return -1
        
        cmd = f'{add:02d}W313 {m[mode]}{b[baud]}010'
        self.omega_command(cmd)
        print(f'Omega address {add} serial configured for {mode} at baudrate {baud}')

    def set_serial_steam(self, add):
        """ command to configure the serial data
            five digits are sent 00000
            0 Omega protocol, 0 command, 0 no line feed, 0 echo off, 0 space separator 
            see manual. """
        cmd = f'{add:02d}W310 00000'
        self.omega_command(cmd)
        self.set_serial(add)

    def get_pid_values(self, add):
        """ function to return the PID parameters """
        add = int(add)
        P = self.omega_command(f'{add:02d}R503')
        I = self.omega_command(f'{add:02d}R504')
        D = self.omega_command(f'{add:02d}R505')
        return [P, I, D]

    def scan_registers(self, add, start, end, width=2):
        """ Read-only sweep of R<reg> for reg in [start, end].

        Registers 503/504/505 (P/I/D) are documented for the Platinum series
        (M5452.pdf); older iSeries CN/CNi controllers may use a different
        memory map. This is for discovering the real register addresses on
        hardware where the model can't be confirmed (e.g. deployed in the
        field). Read commands are assumed side-effect-free on this protocol,
        unlike the W<reg> write commands.
        Returns {register_code: raw_reply}, in register order.
        """
        add = int(add)
        results = {}
        for reg in range(start, end + 1):
            code = f'{reg:0{width}d}'
            results[code] = self.omega_command(f'{add:02d}R{code}')
        return results

    def set_pid_from_yaml(self, add, yaml_path='omega_config.yaml'):
        """
        Load PID parameters for the given address from a YAML config file
        and write them to the Omega controller.
        """
        add = int(add)

        try:
            with open(yaml_path) as f:
                cfg = yaml.safe_load(f) or {}
        except FileNotFoundError:
            print(f"PID config file '{yaml_path}' not found.")
            return

        try:
            params = cfg[add]
        except KeyError:
            params = cfg.get(str(add))
        if params is None:
            print(f"No PID parameters for address {add} in {yaml_path}.")
            return

        P = params.get('P')
        I = params.get('I')
        D = params.get('D')

        if P is not None:
            cmd = f"{add:02d}W503 {P}"
            self.omega_command(cmd)
            print(f"Set Omega {add} P to {P}")

        if I is not None:
            cmd = f"{add:02d}W504 {I}"
            self.omega_command(cmd)
            print(f"Set Omega {add} I to {I}")

        if D is not None:
            cmd = f"{add:02d}W505 {D}"
            self.omega_command(cmd)
            print(f"Set Omega {add} D to {D}")


if __name__ == '__main__':
    try:
        opt = argparse.ArgumentParser(
            description='Omega temperature controll software.'
        )
        opt.add_argument('-c', action='store', dest='command',
                         help='send a string command (use manual)')
        opt.add_argument('--sp1', action='store', nargs=2, metavar=('ADD', 'TEMP'),
                         help='set setpoint1 on of Omega with address: ADD to TEMP')
        opt.add_argument('--scan', action='store_true', dest='scan',
                         help='scan for omegas')
        opt.add_argument('--pid', action='store', nargs=1, metavar=('ADD'), dest='getpid',
                         help='return PID values for an Omega with address: ADD')
        opt.add_argument('--scan-reg', action='store', nargs=3, metavar=('ADD', 'START', 'END'),
                         dest='scanreg',
                         help='read-only sweep of R<reg> for reg in [START, END] on Omega '
                              'address ADD; use to discover an unknown/undocumented register '
                              'map (e.g. P/I/D on older iSeries hardware)')
        opt.add_argument('--width', action='store', type=int, default=2,
                         help='zero-padded digit width for --scan-reg register codes (default 2; '
                              'use 3 for registers like 503-505)')
        opt.add_argument('-p', action='store', dest='port',
                         help='serial port to use (default is autodetect)')
        opt.add_argument('--baud', action='store', default='19200',
                         help='communicate at this baudrate.')
        opt.add_argument('--setadd', nargs=2, metavar=('ADD', 'NEWADD'),
                         help='change Omega address from ADD to NEWADD')
        opt.add_argument('--config', nargs=1, metavar=('ADD'),
                         help='setup Omega using IE3 defaults')

        options = opt.parse_args()

        if options.port:
            om = Omega_PlatinumSeries(port=options.port, baud=options.baud)
        else:
            om = Omega_PlatinumSeries(baud=options.baud)

        if options.command:
            rt = om.omega_command(options.command)
            print(f'command: {options.command} reply: {rt}')
            quit()

        elif options.scan:
            values = om.scan([1,2,3,4])
            print(values)
            for add,vals in values.items():
                print(f'{add}: setpoint1 {vals[0]}, actual {vals[1]}')

        elif options.sp1:
            print(f'Setting Omega {options.sp1[0]} to {options.sp1[1]} C')
            om.set_omega_sp1(options.sp1[0], options.sp1[1])

        elif options.getpid:
            pid = om.get_pid_values(options.getpid[0])
            try:
                print(f'P = {float(pid[0]):3.3f}, I = {float(pid[1]):3.3f}, D = {float(pid[2]):3.3f}')
            except ValueError:
                sys.stderr.write(f'Invalid PID reply for Omega {options.getpid[0]}: {pid}\n')
                sys.exit(1)

        elif options.scanreg:
            add, start, end = options.scanreg
            results = om.scan_registers(int(add), int(start), int(end), width=options.width)
            for code, reply in results.items():
                flag = ' (error?)' if reply.startswith('?') else ''
                print(f'R{code}: {reply!r}{flag}')

        elif options.setadd:
            om.set_add(int(options.setadd[0]), int(options.setadd[1]))
        
        elif options.config:
            add = int(options.config[0])
            om.set_rtd(add)
            om.set_serial_steam(add)
            om.set_pid_from_yaml(add)
    except (RuntimeError, serial.serialutil.SerialException) as exc:
        sys.stderr.write(f'{exc}\n')
        sys.exit(1)

"""
# simplest test code

ser = serial.Serial('/dev/ttyUSB1', timeout=0.05, baudrate=9600, bytesize=8, parity='N', stopbits=1)

ser.flushInput()

cmd = '*01R01\r'
ser.write(cmd.encode())
sleep(.1)
ser.read(1024).decode()
"""
