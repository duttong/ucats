#include <unistd.h>
#include <fcntl.h>
#include <sys/dev.h>
#include <sys/name.h>
#include <sys/proxy.h>
#include <sys/kernel.h>
#include <sys/uio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include "nortlib.h"
#include "collect.h"
#include "panthermsg.h"
#include <errno.h>
#include <termios.h>
#include <time.h>

#define UNKNOWN 		-999
#define MAXNUMOMEGAS	12 + 1
#define RESETDELAY		4				// Number of seconds to wait after a SP change
#define MSGSIZE			8

#define TIMEOUT_PERIOD	10
#define RCV_MSG_SIZE	256
#define RCVfromSRVR		4
#define	RS_DATA_SIZE	40
#define POLY 			0xA001
#define ACK				6
#define QUEUE_SIZE		50

typedef enum {
	FALSE = 0,
	TRUE
} Bool;

// to compile this program use cc -2 -ms -g

char msg[MSGSIZE];
char port[30] = "/dev/ser2";	// Default port
clock_t start_disable_time[MAXNUMOMEGAS];

// Global variables use for the command line calls
int fd;
unsigned int CLcalled = 0, CLreset = 0;
unsigned int CLtestCRC = 0;
int CLadd = -1;
float CLvalue = -999;


int open_port(char *port) {
	
	if ((fd = open( port , O_RDWR )) == -1) {
		perror("modbus could not open serial port");
		return -1;
	} 

	tcflush( fd, TCIOFLUSH );
	return 0;

}

int send_command() {

	int bytes;

	bytes = write(fd, msg, MSGSIZE);
	tcdrain( fd );

	if (bytes < MSGSIZE) {
		printf("command %s failed to send\n", msg);
		return 0;
	}

	return 1;  
}

char *init_opt(int argc, char ** argv) {
	int optltr;

	while ((optltr = getopt(argc, argv, "p:a:s:RSTh")) != -1) {
		CLcalled = 1;
		switch( optltr ) {
			case 'p': sprintf(port,"%s", optarg);
				CLcalled = 0;
				break;
			case 'a': CLadd = atoi(optarg);
				break;
			case 's': CLvalue = atof(optarg);
				break;
			case 'S':
				if ( open_port(port) < 0 ) {
					printf("unable to open the serial port \n");
					exit( 1 );
				}
				find_omegas( );
				close( fd );
				exit( 1 );
			case 'R': CLreset = 1;
				break;
			case 'T': CLtestCRC = 1;
				break;
			case 'h':
				usage();
			default:
				usage();
		}
	}

	return 0;
}

void usage() {
	printf("USAGE: modbus [-p serial port] [-S] [-a address] [-R address] [-s value] [-h]\n\n");
	printf("   Examples:\n");
	printf("   Run modbus driver for PANTHER on default serial port /dev/ser2 \n");
	printf("       modbus \n\n");
	printf("   Run modbus driver for PANTHER on serial port /dev/ser3 \n");
	printf("       modbus -p /dev/ser3 \n\n");
	printf("   Display current temperature and SP1 for Omega with address 2 on /dev/ser2 \n");
	printf("       modbus -p /dev/ser2 -a 2 \n\n");
	printf("   Send reset to Omega with addres 3 on /dev/ser1 \n");
	printf("       modbus -R -a 3 \n\n");
	printf("   Set SP1 to 235.5 C for Omega at address 4 on /dev/ser2 \n");
	printf("       modbus -p /dev/ser2 -a 4 -s 235.5 \n\n");
	printf("   Scan for all Omegas on /dev/ser2 \n");
	printf("       modbus -p /dev/ser2 -S \n\n");
	exit(0);
}



unsigned long crc_calculation(unsigned char *start_string, unsigned char number_byte) {
	unsigned long crc;
	unsigned char bit_counter;
	unsigned char *data_pointer;

	data_pointer = start_string;
	crc = 0xFFFF;

	while (number_byte>0) {

		crc ^= *data_pointer;
		bit_counter = 0;

		while (bit_counter<8) {
			if ( crc & 0x0001 ) {
		        crc >>= 1;
				crc ^= POLY;
			} else {
				crc >>= 1;
			}
			bit_counter++;
		}
		number_byte--;
		data_pointer++;
	}

	//printf("crc = %ld\n", crc);
	return (crc);
}

void reset(int address) {
	unsigned long chk;

// first build the string to send to the omega
	msg[0] = address;
	msg[1] = 6;
	msg[2] = 0;
	msg[3] = 43;
	msg[4] = 255;
	msg[5] = 255;

	chk = crc_calculation(msg,6);
	msg[7] = chk/256;
	msg[6] = chk-256 * msg[7];
	msg[8] = 0;

	send_command();
}

