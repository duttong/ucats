#! /usr/bin/env python
""" Serial port autodetection for UCATS hardware.

    Probes all available (non-Bluetooth) serial ports and identifies which
    device is connected to each by sending a device-specific command and
    checking for a response.  Supports: ADR2000 board(s), Valco valves, and
    Omega Platinum Series temperature controllers.

    Usage:
        auto = SerialAutoDetect({'valco': None, 'omega_temp': None})
        port = auto.devices['valco']   # None if not found

    Adapted from IE3_acquisition/autodetect.py (which already has an
    adr2000 probe matching this instrument's hardware); baud rates are set
    per-device to match UCATS's actual drivers: valco and adr2000 at 9600
    (drivers/valve/valco.c, drivers/adr2000/adr2000.c), omega_temp at 19200
    (Omega_PlatinumSeries in omega.py). GSD 260722
"""

import string
import serial
import serial.tools.list_ports as list_ports
from time import sleep

all_devices = {'adr2000': None, 'valco': None, 'omega_temp': None}


class SerialAutoDetect():
    """ Probes serial ports and maps device names to their port paths.

        Pass a dict of {device_name: None} for only the devices you need,
        or use all_devices to scan for everything.  After construction,
        self.devices contains the detected port path for each device, or
        None if the device was not found.
    """

    READBYTES = 1000
    DELAY = 0.1

    def __init__(self, devices=all_devices, exclude_ports=None):
        """ exclude_ports: ports to skip entirely, e.g. a dedicated bus
            running at a different baud rate than any of the devices being
            probed here. Without this, a baud-mismatched device on that
            port can still return bytes that happen to decode and get
            mistaken for the device being searched for. """
        self.devices = devices
        self.exclude_ports = set(exclude_ports or [])
        self.baud = {'valco': 9600, 'adr2000': 9600, 'omega_temp': 19200}
        self.cmds = {
            'valco': self.cmd_valco,
            'adr2000': self.cmd_adr2000,
            'omega_temp': self.cmd_omega_temp
        }
        self.assign_ports()

    def potential_ports(self):
        potentialports = []
        for port, desc, hwid in sorted(list_ports.comports(), reverse=True):  # reverse to list USB devices first
            if port.find('Bluetooth') == -1 and port not in self.exclude_ports:
                potentialports.append(port)
        return potentialports

    """ Hardcoded commands for each type of device """
    def cmd_valco(self, ser):
        """ Requires a Valco valve on address 1. UCATS's valco.c reads
            commands terminated with '\\n' at 9600 baud (drivers/valve/valco.c). """
        ser.write(b'1cp\n')
        sleep(self.DELAY)
        d = ser.read(self.READBYTES)
        self.devices['valco'] = ser.port if len(d) > 0 else None

    def cmd_adr2000(self, ser):
        ser.write(b'\rRD\r')
        sleep(self.DELAY)
        d = ser.read(self.READBYTES)
        self.devices['adr2000'] = ser.port if len(d) > 0 else None

    def cmd_omega_temp(self, ser):
        """ Requires an Omega on address 1. R01 (setpoint1) replies with a
            short hex string, so validate that shape instead of merely
            accepting any decodable bytes -- a device on a different baud
            rate can still return noise that happens to decode. """
        ser.write(b'*01R01\r')
        sleep(0.3)      # Omega delay is longer than self.DELAY
        d = ser.read(self.READBYTES)
        try:
            v = d[1:].split(b'\r', 1)[0].decode()
        except UnicodeDecodeError:
            v = None
        valid = (
            v is not None
            and b'\r' in d
            and 1 <= len(v) <= 6
            and all(c in string.hexdigits for c in v)
        )
        self.devices['omega_temp'] = ser.port if valid else None

    def process_cmds(self, device, ser):
        func = self.cmds[device]
        ser.flushInput()
        sleep(self.DELAY)
        func(ser)

    def assign_ports(self):
        for port in self.potential_ports():
            for dev, status in self.devices.items():
                if status is None:
                    try:
                        ser = serial.Serial(port, timeout=self.DELAY, baudrate=self.baud[dev])
                        self.process_cmds(dev, ser)
                        ser.close()
                    except serial.serialutil.SerialException:
                        print(f'{dev} not found on {port}')


if __name__ == '__main__':

    ''' Here is how to call on a single serial device
    dv = {'valco': None}
    auto = SerialAutoDetect(dv)
    '''
    auto = SerialAutoDetect()
    print(auto.devices)
