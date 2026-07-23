#include <unistd.h>
#include <fcntl.h>
#include <sys/dev.h>
#include <sys/name.h>
#include <sys/proxy.h>
#include <sys/kernel.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <termios.h>
#include "nortlib.h"
#include "collect.h"
#include "panthermsg.h"

#define BAUD			9600
#define MAXVALVES 		10			// addresses 0 to 9
#define RCV_MSG_SIZE    256
#define RCVMSGSIZE		5
#define COMMSIZE		10			// Size of command buffer

char port[30] = "/dev/ser3";		// default port for PANTHER
char comm[COMMSIZE];				// command sent to serial port 
char buffer[2000];					// Data read from serial port 
int fd;

void init_opt(int argc, char ** argv) {
	int optltr,
		i;
	
	while ((optltr = getopt(argc, argv, "p:c:h")) != -1) {
		switch( optltr ) {
			case 'p': 
				sprintf(port, "%s", optarg );
				break;
			case 'c': 
				open_port();
				sprintf(comm, "%s\n", optarg );
				dev_read(fd, buffer, 2000, 0, 0, 0, 0, 0);
				for(i=0; i<2000; i++) buffer[i] = '\0';
				send_command();
				dev_read(fd, buffer, 2000, 2000, 0, 5, 0, 0);
				printf("%s\n", buffer);
				exit(0);
				break;
			case 'h': 
				usage();
				break;
			default:
				usage();
		}
	}
}

void usage() {
	printf("USAGE: valco [-p device] [-c command]\n\n");
	printf("  Examples: \n");
	printf("  Run as a valve driver for PANTHER on /dev/ser1 port.\n");
	printf("      valco -p /dev/ser1 \n\n");
	printf("  Run a single command on /dev/ser2 the quit. \n");
	printf("      valco -p /dev/ser2 -c 3go1 \n\n");
	printf("  Run as a valve driver of PANTHER on default port /dev/ser3. \n");
	printf("      valco \n\n");
	exit(0);
}

void config_port( char *port ) {

	char 	comm[200];

	sprintf( comm, "stty +raw <%s\n", port );
	if ( system ( comm ) == -1 )
		printf("config_port error: %s\n", comm);

	sprintf( comm, "stty +sane -osflow -ihflow -ohflow -lkhflow <%s\n", port );
	if ( system ( comm ) == -1 )
		printf("config_port error: %s\n", comm);

	sprintf( comm, "stty baud=%d <%s\n", BAUD, port );
	if ( system ( comm ) == -1 )
		printf("config_port error: %s\n", comm);

}

void open_port() {

	config_port( port );

	printf("program valco: trying serial port: %s\n", port);
	if ((fd = open( port , O_RDWR )) == -1) {
		perror("valco could not open serial port");
		exit(0);
	}

	tcflush( fd, TCIOFLUSH );

}

int send_command() {

	int char_out;

	char_out = write(fd, comm, strlen(comm));
	printf("comm = %s", comm);

	tcdrain( fd );

	if (char_out != strlen(comm)) {
		perror("send_command: Failed to send all data to port.");
		printf("  sending command %s, char_out = %d, ERROR num = %d\n", comm, char_out, errno);
	}

	return char_out;
}

// Call to read either GSVs or SSVs
// valve_id is from 0 to 9.
// addresses 0, 1, and 2 are for multi-port valves (SSVs)
int read_valve_pos(int valve_id) {
	int cp;

	if (valve_id <= 2)
		cp = read_valve_posSSV( valve_id );
	else
		cp = read_valve_posGSV( valve_id );

	return (cp);

}


int read_valve_posSSV(int valve_id ) {

	char 	*pt;
	int 	i,
//			bytes,
			NUMRET = 40; 	// NUMRET is calculated from return of: 1 Position =  4
	
	// Clear port and buffer
	tcflush( fd, TCIOFLUSH );
	for(i=0; i<RCV_MSG_SIZE; i++) 
		buffer[i] = '\0';
	
	// Build up valve CP (current position) command and send it
	for( i=0; i<COMMSIZE; i++ ) 
		comm[i] = '\0';
	sprintf(comm, "%dCP\n", valve_id);
	send_command();
	
	if ( dev_read(fd, buffer, RCV_MSG_SIZE, NUMRET, 0, 2, 0, 0) <= 0 )
		return 0;		

//	printf(" returned command is %s \n", buffer);

	// The SSV position is the number after the = sign.
	if ((pt = strstr(buffer, "=")) == NULL)
		return 0;
	else
		return atoi(++pt);

}


