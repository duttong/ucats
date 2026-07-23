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


#define BAUD			4800
#define PAR			  "even"
#define BITS			   7
#define STOPB			   1
#define MAXCHAR_RET		 100	// largest packet that can be returned
#define RCVfromSRVR        2    // max number of bytes a command from the server can be.
#define NAN				-1

int		fd;
char 	port[30] = "/dev/ser2";	// Default port
char 	buffer1[MAXCHAR_RET];
char 	buffer2[MAXCHAR_RET];
char 	data[MAXCHAR_RET];


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
		perror("o3ser could not open serial port");
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


void main( int argc, char ** argv ) {

	int i, bytes;

	open_port ( );

	delay(100);
//	send_command( "SMODE RUN\r\n" );
	delay(100);
//	send_command( "FTIME OFF\r\n" );
	delay(100);
//	send_command( "FORM \"RH=\" 4.2 rh U5 \#t \"T=\" t U3 \#r \#n\r\n" );
	delay(100);

	send_command( "S\r\n" );
	delay(100);

	for (i=0; i<100; i++) {
		bytes = dev_read(fd, data, MAXCHAR_RET, 255, 0, 4, 0, 0);
		if ( bytes > 0 )
			printf("bytes = %d,  %s\n", bytes, data);
	}


}
