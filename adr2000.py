#! /usr/bin/env python

VERSION = '1.4'
""" Added autodetect.py and removed old autodetect code.  GSD 150417

    Converted to python3.8 210915

    Removed Driver's flow_omega/OFM coupling (flow_omega.py isn't part of
    this repo -- import flow_omega was a hard crash -- and no flow meter is
    wired to the ADR2000 boards on UCATS). Added Driver.from_config() to
    build a2d/dac/dig from config.yaml instead of hardcoded dicts. GSD 260722
"""

import sys
import os
from time import sleep, time, localtime, strftime
from numpy import polyval
from threading import Thread
import queue
import serial
import yaml

import autodetect

DIG_DELAY = 0.1
DELAYloop = 0.1

# FM get Tsec going not t since 1970
now = localtime(time())
TsecStartDay = (time() - ((now.tm_hour*60 + now.tm_min)*60 + now.tm_sec))
#print(f'TsecStartDay {TsecStartDay}')

class ADR2000:
    """ Commands that work on the ADR2000 data acquisition board.
    
        port is the serial port the ADR board is on.
        use boardaddress for more than one ADR2000 board, leave blank for one board.
        
        ADR2000 boards are from www.ontrak.net
        These are not a complete set of commands !!
    """

    def __init__(self, port, boardaddress=None):
        
        self.port = port
        self.add = boardaddress
        if port is None:
            auto = autodetect.SerialAutoDetect({'adr2000': None})
            auto.devices['adr2000']
            if auto.devices['adr2000'] is None:
                print('Could not deterimine valid serial port for ADR2000 board(s).')
                quit()
            print(f'Using port: {auto.devices["adr2000"]} for ADR2000 boards(s)')
            self.port = auto.devices['adr2000']
            
        try:
            self.ser = serial.Serial(self.port, timeout=0.06, baudrate=9600, 
                bytesize=8, parity='N', stopbits=1)
        except serial.serialutil.SerialException:
            sys.stderr.write(f"adr2000: Can't connect to serial port: {self.port}\n")
            quit()
            
        self.DIGIN = []
        self.ANALOGIN = []
    
    def send(self, cmd):
        """ Basic command sent to ADR2000 board. """
        if self.add == None:
            cmdv = f'{cmd}\r'.encode()
        else:
            cmdv = f'{self.add}{cmd}\r'.encode()

        self.ser.write(cmdv)
    
    def read(self, bytes=50):
        """ Read data off of serial port. """
        try:
            r = self.ser.read(bytes).decode()
        except UnicodeDecodeError:
            r = ''
        self.ser.flushInput()
        return r
        
    def uni(self, a):
        return 5.*(a/4096.)  # conversion for 0-5VDC

    def bi(self, a):
        return 10.*(a/4096.) - 5.  # conversion for +/- 5VDC
    
    def analogin_uni(self, channel):
        """ Read analog input in unipolar mode (0-5V). """
        self.send(f'RD{channel}')
        A = self.read()
        if A == '':
            return None
        return [(time()-TsecStartDay), self.uni(int(A))]
        
    def analogin_uni_all(self):
        """ Read all channels on board with address=add in unipolar mode. """
        self.send('RD')
        chans = self.read().strip().split(' ')
        if len(chans) == 1:
            return
        try:
            D = [self.uni(int(ch)) for ch in chans]
        except ValueError:
            print("analog_uni_all ValueError")
            return
        D[:0] = [(time()-TsecStartDay)]
        self.ANALOGIN = D
        return D
        
    def analogin_bi(self, channel):
        """ Read analog input in bipolar mode (+/-5V) of one port.
            channel = analog channel address on board.
        """
        self.send(f'RB{channel}')
        A = int(self.read())
        if A == '':
            return
        return [(time()-TsecStartDay), self.bi(int(A))]
    
    def analogin_bi_all(self):
        """ Read all channels on board with address=add in bipolar mode """
        self.send('RB')
        chans = self.read().strip().split(' ')
        if len(chans) == 1:
            return
        D = [self.bi(int(ch)) for ch in chans]
        D[:0] = [(time()-TsecStartDay)]
        self.ANALOGIN = D
        return D
        
    def analogin(self, tup):
        """ Uses mode number to choose uni or bipolar inputs. """
        channel, mode = tup
        if mode == 0:
            return analogin_uni(self, channel)
        elif mode == 1:
            return analogin_bi(self, channel)
        else:
            return -1
        
    def analogout(self, voltage, chan=1):
        """ Analog Output Commands - Version A (12-bit, 0-5VDC analog output)
            add = board address
            chan = 1 or 2
            voltage = 0 to 5 
            simplified logic: GSD 210915
        """
        if chan != 1 and chan != 2:
            return None

        cmd = 'VA' if chan == 1 else 'VB'
        DAC = int(round(voltage/5. * 4095.))
        DAC = 4095 if DAC > 4095 else DAC
        DAC = 0 if DAC < 0 else DAC

        self.send(f'{cmd}{DAC}')
        return DAC
        
    """ Digital I/O commands """
    
    def configdig(self, cmd):
        """ Configures each digital port on an ADR2000 board.
        
            The cmd is for all 8 ports on an ADR2000 board.  Set a bit to 1 for
            dig input and to 0 for dig out.  The left most bit is for dig port 7 (PA7).
        """
        if len(cmd) != 8:
            sys.stderr.write("Bad cmd for configuring digital I/O on ADR2000\n")
            return False
        
        self.send(f'CPA{cmd}')
        print(f"ADR2000 board={self.add} digital I/O configured: CPA{cmd}")
        sleep(DIG_DELAY)
        return True
    
    def digin(self):
        """ Reads all 8 digital ports on ADR2000 board.
        
            If a dig line is set for dig out, it will return 0.
            The returned data is reversed so that the first dig channel is at the front of
            the array.
        """
        self.send('RPA')
        dig = self.read().strip().split(' ')
        if len(dig) == 8:
            dig = dig[::-1]                 # reverse the list
            dig = [int(i) for i in dig]     # make int not str
            dig[:0] = [(time()-TsecStartDay)]              # tack the Tsec on infront of array.
            self.DIGIN = dig
            return self.DIGIN
        else:
            return None
            
    def dighigh(self, channel):
        """ Sets a digital line or channel high.  """
        self.send(f'SETPA{channel}')
        sleep(DIG_DELAY)

    def diglow(self, channel):
        """ Sets a digital line or channel low.  """
        self.send(f'RESPA{channel}')
        sleep(DIG_DELAY)

    