int read_valve_posGSV(int valve_id) {

	char 	*pt, pos[20];
	int 	i,
//			bytes,
			NUMRET = 40;	// NUMRET is calculated from return of: 3 Position is "A"
	
	// Clear port and buffer
	tcflush( fd, TCIOFLUSH );
	for(i=0; i<RCV_MSG_SIZE; i++)
		buffer[i] = '\0';
	
	// Build up valve CP command and send it
	for( i=0; i<COMMSIZE; i++ ) 
		comm[i] = '\0';
	sprintf(comm, "%dCP\n", valve_id);
	send_command();
	
	if ( dev_read(fd, buffer, RCV_MSG_SIZE, NUMRET, 0, 2, 0, 0) <= 0 )
		return 3;		

//	printf(" returned command is %s \n", buffer);
	
	// The GSVs return something like.... 1 Position is "A"
	if ( (pt = strstr(buffer, "\"")) == NULL )
		return 3;		// error handled in bittxt.tmc
	else {
		sprintf(pos,"%s", pt);
		if (pos[1] == 'A')
			return 1;
		else {
			if (pos[1] == 'B')
				return 2;
			else
				return 3;
		}
	}

}



int switch_multi_valve(int position, int valve_id) {

	int i;

	for( i=0; i<COMMSIZE; i++ ) comm[i] = '\0';

	sprintf(comm, "%dGO%d\n", valve_id, position);
//	sprintf(comm, "%dCW%d\n", valve_id, position);

	send_command();

	return position;

}


int switch_valve(int position, int valve_id) {

	int i;

	for( i=0; i<COMMSIZE; i++ ) comm[i] = '\0';

	if (position == 1)
		sprintf(comm, "%dGOA\n", valve_id);
	else
		sprintf(comm, "%dGOB\n", valve_id);

	send_command();

	return position;

}


void main(int argc, char ** argv) {
	int 		index,
				valveInc = 0,
				loop,
				serverNameId;

	int  		valvePos[MAXVALVES];

	char		rcvMsg[RCVMSGSIZE];
	char		*name;

	pid_t		rcvPid,
				colProxy;

	send_id		colId;
	
	// get commands from the command line 
	init_opt(argc, argv);

	open_port();

	// attach valve driver name 
	name = nl_make_name( "valco", 1 );
	serverNameId = qnx_name_attach( 0, name );
	if ( serverNameId == -1 )
		nl_error( 3, "Unable to attach name %s", name );

	// Initialize valvePos array
	for(index=0; index < MAXVALVES; index++) {
		if (index <= 2 )			// SSVs
			valvePos[index] = 0;
		else						// GSVs
			valvePos[index] = 3;
	}

	colId = Col_send_init("valvePos", &valvePos, sizeof(valvePos) );
	colProxy = Col_set_proxy( 4, msg_valveId );

	Col_send( colId );

	// Main loop
	while ( 1 ) {
		
		rcvMsg[0] = msg_valvenoMsg;
		rcvPid = Creceive(0, &rcvMsg, RCVMSGSIZE);

		if ( rcvPid != -1 ) {


			switch ( rcvMsg[0] ) {

				case msg_valveQuit:
					close(fd);
					exit(0);
		
				case msg_ssvSwitch:
					Reply(rcvPid, "", 0);
					valvePos[rcvMsg[2]] = rcvMsg[1];
					switch_multi_valve( rcvMsg[1], rcvMsg[2] );
					Col_send( colId );
					break;

				case msg_gsvSwitch:
					Reply(rcvPid, "", 0);
					valvePos[rcvMsg[2]] = rcvMsg[1];
					switch_valve( rcvMsg[1], rcvMsg[2] );
					Col_send(colId);
					break;

				case msg_valveId:
					Col_send( colId );
					break;

				case msg_valvenoMsg:
					break;
			}

		} else {

			// the loop variable is used to slow down the polling 
			// of the valves.
			if ( loop > 5 ) loop = 0;

			// Read the next valve position
			if ( loop == 1 ) {
				delay(10);
				if ( valveInc == MAXVALVES ) valveInc = 0;
				valvePos[valveInc] = read_valve_pos( valveInc );
				valveInc++;
			} else {
				delay(50);
			}
			loop++;
		}
	}

}
