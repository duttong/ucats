#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/dev.h>
#include <sys/name.h>
#include <sys/proxy.h>
#include <sys/kernel.h>
#include <math.h>
#include "nortlib.h"
#include "collect.h"
#include "reveal.h"


int		sockfd;
int		testnum = 0;
int		port = 4600;		// default port
char	ipadd[100];			// IP address
char	RVLdata[100];		// data to be sent to REVEAL

FILE *dfile;

struct sockaddr_in 	name;
struct hostent 		*hp;

static void usage() {
	printf("USAGE: reveal [-t num] [-p port] [-i IPaddress]\n");
	printf("       -p port        (default 4600)\n");
	printf("       -i IPaddress	  name or IP address of host computer\n");
	printf("       -t num		  send test data packet this many times.\n");
	printf("       -h             help\n\n");
	printf("    examples:\n");
	printf("       reveal -i 198.11.145.122\n");  
	printf("          sends data to IP address on default port\n");
	printf("       reveal -p 1533 -i 198.11.145.122\n");
	printf("          sends data to port 1533 on IP address 198.11.145.122\n\n");
	exit(0);
}


// Handle command line inputs
static void commandline( int argc, char ** argv ) {

	int	optltr;

	while ((optltr = getopt(argc, argv, "p:hi:t:")) != -1) {
		switch( optltr ) {
			case 'p': 	port = atoi(optarg); 			break;
			case 'i':	sprintf(ipadd, "%s", optarg);	break;
			case 't':	testnum = atoi(optarg);			break;
			case 'h': 	usage();						break;
			default: 	usage();
		}
	}
}

static int OpenSock( ) {

	/* Create socket on which to send. */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sockfd < 0) {
		perror("opening datagram socket");
		return 0;
	}


	/*
	 * Construct name,  with no wildcards,  of the socket  to send to.
	 *  Gethostbyname()  returns  a structure  including  the network address
	 * of the specified host.   The port number is taken from the command
	 * line.
	*/
	hp = gethostbyname(ipadd);
	if (hp == 0) {
		fprintf(stderr, "%s: unknown host\n", ipadd);
		return 0;
	}

	memcpy(&name.sin_addr, hp->h_addr, hp->h_length);
	name.sin_family = AF_INET;
	name.sin_port = htons(port);

	/*
	// for TCP stream
	if ( connect( sockfd, (struct sockaddr *)&name, sizeof(name) ) < 0 ) {
		perror("can't connect socket");
		return 0;
	}
	*/

	printf("datagram socket opened to %s on port %d\n", ipadd, port);
	return 1;

}

int SendDatatoSock ( char * buff, int len ) {

	int bytes;

//	printf("len = %d, buff = %s\n", strlen(buff), buff);

	/* Send message. */
	bytes = sendto( sockfd, buff, len, 0, (struct sockaddr *)&name, sizeof(name));
	if ( bytes < 0 ) {	
		perror("can't send datagram message");
		return 0;
	}

//	printf("%d bytes sent\n", bytes);
	return bytes;

}

void SendDatatoFile( char *buff ) {

	fprintf( dfile, "%s\n", buff );

}

main ( int argc, char ** argv ) {

	char 		*name;
	int			name_id;

	int			i;
	char		rcvMsg[REVEAL_MAXDATA];
	char		buff[REVEAL_MAXDATA];
	pid_t		rcvPid;

	if ( argc > 1 ) 
		commandline( argc, argv );
	else
		usage();

	OpenSock();
//dfile = fopen( "/home/panther/flight/src/rev.dat", "w+" );

	if ( testnum > 0 ) {
		for(i=0; i<testnum; i++) {
			sprintf( buff, "%s%3.1f\n", "O3:456.2,111.1,", 800+(float)i/10);
			SendDatatoSock ( &buff, strlen(buff) );
			delay(500);
		}
		exit(0);
	}	

	/* attach REVEAL name */
	name = nl_make_name( REVEAL_NAME, 1 );
	name_id = qnx_name_attach( 0, name );
	if ( name_id == -1 )
		nl_error( 3, "Unable to attach name %s", name );

	// Main loop
	while ( rcvMsg[0] != msg_RVLquit ) {

		for ( i=0; i<REVEAL_MAXDATA; i++ ) rcvMsg[i] = '\0';
		rcvMsg[0] = msg_RVLnomsg;
		rcvPid = Creceive( 0, &rcvMsg, sizeof(rcvMsg) );

		if ( rcvPid != -1 ) {

			switch ( rcvMsg[0] ) {
	
				case msg_RVLquit:
					close( sockfd );
					exit(0);

				case msg_RVLdata:
					Reply( rcvPid, "", 0 );
					strncpy(buff, rcvMsg+1, strlen(rcvMsg)-1 );
					SendDatatoSock( &buff, strlen(rcvMsg)-1 );
//					SendDatatoFile( &buff );
					for ( i=0; i<REVEAL_MAXDATA; i++ ) buff[i] = '\0';
					break;
			}
		}
		else {
			delay(200);
		}

	}

	close(sockfd);

}
