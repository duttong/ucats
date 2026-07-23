/* 161228 Changed proxy from 11 to 13.  11 conflicted with o3x.  */

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
#include <errno.h>
#include <termios.h>
#include <time.h>
#include "nortlib.h"
#include "globmsg.h"
#include "collect.h"

#include "vaisala.h"


#define BAUD			4800
#define PAR			  "even"
#define BITS			   7
#define STOPB			   1

#define PACKETSIZE		  24	// number of chars returned in a normal packet
#define MAXCHAR_RET		1000	// largest packet that can be returned
#define RCVfromSRVR        2    // max number of bytes a command from the server can be.
#define NAN				  -1

int		fd;
char 	port[30] = "/dev/ser6";	// Default port
char 	data[MAXCHAR_RET*2];
char 	dataAlt[MAXCHAR_RET];

RHstruct RHrec;

static void usage() {
	printf("USAGE: vaisala [-p serial port] [-c command] [-t incs] [-r] [-h]\n");
	printf("       -p serial port (default /dev/ser6)\n");
	printf("       -t inc         test mode with number of increments.\n");
	printf("       -r             reset\n");
	printf("       -c command     send a Vaisala command\n");
	printf("       -h             help\n\n");
	printf("    examples:\n");
	printf("       vaisala -p /dev/ser2   runs the driver on serial port 2.\n");
	printf("       vaisala -t 10		  when the Vaisala is polling, read 10 times.\n\n");
	printf("       vaisala -c S           stop polling command send to Vaisala.\n");
	printf("       vaisala -c ?           info command send to Vaisala.\n");
	printf("       vaisala -c \"FILT ON\"   turn 15s mean filter on.\n");
	exit(0);
}


static void config_port( char *port ) {

	char 	comm[200];

	sprintf( comm, "stty baud=%d par=%s bits=%d stopb=%d<%s\n", BAUD, PAR, BITS, STOPB, port );
	if ( system ( comm ) == -1 )
		printf("config_port error: %s\n", comm);

	sprintf( comm, "stty +raw <%s\n", port );
	if ( system ( comm ) == -1 )
		printf("config_port error: %s\n", comm);

	sprintf( comm, "stty +sane -osflow -ihflow -ohflow -lkhflow <%s\n", port );
	if ( system ( comm ) == -1 )
		printf("config_port error: %s\n", comm);

}

static int open_port( ) {

	config_port( port );

	printf("opening port: %s\n", port);
	
	if ((fd = open( port , O_RDWR )) == -1) {
		perror("vaisala could not open serial port");
		exit( -1 );
	} 

	tcflush( fd, TCIOFLUSH );
	return 0;

}

static int send_command( char *msg ) {

	int bytes;

//	printf ( "strlen = %d, %s\n", strlen(msg), msg );

	tcflush( fd, TCIOFLUSH );
	bytes = write(fd, msg, strlen(msg) );
	tcdrain( fd );

	if (bytes < strlen(msg) ) {
		printf("command %s failed to send\n", msg);
		return 0;
	}

	// need a small delay before any reads
	delay(10);

	return 1;  
}

// reset will stop the data polling and resend the format string.
// once sent, the continouse polling is turned back on.
// Power to the Vaisala should be cycled for the changes to take place.
static void reset( ) {

	open_port( );
	delay(200);

	// stop sampling
	send_command( "S\r\n" );
	printf(" ** polling stoped \n");
	delay(100);

	// set filtering off (if turned on, 15s moving avg is used)
	send_command( "FILT OFF\r\n" );
	printf(" ** filtering off \n");
	delay(100);

	// set filtering off (if turned on, 15s moving avg is used)
	send_command( "FST OFF\r\n" );
	printf(" ** format state off \n");
	delay(100);

	// set format string
	send_command( "FORM 4.2 rh U5 t U3 #r #n\r\n" );
	printf(" ** Format string sent: FORM 4.2 rh U5 t U3 #r #n\n");
	delay(100);

	// turn polling on
	send_command( "SMODE RUN\r\n" );
	printf(" ** SMODE RUN sent\n" );
	delay(100);

	printf("Cycle the Vaisala's power for the reset to take ahold.\n");
	exit(0);

}

static void nullarrays() {

	int i;
	for (i=0; i<MAXCHAR_RET; i++)
		data[i] = dataAlt[i] = '\0';

}

