#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <varargs.h>
#include <unistd.h>
#include <sys/dev.h>
#include <sys/name.h>
#include <sys/proxy.h>
#include <sys/kernel.h>
#include <math.h>
#include <time.h>
#include "nortlib.h"
#include "collect.h"
#include "kuband.h"

int		sockfd;
int		testnum = 0;
int		port = 4600;		// default port
char	ipadd[100];			// IP address

struct sockaddr_in 	name;
struct hostent 		*hp;


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

static void usage() {
	printf("USAGE: kuband [-t num] [-p port] [-i IPaddress]\n");
	printf("       -p port        (default 4600)\n");
	printf("       -i IPaddress	  name or IP address of host computer\n");
	printf("       -t num		  send test data packet this many times.\n");
	printf("       -h             help\n\n");
	printf("    examples:\n");
	printf("       kuband -i 198.11.145.122\n");  
	printf("          sends data to IP address on default port\n");
	printf("       kuband -p 1533 -i 198.11.145.122\n");
	printf("          sends data to port 1533 on IP address 198.11.145.122\n\n");
	exit(0);
}


static int OpenUDPSock( ) {

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

	printf("datagram socket opened to %s on port %d\n", ipadd, port);
	return 1;

}

int SendDatatoSock(char *buff) {

	int bytes;

//	printf("len = %d, buff = %s\n", strlen(buff), buff);

	/* Send message. */
	bytes = sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *)&name, sizeof(name));
	if ( bytes < 0 ) {	
		perror("can't send datagram message");
		return 0;
	}

//	printf("%d bytes sent\n", bytes);
	return bytes;

}


main ( int argc, char ** argv ) {

	char 		*name;
	int			name_id;

	int			i;
	char		rcvMsg[KUDATA_MAXDATA];
	char		buff[KUDATA_MAXDATA];
	pid_t		rcvPid;
	
	char Time[20], Date[20];
	struct tm *gm;
	time_t t;

	if ( argc > 1 ) 
		commandline( argc, argv );
	else
		usage();

	OpenUDPSock();

	if ( testnum > 0 ) {
		for(i=0; i<testnum; i++) {
			// current time
			t = time(NULL);
			gm = gmtime(&t);
			sprintf(Date, "%04d/%02d/%02d", gm->tm_year+1900, gm->tm_mon+1, gm->tm_mday);
			sprintf(Time, "%02d:%02d:%02d", gm->tm_hour, gm->tm_min, gm->tm_sec);
			sprintf(buff, "#UCATS#Date=%s,Time=%s,flow_M1=99.9\n", Date, Time);
			printf("%s", buff);
			SendDatatoSock( &buff );
			delay(1000);
		}
		exit(0);
	}	

	/* attach KUDATA name */
	name = nl_make_name( KUDATA_NAME, 1 );
	name_id = qnx_name_attach( 0, name );
	if ( name_id == -1 )
		nl_error( 3, "Unable to attach name %s", name );

	// Main loop
	while ( rcvMsg[0] != msg_KUquit ) {

		for ( i=0; i<KUDATA_MAXDATA; i++ ) rcvMsg[i] = '\0';
		rcvMsg[0] = msg_KUnomsg;
		rcvPid = Creceive( 0, &rcvMsg, sizeof(rcvMsg) );

		if ( rcvPid != -1 ) {

			switch ( rcvMsg[0] ) {
	
				case msg_KUquit:
					close( sockfd );
					exit(0);

				case msg_KUdata:
					Reply( rcvPid, "", 0 );
					strncpy(buff, rcvMsg+1, strlen(rcvMsg)-1 );
					SendDatatoSock( &buff );
					for ( i=0; i<KUDATA_MAXDATA; i++ ) buff[i] = '\0';
					break;
			}
		}
		else {
			delay(200);
		}

	}

	close(sockfd);

}