void testcrc () {
	unsigned long chk;

	msg[0]=4;
	msg[1]=4;
	msg[2]=2;
	msg[3]=0;
	msg[4]=125;
	msg[5]=0;
	msg[6]=0;
	msg[7]=0;
	msg[8]=0;
	chk = crc_calculation(msg,5);

	printf("chk = %ld dec, hex: %X\n", chk, chk);

}

// value1 is the high bit and value2 is the low bit.
float set_sp1(int address, int value1, int value2) {
	unsigned long chk;
	int sp;
//	int newsp;

// first build the string to send to the omega
	msg[0] = address;
	msg[1] = 6;
	msg[2] = 0;
	msg[3] = 1;
	msg[4] = value1;
	msg[5] = value2;
	chk = crc_calculation(msg, 6);
//	chk = 1234;
	msg[6] = chk & 0xFF;
	msg[7] = chk / 256;
	msg[8] = 0;

	// Sometimes the omega SP is set to 999.9 ???.
	// It takes about .3 sec before I can poll the
	// omega and find out if it was set correctly.
	sp = 256*value1 + value2;
	if (sp > 0x80) {
		// the  temp is negative
		sp =~ sp + 1;
		sp =- sp;
	}

	// bad setpoint (4000 = 400.0 C)
	if (sp > 4000) {
		printf("OMEGA Setpoint dangerously high at %f.  IGNORING!\n", (float)sp/10);
		return -99;
	}

	send_command();

	/*
	// see comment above.
	printf("msg = %x %x %x %x %x %x, %x %x, %X\n", msg[0], msg[1], msg[2], msg[3], msg[4], msg[5], msg[6], msg[7], chk);
	printf("OMEGA SP1: %d value1 = %x, value2 = %x, (%x, %x = %X) \n", sp, value1, value2, msg[6], msg[7], chk);

	delay(300);
	if ( (newsp = get_sp1(address)) != sp ) {
		printf("error sp = %d, newsp = %d\n", sp, newsp);
	}
	*/

	start_disable_time[address] = clock();

	return sp;

}


int get_sp1(int address) {
	return readOmega(address, 1);
}

int get_sp2(int address) {
	return readOmega(address, 2);
}

int get_temp(int address) {
	return readOmega(address, 39);
}

int readOmega(int address, int command) {
	int 			tmp, bytes = 0;
	unsigned long 	chk;
	char data1[RCV_MSG_SIZE];
	char d_data[5];

	// first build the string to send to the omega
	msg[0] = address;
	msg[1] = 4;
	msg[2] = 0;
	msg[3] = command;
	msg[4] = 0;
	msg[5] = 1;
	chk = crc_calculation( msg, 6 );
	msg[6] = chk & 0xFF;
	msg[7] = chk / 256;
	msg[8] = 0;

	// Clean out buffer.
	//bytes = dev_read(fd, data1, RCV_MSG_SIZE, 0, 0, 0, 0, 0);
	tcflush( fd, TCIOFLUSH );

	send_command();

	if ( (bytes = dev_read(fd, &data1, RCV_MSG_SIZE, 7, 0, 1, 0, 0)) <= 0) {
		//printf("timout reading Omega on controller %i\n", address);
		return UNKNOWN;
	}
//	printf("data = %x %x %x %x %x, %x %x %x\n", data1[0], data1[1], data1[2], data1[3], data1[4], data1[5], data1[6], data1[7]);

	//now parse the data1
	memcpy(d_data, data1, 5);
	chk = crc_calculation(d_data, 5);

	if ( data1[6] != (chk/256) ) {
		printf("Get Temp checksum failure on channel %d (data1[6] %x != chk/256 %x )\n", address, data1[6], chk/256);
		printf("chk= %ld, %lX data1[5]=%x data1[6]=%x bytes=%d \n",chk, chk, data1[5], data1[6], bytes);
		printf("data = %x %x %x %x %x, %x %x %x\n", data1[0], data1[1], data1[2], data1[3], data1[4], data1[5], data1[6], data1[7]);
		return UNKNOWN;
	} else 
	if (data1[5] != (chk&0xFF)) {
		printf("Get Temp checksum failure on channel %d chk&0xFF %x\n",address, chk&0xFF);
		printf("chk= %ld, %lX data1[5]=%d data1[6]=%d bytes=%d \n",chk,chk,data1[5],data1[6],bytes);
		printf("data = %x %x %x %x %x, %x %x %x\n", data1[0], data1[1], data1[2], data1[3], data1[4], data1[5], data1[6], data1[7]);
		return UNKNOWN;
	}

	tmp = 256*data1[3] + data1[4];
	if (tmp>0x80) { // the  temp is negative
		tmp =~ tmp + 1;
		tmp =- tmp;
	}

	return tmp;

}

