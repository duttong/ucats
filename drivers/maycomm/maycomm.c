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

#include "maycomm.h"


#define BAUD			9600
#define PAR			  "none"
#define BITS			   8
#define STOPB			   1

#define PACKETSIZE		  77	// number of chars returned in a normal packet
#define MAXCHAR_RET		 100	// largest packet that can be returned
#define RCVfromSRVR        2    // max number of bytes a command from the server can be.
#define NAN				  -1

int		fd;
long	rec = 0;
char 	port[30] = "/dev/ser8";	// Default port
char 	data[MAXCHAR_RET*2];
char 	dataAlt[MAXCHAR_RET];

// make the TDL struct handle multiple records
TDLstruct TDL[NUM_TDL_RECS];

static void usage() {
	printf("USAGE: maycomm [-p serial port] [-t incs] [-h]\n");
	printf("       -p serial port (default /dev/ser8)\n");
	printf("       -t inc         test mode with number of increments.\n");
	printf("       -h             help\n\n");
	printf("    examples:\n");
	printf("       maycomm -p /dev/ser2   runs the driver on serial port 2.\n");
	printf("       maycomm -t 10		  when the maycomm is polling, read 10 times.\n\n");
	exit(0);
}


static void config_port( char *port ) {

	char 	comm[200];

	sprintf( comm, "stty +raw <%s\n", port );
	if ( system ( comm ) == -1 )
		printf("config_port error: %s\n", comm);

	sprintf( comm, "stty +sane -osflow -ihflow -ohflow -lkhflow <%s\n", port );
	if ( system ( comm ) == -1 )
		printf("config_port error: %s\n", comm);

	sprintf( comm, "stty baud=%d par=%s bits=%d stopb=%d<%s\n", BAUD, PAR, BITS, STOPB, port );
	if ( system ( comm ) == -1 )
		printf("config_port error: %s\n", comm);

}

static int open_port( ) {

	config_port( port );

	printf("opening port: %s\n", port);
	
	if ((fd = open( port , O_RDWR )) == -1) {
		perror("o3ser could not open serial port");
		exit( -1 );
	} 

	tcflush( fd, TCIOFLUSH );
	return 0;

}

static void nullarrays() {

	int i;
	for (i=0; i<MAXCHAR_RET; i++)
		data[i] = dataAlt[i] = '\0';

}

static void NANrecs() {
	
	int i;
	for (i=0; i<NUM_TDL_RECS; i++) {
		TDL[i].rec =	NAN;	// record number 
		
		TDL[i].p = 		NAN;
		TDL[i].t = 		NAN;
	
		TDL[i].l.h2o = 	NAN;	// long path
		TDL[i].l.amp = 	NAN;
		TDL[i].l.pow = 	NAN;
		TDL[i].l.pos = 	NAN;
		TDL[i].l.zero = NAN;
	
		TDL[i].s.h2o = 	NAN;	// short path
		TDL[i].s.amp = 	NAN;
		TDL[i].s.pow = 	NAN;
		TDL[i].s.pos = 	NAN;
		TDL[i].s.zero = NAN;
	}

}

// function rotates the recs forward, i=i+1
static void PopRecs() {
	
	int i;
	for (i=0; i<NUM_TDL_RECS-1; i++) {
		TDL[i].rec =	TDL[i+1].rec;	// record number 
		
		TDL[i].p = 		TDL[i+1].p;
		TDL[i].t = 		TDL[i+1].t;
	
		TDL[i].l.h2o = 	TDL[i+1].l.h2o;	// long path
		TDL[i].l.amp = 	TDL[i+1].l.amp;
		TDL[i].l.pow = 	TDL[i+1].l.pow;
		TDL[i].l.pos = 	TDL[i+1].l.pos;
		TDL[i].l.zero = TDL[i+1].l.zero;
	
		TDL[i].s.h2o = 	TDL[i+1].s.h2o;	// short path
		TDL[i].s.amp = 	TDL[i+1].s.amp;
		TDL[i].s.pow = 	TDL[i+1].s.pow;
		TDL[i].s.pos = 	TDL[i+1].s.pos;
		TDL[i].s.zero = TDL[i+1].s.zero;
	}
	
	TDL[NUM_TDL_RECS].rec =		NAN;	// record number 
	TDL[NUM_TDL_RECS].p = 		NAN;
	TDL[NUM_TDL_RECS].t = 		NAN;
	TDL[NUM_TDL_RECS].l.h2o = 	NAN;	// long path
	TDL[NUM_TDL_RECS].l.amp = 	NAN;
	TDL[NUM_TDL_RECS].l.pow = 	NAN;
	TDL[NUM_TDL_RECS].l.pos = 	NAN;
	TDL[NUM_TDL_RECS].l.zero = 	NAN;
	TDL[NUM_TDL_RECS].s.h2o = 	NAN;	// short path
	TDL[NUM_TDL_RECS].s.amp = 	NAN;
	TDL[NUM_TDL_RECS].s.pow = 	NAN;
	TDL[NUM_TDL_RECS].s.pos = 	NAN;
	TDL[NUM_TDL_RECS].s.zero = 	NAN;

}


