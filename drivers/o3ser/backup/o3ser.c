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

#include "o3ser.h"

#define BAUD			2400
#define PAR			  "none"
#define BITS			   8
#define STOPB			   1

#define MAXCHAR_RET		 100	// largest packet that can be returned
#define RCVfromSRVR		   2    // max number of bytes a command from the server can be.
#define NAN				  -1

int		fd;
char 	port[30] = "/dev/ser7";	// Default port
char 	buffer1[MAXCHAR_RET];
char 	buffer2[MAXCHAR_RET];
char 	data[MAXCHAR_RET];

O3struct o3rec;

static void usage() {
	printf("USAGE: o3ser [-p serial port] [-t incs] [-h]\n");
	printf("       -p serial port (default /dev/ser7)\n");
	printf("       -t inc         test mode with number of increments.\n");
	printf("       -h             help\n");
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
	
	if ((fd = open( port , O_RDWR )) == -1) {
		perror("o3ser could not open serial port");
		exit( -1 );
	} 

	tcflush( fd, TCIOFLUSH );
	return 0;

}

void zerobuffs( ) {
	int	i;

	for( i=0; i<MAXCHAR_RET; i++ ) {
		data[i] = '\0';
		buffer1[i] = '\0';
		buffer2[i] = '\0';
	}
}

void NANo3struct( ) {
	// o3rec.log = NAN;
	o3rec.o3 = NAN; 
	o3rec.t = NAN; 
	o3rec.p = NAN; 
	o3rec.date.year = NAN;
	o3rec.date.mon = NAN;
	o3rec.date.day = NAN;
	o3rec.time.hh = NAN;
	o3rec.time.min = NAN;
	o3rec.time.sec = NAN;
}

void parsebuff( ) {

	char	*p;
	char	*delims = { ",/:" };

	/* removed for simplicity
	if ( (p = strtok( data, delims )) != NULL )
		o3rec.log = atol( p );
	*/

	if ( (p = strtok( data, delims )) != NULL )
		o3rec.o3 = atof( p );
		
	// temp		
	if ( (p = strtok( NULL, delims )) != NULL )
		o3rec.t = atof( p );
	 
	// pressure
	if ( (p = strtok( NULL, delims )) != NULL )
		o3rec.p = atof( p );

	// lamp voltage
	if ( (p = strtok( NULL, delims )) != NULL )
		o3rec.lamp_v = atof( p );

	// lamp voltage standard deviation in %
	if ( (p = strtok( NULL, delims )) != NULL )
		o3rec.lamp_sd = atof( p );

	// date ( dd/mm/yy )
	if ( (p = strtok( NULL, delims )) != NULL ) {
		o3rec.date.day = atoi( p );
		p = strtok( NULL, delims );
		o3rec.date.mon = atoi( p );
		p = strtok( NULL, delims );
		o3rec.date.year = atoi( p );
	}

	// time  ( hh:min:ss )
	if ( (p = strtok( NULL, delims )) != NULL ) {
		o3rec.time.hh = atoi( p );
		p = strtok( NULL, delims );
		o3rec.time.min = atoi( p );
		p = strtok( NULL, delims );
		o3rec.time.sec = atoi( p );
	}

}


int checkfordata( int disp ) {

	int 	bytes1, bytes2;

	zerobuffs();

	bytes1 = dev_read( fd, buffer1, MAXCHAR_RET, MAXCHAR_RET, 0, 2, 0, 0);

	if ( bytes1 > 0 ) {
		delay( 1000 );
		bytes2 = dev_read( fd, buffer2, MAXCHAR_RET, MAXCHAR_RET, 0, 2, 0, 0);

		sprintf( data, "%s%s", buffer1, buffer2 );

		if ( disp == 1 ) {
			printf("\n\n%s\n", data );
		}

		parsebuff();

		if ( disp == 1 ) {
			printf( "o3 = %5.1f, T = %3.1f, P = %4.1f, lamp volt = %6.3f +/- %6.3f, %02d/%02d/%02d, %02d:%02d:%02d\n", 
				o3rec.o3, o3rec.t, o3rec.p, o3rec.lamp_v, o3rec.lamp_sd, 
				o3rec.date.day, o3rec.date.mon, o3rec.date.year,
				o3rec.time.hh, o3rec.time.min, o3rec.time.sec ); 
		}

		return 1;
	}
	
	return 0;


}

// Handle command line inputs
static void commandline( int argc, char ** argv ) {

	int	optltr,
		test = 0,
		inc, maxinc;

	while ((optltr = getopt(argc, argv, "p:t:h")) != -1) {
		switch( optltr ) {
			case 'p': 	sprintf( port,"%s", optarg ); 		break;
			case 't': 	test = 1; maxinc = atoi( optarg );	break;
			case 'h': 	usage();							break;
			default: 	usage();
		}
	}

	// test command
	if ( test == 1 ) {
		open_port( );
		inc = 0;
		while( inc < maxinc ) {
			delay(2000);
			inc += checkfordata( 1 );
		}
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

	if ( argc > 0 ) commandline( argc, argv );

	printf ( "o3ser opening port: %s\n", port);
	open_port ( );

	NANo3struct( );

	/* attach o3ser name */
	name = nl_make_name( "o3ser", 1 );
	name_id = qnx_name_attach( 0, name );
	if ( name_id == -1 )
		nl_error( 3, "Unable to attach name %s", name );

	colId = Col_send_init( "ozone", &o3rec, sizeof(o3rec) );
	colProxy = Col_set_proxy ( 10, msg_o3col );

	Col_send( colId );

	// Main loop
	while ( rcvMsg[0] != msg_o3quit ) {

		rcvMsg[0] = msg_o3nomsg;
		rcvPid = Creceive( 0, &rcvMsg, RCVfromSRVR );

		if ( rcvPid != -1 ) {

			switch ( rcvMsg[0] ) {
	
				case msg_o3quit:
					close(fd);
					exit(0);

				case msg_o3col:
					Col_send( colId );
					break;
			}
		}
		else {
	
			delay(200);
			checkfordata( 1 );
		}

	}


}
