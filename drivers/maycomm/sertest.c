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


#define BAUD			9600
#define PAR			  "none"
#define BITS			   8
#define STOPB			   1

#define MAXCHAR_RET		 77		// largest packet that can be returned
#define RCVfromSRVR        2    // max number of bytes a command from the server can be.
#define NAN				-1

int		fd;
char 	port[30] = "/dev/ser2";	// Default port
//char 	buffer1[MAXCHAR_RET];
//char 	buffer2[MAXCHAR_RET];
char 	data[MAXCHAR_RET];


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


void main( int argc, char ** argv ) {

	int i, d, bytes;

	open_port ( );

	for (i=0; i<1000; i++) {
		for (d=0; d<MAXCHAR_RET; d++) data[d] = '\0';
		bytes = dev_read(fd, data, MAXCHAR_RET, MAXCHAR_RET, 0, 4, 0, 0);
		if ( bytes == 77 ) {
			printf("%s", data);
		}
			
	}


}
