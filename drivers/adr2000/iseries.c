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
#define RESETDELAY		1				// Number of seconds to wait after a SP change
#define RECOG_CHAR 		'*'
#define MAXCHAR_RET		6
#define RCVfromSRVR		4

char data[MAXCHAR_RET];
char port[30] = "/dev/ser2";	// Default port

clock_t start_disable_time[MAXNUMOMEGAS];

// Global variables use for the command line calls
int fd;
unsigned int CLcalled = 0, CLreset = 0;
int CLadd = -1;
float CLvalue = -999;


int open_port(char *port) {
	
	if ((fd = open( port , O_RDWR )) == -1) {
		perror("iseries could not open serial port");
		return -1;
	} 

	tcflush( fd, TCIOFLUSH );
	return 0;

}

int send_command( char *msg ) {

	int bytes;

//	printf ( "strlen = %d, %s\n", strlen(msg), msg );

	tcflush( fd, TCIOFLUSH );
	bytes = write(fd, msg, strlen(msg) );
	tcdrain( fd );

	if (bytes < strlen(msg) ) {
		printf("command %s failed to send\n", msg);
		return 0;
	}

	return 1;  
}


char *init_opt(int argc, char ** argv) {
	int optltr;

	while ((optltr = getopt(argc, argv, "p:a:s:RSh")) != -1) {
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
			case 'h':
				usage();
			default:
				usage();
		}
	}

	return 0;
}

void usage() {
	printf("USAGE: iseries [-p serial port] [-S] [-a address] [-R address] [-s value] [-h]\n\n");
	printf("   Examples:\n");
	printf("   Run iseries driver for PANTHER on default serial port /dev/ser2 \n");
	printf("       iseries \n\n");
	printf("   Run iseries driver for PANTHER on serial port /dev/ser3 \n");
	printf("       iseries -p /dev/ser3 \n\n");
	printf("   Display current temperature and SP1 for Omega with address 2 on /dev/ser2 \n");
	printf("       iseries -p /dev/ser2 -a 2 \n\n");
	printf("   Send reset to Omega with addres 3 on /dev/ser1 \n");
	printf("       iseries -R -a 3 \n\n");
	printf("   Set SP1 to 235.5 C for Omega at address 4 on /dev/ser2 \n");
	printf("       iseries -p /dev/ser2 -a 4 -s 235.5 \n\n");
	printf("   Scan for all Omegas on /dev/ser2 \n");
	printf("       iseries -p /dev/ser2 -S \n\n");
	exit(0);
}


// Iseries Read command.  
// Example: *02R01   where the 02 is the omeaga address
//                         the R is the read and the 01 is the command Index
int iseries_Read( int omega_add, char command, char *com_num, int char_ret ) {

	char 	msg[8];
	char	omega_addStr[3];
	int 	i,
			bytes;

	for (i=0; i<MAXCHAR_RET; i++) data[i] = '\0';

	// The omega address is sent in hex
	sprintf( omega_addStr, "%02X", omega_add );

	msg[0] = RECOG_CHAR;
	msg[1] = omega_addStr[0];
	msg[2] = omega_addStr[1];
	msg[3] = command;
	msg[4] = com_num[0];
	msg[5] = com_num[1];
	msg[6] = '\r';
	msg[7] = '\0';

	send_command( msg );

	if ( (bytes = dev_read(fd, data, MAXCHAR_RET, char_ret, 0, 5, 0, 0)) <=0) {
		return 0;
	}

	return 1;	

}


// takes a ascii character that represents a hexidecimal number and returns
// its decimal equivalent.  eg  'A' = 10, '2' = 2
int hex2dec( char ascii ) {
	int hex;

	if (( ascii >= '0' ) && ( ascii <= '9' )) 
		hex = ascii - '0';
	else if (( ascii >= 'A' ) && ( ascii <= 'F' ))
		hex = ascii - 'A' + 10;
	else
		hex = 0;

	return hex;

}

unsigned long bin2dec( const char *s ) {
	const size_t LENGTH = strlen(s);

	size_t i;
	unsigned long decimal;

	for (decimal=i=0; i<LENGTH; i++) {
		if (s[i] == '1' )
			decimal += pow(2, LENGTH-(i+1));
	}

	return decimal;
}

// see Omega book on how to decode.  This will decode the data in "data" arrary.
float decodeSP( ) {

	unsigned int b0h, b1h, b2h, b3h, b4h, b5h, pos, div;
	float val;

	b0h = hex2dec( data[0] );
	b1h = hex2dec( data[1] );
	b2h = hex2dec( data[2] );
	b3h = hex2dec( data[3] );
	b4h = hex2dec( data[4] );
	b5h = hex2dec( data[5] );

	val = pow(16, 4) * b1h + pow(16, 3) * b2h + 16*16 * b3h + 16 * b4h + b5h;

	// positive or negative
	pos = b0h >> 3;
	if ( pos == 1 ) val = -val;
	
	// decimal point.
	switch (b0h - pos*8) {
		case 1: div = 1; break;
		case 2: div = 10; break;
		case 3: div = 100; break;
		case 4: div = 1000; break;
	}

	return val / div;

}