int checkfordata( ) {
	
	int	bytes;

	nullarrays();

	bytes = dev_read(fd, data, MAXCHAR_RET, PACKETSIZE, 0, 4, 0, 0);
	if ( bytes > 0 ) {
		// if too small look for more data
		if ( bytes < PACKETSIZE ) {
			delay(100);
			dev_read(fd, dataAlt, MAXCHAR_RET, PACKETSIZE, 0, 3, 0, 0);
			data[bytes] = *dataAlt;
			return parsedata();	
		}
		return parsedata();
	}

	return 0;

}

int parsedata( ) {

	char	*p;
	char	*delims = { " " };
	char	buffer[MAXCHAR_RET*2];
	int		i = 0;

	strcpy(buffer, data);

	// if rec is not NAN the data hasn't been read from the TMC side yet.
	// add new data to another index.
	if ( TDL[i].rec != NAN )
		i = 1;

	if ( (p = strtok( buffer, delims )) != NULL )
		TDL[i].p = atof( p );
	else 
		return 0;
		
	p = strtok( NULL, delims );
	TDL[i].t = atof( p );

	// long path record
	p = strtok( NULL, delims );
	TDL[i].l.h2o = atof( p );
	p = strtok( NULL, delims );
	TDL[i].l.amp = atoi( p );
	p = strtok( NULL, delims );
	TDL[i].l.pow = atoi( p );
	p = strtok( NULL, delims );
	TDL[i].l.zero = atoi( p );
	p = strtok( NULL, delims );
	TDL[i].l.pos = atoi( p );


	// short path record
	p = strtok( NULL, delims );
	TDL[i].s.h2o = atof( p );
	p = strtok( NULL, delims );
	TDL[i].s.amp = atoi( p );
	p = strtok( NULL, delims );
	TDL[i].s.pow = atoi( p );
	p = strtok( NULL, delims );
	TDL[i].s.zero = atoi( p );
	p = strtok( NULL, delims );
	TDL[i].s.pos = atoi( p );

	// record number is added to TDL[i] data 
	// it is used to determine if new data has
	// been acquired.
	TDL[i].rec = rec++;

	return 1;

}

// Handle command line inputs
static void commandline( int argc, char ** argv ) {

	int	optltr,
		test = 0, 
		inc = 0,
		i = 0,
		maxinc;

	FILE *fdtest;

	while ((optltr = getopt(argc, argv, "p:t:h")) != -1) {
		switch( optltr ) {
			case 'p': 	sprintf( port,"%s", optarg ); 			break;
			case 't': 	test = 1; maxinc = atoi( optarg );		break;
			case 'h': 	usage();								break;
			default: 	usage();
		}
	}

	// test command
	if ( test ) {
		fdtest = fopen( "maycomm.out" , "w" );
		open_port( );
		delay(2000);
		tcflush( fd, TCIOFLUSH );

		while( inc < maxinc ) {
			if ( checkfordata( ) ) {
				inc++;
				printf("raw: %s", data);
				printf("Cell P: %4.1f Cell T: %4.1f, H2O L/S: %4.1f/%4.1f\n", TDL[i].p, TDL[i].t, TDL[i].l.h2o, TDL[i].s.h2o );
				printf("  LONG: 2f amp, power, zero, pos: %6u %6u %4u %3d\n", TDL[i].l.amp, TDL[i].l.pow, TDL[i].l.pos, TDL[i].l.zero );
				printf(" SHORT: 2f amp, power, zero, pos: %6u %6u %4u %3d\n\n", TDL[i].s.amp, TDL[i].s.pow, TDL[i].s.pos, TDL[i].s.zero );

				fprintf( fdtest, "raw: %s", data);
				fprintf( fdtest, "Cell P: %4.1f Cell T: %4.1f, H2O L/S: %4.1f/%4.1f\n", TDL[i].p, TDL[i].t, TDL[i].l.h2o, TDL[i].s.h2o );
				fprintf( fdtest, "  LONG: 2f amp, power, zero, pos: %6u %6u %4u %3d\n", TDL[i].l.amp, TDL[i].l.pow, TDL[i].l.pos, TDL[i].l.zero );
				fprintf( fdtest, " SHORT: 2f amp, power, zero, pos: %6u %6u %4u %3d\n\n", TDL[i].s.amp, TDL[i].s.pow, TDL[i].s.pos, TDL[i].s.zero );
				
				NANrecs();
			}
		}

		fclose(fdtest);
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

	if ( argc > 0 ) 
		commandline( argc, argv );

	open_port ( );
	delay(2000);
	tcflush( fd, TCIOFLUSH );

	NANrecs();

	/* attach maycomm name */
	name = nl_make_name( "maycomm", 1 );
	name_id = qnx_name_attach( 0, name );
	if ( name_id == -1 )
		nl_error( 3, "Unable to attach name %s", name );

	colId = Col_send_init( "tdl", &TDL, sizeof(TDL) );
	colProxy = Col_set_proxy ( 12, msg_TDLcol );

	Col_send( colId );

	// Main loop
	while ( rcvMsg[0] != msg_TDLquit ) {

		rcvMsg[0] = msg_TDLnomsg;
		rcvPid = Creceive( 0, &rcvMsg, RCVfromSRVR );

		if ( rcvPid != -1 ) {

			switch ( rcvMsg[0] ) {
	
				case msg_TDLquit:
					close( fd );
					exit(0);

				case msg_TDLcol:
					Col_send( colId );
					PopRecs();
					break;
			}
		}
		else {
	
			delay(200);
			checkfordata( );
		}

	}




}