class Driver(Thread):
    """ threaded driver for one or more ADR2000 boards.

        a2d, dac, and dig are dicts keyed by variable name, each value a
        tuple of (board address, channel, calib-or-state) -- see
        from_config() to build these from config.yaml instead of passing
        the dicts in directly.
    """

    def __init__(self, a2d=None, dac=None, dig=None, portAD=None):
        Thread.__init__(self)
        self.job = queue.Queue()
        self.a2d = a2d or {}    # analog to dig channels
        self.dac = dac or {}    # dig to analog channels
        self.dig = dig or {}    # dig in and out
        self.ADRs = {}          # list of ADR20000 instances for each ADR board.
        self.data = {}          # data used for engineering file
        self.loop_t = 1         # driver loop timing in seconds

        """ Determine number of ADR boards used and their addresses. """
        add1 = set(v[0] for v in self.a2d.values())
        add2 = set(v[0] for v in self.dig.values())
        add3 = set(v[0] for v in self.dac.values())

        self.adds = list(add1 | add2 | add3)
        self.a2d_adds = list(add1)
        self.dig_adds = list(add2)

        for add in self.adds:
            self.ADRs[add] = ADR2000(port=portAD, boardaddress=add)
        self.configdigports()

    @classmethod
    def from_config(cls, config_file='config.yaml', portAD=None):
        """ Build a Driver from config.yaml's devices.adr2000 section:

            devices:
              adr2000:
                port: /dev/ttyUSBx      # omit for autodetect
                dig:
                  sol_cal: [0, 4, out]      # [board address, channel, in/out]
                a2d:
                  flask_press: [0, 1, [21.46538, -5.02333]]   # [board, channel, calib]
                dac:
                  vfr: [0, 0]               # [board, channel]
        """
        with open(config_file) as f:
            cfg = yaml.safe_load(f)
        adr_cfg = cfg.get('devices', {}).get('adr2000', {}) or {}

        a2d = {k: tuple(v) for k, v in (adr_cfg.get('a2d') or {}).items()}
        dac = {k: tuple(v) for k, v in (adr_cfg.get('dac') or {}).items()}
        dig = {k: tuple(v) for k, v in (adr_cfg.get('dig') or {}).items()}

        port = portAD if portAD is not None else adr_cfg.get('port')
        return cls(a2d=a2d, dac=dac, dig=dig, portAD=port)
  
    def configdigports(self):
        """ Creates a config string to set dig in and out channels.  
        
            dig is a list of tuples that has the board address, channel 
               and 'in' or 'out' state.
            adds is the ADR2000 board addresses used.
        """
        cfg = {}
        for addr in self.adds:
            """ 0 is DigOut, 1 is DigIn, channel 0 is left most. """
            cfg[addr] = list('00000000')
    
            for d in list(self.dig.values()):
                addr, chan, state = d
                if state == 'in':
                    cfg[addr][chan] = '1'
            
        for addr in self.adds:
            """ Need to reverse the cfg string for the ADR digconfig command. """
            cmd = cfg[addr][::-1]
            cmd = ''.join(cmd)
            self.ADRs[addr].configdig(cmd)

    def apply_calcurves(self):
        """ Applies cal curve data to analog variables defined in a2d variable.  
            Also updates data dict.
        """
        for k in list(self.a2d.keys()):
            add, chan, calib = self.a2d[k]
            # print(add, chan, calib)
            try:
                volts = self.ADRs[add].ANALOGIN[chan+1]     # +1 to skip Tsec in 0 index
                units = polyval(calib, volts)
                self.data[k] = units
                self.data['Tsec'] = self.ADRs[add].ANALOGIN[0]
            except IndexError:
                print(f'ADR2000 Error: {add} {chan}')
            
    def digtopacket(self):
        """ Adds all dig chans to data dict. """
        for k in list(self.dig.keys()):
            add, chan, state = self.dig[k]
            self.data[k] = self.ADRs[add].DIGIN[chan+1]     # +1 to skip Tsec in 0 index
                
    def setDAC(self, cmd):
        """ Sets a DAC channel on an ADR2000 board.
            cmd is a list with DAC variable and a setpoint value.
        """
        var, val = cmd
        add, chan, calib = self.dac[var]
        volt = polyval(calib, val)
        volt = 5 if volt > 5 else volt
        volt = 0 if volt < 0 else volt
        self.ADRs[add].analogout(volt, chan)
               
    def setDig(self, cmd):
        """ Sets a dig out line either 'high'/'on' or 'low'/'off'. """
        var, val = cmd
        add, chan, type = self.dig[var]
        if type.lower() != 'out':
            return
        elif val.lower() == 'high' or val.lower() == 'hi' or val.lower() == 'on':
            self.ADRs[add].dighigh(chan)
        elif val.lower() == 'low' or val.lower() == 'off':
            self.ADRs[add].diglow(chan)
            
        
    def run(self):
        """ Run loop called with thread start instance. 
            Runs continuously reading dig and analog data every loop_t seconds.
        """
  
        t = time()
        while True:
            # read dig and analog data

            for add in self.a2d_adds:
                self.ADRs[add].analogin_uni_all()
                self.apply_calcurves()
            for add in self.dig_adds:
                self.ADRs[add].digin()
                self.digtopacket()

            # wait until near the end of loop_t checking Queue
            while self.loop_t-(time()-t) > DELAYloop*3:
                sleep(DELAYloop)
                self.__tasks()

            tsleep = self.loop_t - (time() - t)     

            if tsleep < 0:
                os.write(2, f'ADR Driver Error  tsleep= {tsleep} '.encode())
            else:
                # wait the remaining time
                sleep(self.loop_t - (time()-t))

            t = time()
            
    def __tasks(self):
        """ Possible job taskes in queue. """

        if self.job.qsize() > 0:
            try:
                cmd = self.job.get()
            except ValueError:
                return
            
            print(f'ADR: {cmd}')

            # valid commands are DAC or digout variables or 'quit'                
            if cmd[0] == 'quit': 
                sys.exit("Stopping ADR2000 driver")
            elif cmd[0] in list(self.dac.keys()):
                self.setDAC(cmd)
            elif cmd[0] in list(self.dig.keys()):
                self.setDig(cmd)

            # run again until queue is empty
            self.__tasks()
            