// omeaga_add is the address of the controller
// chan is the Setpoint 1 or 2
// val is the setpoint value
// decimal is the number of decimal places (0 to 3).
int ChangeSetPoint( int omega_add, int chan, float val, int decimal ) {

	char byte[] = "0000";
	char Sdata[] = "000000";
	char msg[12];
	char tmp[6];
	int vallong, i, inc = 0;

	// bit for positive or negative setpoint
	if (val < 0) {
		byte[0] = '1';
		val = abs(val);
	}

	// next three bits for decimal place
	switch ( decimal ) {
		case 0 : byte[3] = '1'; break;
		case 1 : byte[2] = '1'; break;
		case 2 : byte[2] = '1'; byte[3] = '1'; break;
		case 3 : byte[1] = '1'; byte[3] = '1'; break;
	}

	// convert value to integer
	val = val * decimal * 10;
	vallong = floor(val);
	
	// First character to send holds sign and decimal place information.
	sprintf( tmp, "%X", bin2dec(byte) );
	Sdata[0] = tmp[0];

	// Next five characters hold setpoint value in hex.
	sprintf( tmp, "%X", vallong );
	for (i=1; i<=5; i++ ) {
		if ( i <= 5-strlen(tmp) )
			Sdata[i] = '0';
		else {
			Sdata[i] = tmp[inc];
			inc++;
		}
	}

	if ( chan == 1 )
		sprintf( msg, "%c%02XW01%s\r", RECOG_CHAR, omega_add, Sdata );
	else
		sprintf( msg, "%c%02XW02%s\r", RECOG_CHAR, omega_add, Sdata );

	send_command( msg );

	return 1;
		
}

// This is a wrapper function so that panther.cmd code is not changed.
int set_sp1 ( int omega_add, int byteH, int byteL ) {

	int sp;

	sp = 256*byteH + byteL;

	ChangeSetPoint( omega_add, 1, sp/10, 1 );

	return sp;

}



float GetSetPoint( int omega_add, int chan ) {
	int ret;

	if ( chan == 2 )
		ret = iseries_Read( omega_add, 'R', "02", 6 );
	else 
		ret = iseries_Read( omega_add, 'R', "01", 6 );

	delay(10);

	if (ret == 1)
		return decodeSP( );
	else
		return UNKNOWN;

}

float GetTemp( int omega_add ) {
	float temp;

	if ( iseries_Read( omega_add, 'X', "01", 5 ) == 1)
		temp = atof(data);
	else
		temp = UNKNOWN;

	delay(10);
	return temp;	

}

void SendReset( int omega_add ) {

	iseries_Read( omega_add, 'Z', "02", 0 );

}


// Search for MAXNUMOMEGAS 
void find_omegas() {
	int i; 
	float tmp;

	for(i = 1; i < MAXNUMOMEGAS; i++) {
		tmp = GetTemp( i );
		if ( tmp != UNKNOWN ) {
			printf("Omega %d online -- curr temp = %3.1f\n", i, tmp );
			printf("                   curr SP1 = %3.1f\n", GetSetPoint(i, 1) );
		}			
	}

}

void processCL( ) {

	if (CLadd > 0) {
		if (CLvalue > -400) {
			printf("Setting SP1 on Omega %d to %f\n\n", CLadd, CLvalue);
			ChangeSetPoint( CLadd, 1, CLvalue, 1);
			exit(0);
		}
		if (CLreset == 1) {
			printf("Sending RESET to Omega %d\n\n", CLadd);
			SendReset( CLadd );
			exit(0);
		}

		printf("Temp on Omega %d is %4.1f\n", CLadd, GetTemp( CLadd ) );
		printf("Setpoint1 on Omega %d is %4.1f\n\n", CLadd, GetSetPoint( CLadd, 1 ) );

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

	/* attach iseries name */
	name = nl_make_name( "iseries", 1 );
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
	
				case msgI_Quit:
					close(fd);
					exit(0);

				case msgI_changeSp1:
					Reply( rcvPid, "", 0 );
					temps[2*(rcvMsg[1]-1)+1] = set_sp1(rcvMsg[1], rcvMsg[2], rcvMsg[3]);
					Col_send(colId);
					delay(100);
					break;

				case msgI_colId:
					Col_send( colId );
					break;

				case msgI_OmegaReset:
					Reply( rcvPid, "", 0 );
					SendReset( rcvMsg[1] );
					break;

				case msgI_noMsg:
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
					temps[2*index] = GetTemp( chan );
					if ( temps[2*index] != UNKNOWN )
						temps[2*index+1] = GetSetPoint( chan, 1 );
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