static void NANrec() {
	
	RHrec.rh = NAN;
	RHrec.t  = NAN;

}

int checkfordata( ) {
	
	int	bytes;

	nullarrays();

	bytes = dev_read(fd, data, MAXCHAR_RET, PACKETSIZE, 0, 3, 0, 0);
	if ( bytes > 0 ) {
		if ( bytes < PACKETSIZE ) {
			delay(100);
			dev_read(fd, dataAlt, MAXCHAR_RET, PACKETSIZE, 0, 2, 0, 0);
			data[bytes] = *dataAlt;

			return parsedata();	
		}
		return parsedata();
	}

	return 0;

}

int parsedata( ) {

	char	*p;
	char	*delims = { " %'" };


	// relative humidity
	if ( (p = strtok( data, delims )) != NULL )
		RHrec.rh = atof( p );
	else
		return 0;

	// skip
	p = strtok( NULL, delims );
	
	// temperature
	if ( (p = strtok( NULL, delims )) != NULL )
		RHrec.t = atof( p );
	else
		return 0;


	return 1;

}

// Handle command line inputs
static void commandline( int argc, char ** argv ) {

	char comm[100];
	int	optltr,
		test = 0, testraw = 0, com = 0,
		inc = 0, maxinc;

	FILE *fdtest;

	while ((optltr = getopt(argc, argv, "c:p:t:T:rh")) != -1) {
		switch( optltr ) {
			case 'c':   com = 1; sprintf( comm, "%s\r\n", optarg );	break;
			case 'p': 	sprintf( port,"%s", optarg ); 				break;
			case 't': 	test = 1; maxinc = atoi( optarg );			break;
			case 'T': 	test = 1; testraw = 1; maxinc = atoi( optarg ); break;
			case 'r': 	reset();									break;
			case 'h': 	usage();									break;
			default: 	usage();
		}
	}

	// test command
	if ( test ) {
		fdtest = fopen( "vaisala.out" , "w" );
		open_port( );
		delay(2000);
		tcflush( fd, TCIOFLUSH );

		send_command( "R\r\n" );

		if ( testraw ) {
			while( inc < maxinc ) {
				if ( checkfordata( ) ) {
					inc++;
					printf("%s", data);
				}
			}
		}
		else {
			while( inc < maxinc ) {
				if ( checkfordata( ) ) {
					inc++;
					printf("RH = %4.2f %c, T = %4.2f oC\n", RHrec.rh, '%', RHrec.t );
					fprintf( fdtest, "RH = %4.2f %c, T = %4.2f oC\n", RHrec.rh, '%', RHrec.t );
				}
			}
		}

		fclose(fdtest);
		exit(0);

	}

	if ( com ) {
		open_port( );
		delay(200);
		tcflush( fd, TCIOFLUSH );
		send_command( comm );
		delay(1500);
		printf ( "command sent: %s\n", comm);
		dev_read(fd, data, MAXCHAR_RET, PACKETSIZE, 0, 2, 0, 0);
		printf("data returned: %s\n", data);
		exit(0);
	}


}


void main( int argc, char ** argv ) {

	char		*name,
				rcvMsg[RCVfromSRVR];

	int			name_id;

	send_id		colId;

	pid_t		colProxy,
				rcvPid;

	NANrec();

	if ( argc > 0 ) 
		commandline( argc, argv );

	open_port ( );
	delay(2000);
	tcflush( fd, TCIOFLUSH );


	/* attach vaisala name */
	name = nl_make_name( "vaisala", 1 );
	name_id = qnx_name_attach( 0, name );
	if ( name_id == -1 )
		nl_error( 3, "Unable to attach name %s", name );

	colId = Col_send_init( "vai", &RHrec, sizeof(RHrec) );
	colProxy = Col_set_proxy ( 13, msg_RHcol );

	Col_send( colId );

	// Main loop
	while ( rcvMsg[0] != msg_RHquit ) {

		rcvMsg[0] = msg_RHnomsg;
		rcvPid = Creceive( 0, &rcvMsg, RCVfromSRVR );

		if ( rcvPid != -1 ) {

			switch ( rcvMsg[0] ) {
	
				case msg_RHquit:
					close( fd );
					exit(0);

				case msg_RHcol:
					Col_send( colId );
					break;
			}
		}
		else {
	
			delay(200);
			checkfordata( );
		}

	}


}