if __name__=='__main__':

    import argparse

    opt = argparse.ArgumentParser(
        description = 'ADR2000 driver.',
    )
    opt.add_argument('-c', action='store', 
        dest='command', help='command string to send on serial port')
    opt.add_argument('-p', action='store', 
        dest='port', help='serial port to use. (default is autodetect)')
    opt.add_argument('-a', default=None, dest='add', 
        help='ADR2000 board address (default is None)')
    opt.add_argument('--tog', dest='tog', metavar='LINE', action='store', 
        help='Toggle a digital line high then low.')
        
    options = opt.parse_args()

    if options.port:
        a = ADR2000(port=options.port, boardaddress=options.add)
    else:
        a = ADR2000(port=None, boardaddress=options.add)
    
    if options.command:
        print(f"Sending: {options.command}")
        a.send(options.command)
        print(a.read())
        quit()
    
    if options.tog:
        print(f"Setting dig line {options.tog} high")
        a.dighigh(int(options.tog))
        sleep(.5)
        print(f"Setting dig line {options.tog} low")
        a.diglow(int(options.tog))

    for ch in [0,1,2,3]:
        print(f'chan {ch} {a.analogin_uni(ch)}')


    print(a.analogin_uni_all())
    """    
    #a.configdig('11110000')
    a.digin()
    print(a.DIGIN)
    a.dighigh(2)
    a.digin()
    print(a.DIGIN)
    a.diglow(2)
    a.digin()
    print(a.DIGIN)
    quit()
    
    t = time()
    i = 100
    for i in range(i):
        print(a.analogin_uni_all(0))
        
    print((time()-t)/i)
    """