// Search for MAXNUMOMEGAS 
void find_omegas() {
	int i, tmp;

	for(i = 1; i < MAXNUMOMEGAS; i++) {
		tmp = get_temp(i);
		if ( tmp != UNKNOWN ) {
			printf("Omega %d online -- curr temp = %3.1f\n", i, (float) tmp/10);
			printf("                   curr SP1 = %3.1f\n", (float) get_sp1(i)/10 );
		}			
	}

}

void processCL( ) {
	int CLvalueINT, CLvalueINT1, CLvalueINT2;

	if (CLadd > 0) {
		if (CLtestCRC == 1) {
			testcrc();
			exit(0);
		}
		if (CLvalue > -400) {
			printf("Setting SP1 on Omega %d to %f\n\n", CLadd, CLvalue);
			CLvalueINT = floor(CLvalue*10);
			CLvalueINT1 = CLvalueINT>>8;
			CLvalueINT2 = CLvalueINT&255;
			set_sp1(CLadd, CLvalueINT1, CLvalueINT2);
			exit(0);
		}
		if (CLreset == 1) {
			printf("Sending RESET to Omega %d\n\n", CLadd);
			reset(CLadd);
			exit(0);
		}

		printf("Temp on Omega %d is %4.1f\n", CLadd, (float) get_temp(CLadd) / 10);
		printf("Setpoint1 on Omega %d is %4.1f\n\n", CLadd, (float) get_sp1(CLadd) / 10);

	} else {
		printf("Bad Omega address %d\n\n", CLadd);
	}
	exit(0);
}

void main ( int argc, char ** argv ) {
		
	char		rcvMsg[RCVfromSRVR];
	char		*name;

	pid_t		rcvPid,
				colProxy;
			
	send_id		colId;
			
	int			modname_id,
				chan,
				index = 0,
				loop;	

	int 		*temps;


	/* get command from the command line */
	init_opt(argc, argv);

	printf("omega 485 communication started on port: %s\n", port);	
	
	// open the serial port
	if (open_port(port) < 0) {
		printf("unable to open the serial port \n");
		return;
	}

	// If called from the command line
	if (CLcalled == 1) {
		processCL( );
	}

	/* attach modbus name */
	name = nl_make_name( "modbus", 1 );
	modname_id = qnx_name_attach( 0, name );
	if ( modname_id == -1 )
		nl_error( 3, "Unable to attach name %s", name );


	// All code below is for communications to data collection.

	temps = (int *) malloc( sizeof(int) * (MAXNUMOMEGAS) * 2 );
	for(index=0; index < (MAXNUMOMEGAS)*2; index++)
		temps[index] = UNKNOWN;

	colId = Col_send_init ("Omega485", temps, (sizeof(int)*(MAXNUMOMEGAS)*2) );
	colProxy = Col_set_proxy ( 3, msg_colId );

	Col_send(colId);

	// Main loop
	while ( 1 ) {

		rcvMsg[0] = rcvMsg[1] = rcvMsg[2] = rcvMsg[3] = msg_noMsg;
		rcvPid = Creceive( 0, &rcvMsg, RCVfromSRVR );

		if ( rcvPid != -1 ) {

			switch ( rcvMsg[0] ) {
	
				case msg_modbusQuit:
					close(fd);
					exit(0);

				case msg_changeSp1:
					Reply( rcvPid, "", 0 );
					temps[2*(rcvMsg[1]-1)+1] = set_sp1(rcvMsg[1], rcvMsg[2], rcvMsg[3]);
					Col_send(colId);
					delay(100);
					break;

				case msg_colId:
					Col_send( colId );
					break;

				case msg_OmegaReset:
					Reply( rcvPid, "", 0 );
					reset(rcvMsg[1]);
					break;

				case msg_noMsg:
					break;

				default:
					break;
			}

		} else {

			// The loop variable slows down the calls to the omegas,
			// but still services the Creceive function.
			if ( loop > 3 ) loop = 0;
			
			if ( loop == 1 ) {

				// Poll the omegas
				if (index >= MAXNUMOMEGAS) index = 0;
				chan = index+1;

				// Don't pull the omega for RESTDELAY seconds after a RESET has been sent
				if ( (clock()-start_disable_time[chan]) > RESETDELAY * CLOCKS_PER_SEC) {
//printf("sending omega %d\n", chan);
					temps[2*index] = get_temp(chan);
					if ( temps[2*index] != UNKNOWN )
						temps[2*index+1] = get_sp1(chan);
					else
						temps[2*index+1] = UNKNOWN;
				} 
				index++;
		
			} else {
				delay( 50 );
			}

			loop++;

		}
	}
}

