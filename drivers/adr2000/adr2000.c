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
#include "collect.h"
#include "globmsg.h"
#include "adr2000.h"

enum {
	FALSE,
	TRUE
};

//#define DEBUG           FALSE
//#define DEBUGV			TRUE

#define BAUD			9600
#define UNKNOWN 		-999
#define BAD				-9.999
#define UNDEFINED		-111
#define MAXCHAR_RET		  40	// largest packet that can be returned
#define RCVfromSRVR        7    // max number of bytes a command from the server can be.
#define RCVfromSOLD       20    // max number of bytes a command from soldrv

#define HARDWARE		"hardware.cfg"

int		fd;
char 	data[MAXCHAR_RET];
char 	port[30] = "/dev/ser4";	// Default port

ADRstruct ADRdata[NUMboards];
unsigned int ADRanalfull[NUMboards][ADchans];

static void usage() {
	printf("USAGE: adr2000 [-p serial port] [-I board ID] [-a analog chn] [-ADX] [-d DAC chn]\n");
	printf("               [-i dig in chn] [-o dig out chn] [-t text command] [-v value]\n\n");
	printf(" Options:\n");
	printf("     -p serial port    Used to select serial port (default: /dev/ser4)\n"); 
	printf("     -I board ID       Specify adr2000 board ID (default: 0)\n"); 
	printf("     -a analog chn     Used to read an analog input channel (0-5 V)\n");
	printf("     -b analog chn     Used to read an analog input channel (+/-5 V)\n");
	printf("     -A                Read all analog input channels\n");
	printf("     -d DAC chn        Set a DAC chan to value specified by option -v\n");
	printf("     -i dig in chn     Read a digital in channel\n");
	printf("     -D                Read all digital channels\n");
	printf("     -o dig out chn    Set a digital out chan to value specified by option -v\n"); 
	printf("     -t text command   Send a text command to adr2000 board\n");
	printf("     -v value          Used with -d and -o commands.  See examples.\n");
	printf("     -X                Default configuration of dig channels.  Chan 0 is set\n");
	printf("                          to digital IN and channels 1 to 7 are set to dig OUTs.\n\n");
	printf(" Examples:\n");
	printf("     adr2000 -p /dev/ser2\n");
	printf("        This will run the adr2000 driver on serial port 2.\n");
	printf("     adr2000 -I1 -a3\n");
	printf("        Read analog channel 3 on board 1.\n");
	printf("     adr2000 -d 0 -v 2.5\n");
	printf("        Set DAC channel 0 to 2.5 volts.\n");
	printf("     adr2000 -I 0 -i 3\n");
	printf("        Read digital in channel 3 on board 0.\n");
	printf("     adr2000 -o4 -v 1\n");
	printf("        Set digital out channel 4 to 1 (on).\n");
	printf("     adr2000 -I1 -t CPA11110000\n");
	printf("        Sends text command 'CPA11110000' to adr2000 board 1.\n");
	printf("     adr2000 -X\n");
	printf("        Sets adr2000 board 0 to the default digital configuration.\n");
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

	sprintf( comm, "stty baud=%d <%s\n", BAUD, port );
	if ( system ( comm ) == -1 )
		printf("config_port error: %s\n", comm);

}

static int open_port( char *port ) {

	config_port( port );	
	
	if ((fd = open( port , O_RDWR )) == -1) {
		perror("daq could not open serial port");
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

void adr2000config ( ) {
	
	int		hrdfd,
			board;
	char 	buffer[2000];
	char	comm[200];
	char	*pt;
	char	*delims = { " \n" };

	if ((hrdfd = open( HARDWARE , O_RDONLY )) == -1) {
		sprintf(comm, "Could not open %s file!\n", HARDWARE );
		perror(comm);
		return;
	} 

	if ( read(hrdfd, buffer, sizeof( buffer )) >= 2000 ) {
		sprintf(comm, "%s file is too larger (greater than 2000 bytes)\n", HARDWARE );
		perror(comm);
		exit( -1 );
	}

	// Parse
	pt = strtok( strlwr(buffer), delims );
	while ( pt != NULL ) {
		if ( strcmp( pt, "adr2000:" ) == 0 ) {
			// adr2000 variable found

			pt = strtok( NULL, delims );

			// configure an digital channels
			if ( strcmp( pt, "digconfig:" ) == 0 ) {
				board = atoi( strtok( NULL, delims ) );
				pt = strtok( NULL, delims );
				printf ("%s: digconfig, board %d, cmd = %s\n", HARDWARE, board, pt);
				DIGconfig( board, pt );
			}
			// set analog in channels to be +/- 5 volts.
			else if ( strcmp( pt, "analogfull:" ) == 0 ) {
				board = atoi( strtok( NULL, delims ) );
				pt = strtok( NULL, delims );
				printf ("%s: analogfull, board %d, ch = %d\n", HARDWARE, board, atoi(pt));
				ADRanalfull[board][atoi(pt)] = 1;
			}

		}
		pt = strtok( NULL, delims );

	}
	
	close( hrdfd );

}


// RD command (unipolar mode (0-5 VDC)
// board == address of ADR2000 board (0 to 9)
// ch == analog channel number (0 to 7)
static float ADin_RD ( int board, int ch ) {

	char 	comm[10];
	int 	bytes,
			char_ret = 5;
	float 	val;

	if ( (board < 0) || (board > 9) ) return UNKNOWN;
	if ( (ch < 0) || (ch > 7) ) return UNKNOWN;
	
	sprintf( comm, "%dRD%d\r", board, ch );

	send_command ( comm );

	if ( (bytes = dev_read(fd, data, MAXCHAR_RET, char_ret, 0, 1, 0, 0)) <= 0) {
		ADRdata[board].analog[ch] = BAD;
		return UNKNOWN;
	}

	val = (data[0]-'0')*1000 + (data[1]-'0')*100 + (data[2]-'0')*10 + (data[3]-'0');
	val = ( val / 4095 ) * 5;

	ADRdata[board].analog[ch] = val;

	return val;
	
}

// RB command (bipolar mode (-5 to 5 VDC)
// board == address of ADR2000 board (0 to 9)
// ch == analog channel number (0 to 7)
static float ADin_RB ( int board, int ch ) {

	char 	comm[10];
	int 	bytes,
			char_ret = 5;
	float 	val;

	if ( (board < 0) || (board > 9) ) return UNKNOWN;
	if ( (ch <0) || (ch > 7) ) return UNKNOWN;
	
	sprintf( comm, "%dRB%d\r", board, ch );

	send_command ( comm );

	if ( (bytes = dev_read(fd, data, MAXCHAR_RET, char_ret, 0, 1, 0, 0)) <= 0) {
		ADRdata[board].analog[ch] = BAD;
		return UNKNOWN;
	}

	val = (data[0]-'0')*1000 + (data[1]-'0')*100 + (data[2]-'0')*10 + (data[3]-'0');
	val = (( val / 4095 ) * 10) - 5;

	ADRdata[board].analog[ch] = val;

	return val;
	
}

// Function will read all of the analog channels on a single board
// will also handle +/-5 analog channels
static void ReadAnalog ( int board ) {

	// first read all channels as if they were 0-5 volts
	ADin_RDall( board );

	// now read channels that are programmed to be +/- 5 volts
	ADin_RBscan( board );

}


static void ADin_RBscan ( int board ) {

	int ch;

	for( ch=0; ch<ADchans; ch++ ) {
		if ( ADRanalfull[board][ch] == 1 )
			ADRdata[board].analog[ch] = ADin_RB( board, ch );
	}

}

// RD command (unipolar mode (0-5 VDC)
// board == address of ADR2000 board (0 to 9)
static int ADin_RDall ( int board ) {

	char 	comm[10];
	int 	bytes,
			i,
			pt,
			char_ret = 40;
	float 	val;

	if ( (board < 0) || (board > 9) ) return UNKNOWN;
	
	sprintf( comm, "%dRD\r", board );

	send_command ( comm );

	if ( (bytes = dev_read(fd, data, MAXCHAR_RET, char_ret, 0, 1, 0, 0)) <= 0) {
		for(i=0; i<ADchans; i++) {
			ADRdata[board].analog[i] = BAD;
		}
		return UNKNOWN;
	}

	// parse
	for(i=0; i<ADchans; i++) {
		pt = i*5;
		val = (data[pt]-'0')*1000 + (data[pt+1]-'0')*100 + (data[pt+2]-'0')*10 + (data[pt+3]-'0');
		val = ( val / 4095 ) * 5;
		ADRdata[board].analog[i] = val;
	}

	return 8;
	
}

// Set Analog output
static int DAset ( int board, int ch, float setpoint ) {

	int 	AD;
	char	comm[10];

	if ( setpoint > 5.0 ) setpoint = 5.0;

	AD = setpoint / 5 * 4095;

	if ( ch == 0 )
		sprintf( comm, "%dVA%04d\r", board, AD );
	else if ( ch == 1 )
		sprintf( comm, "%dVB%04d\r", board, AD );
	else
		return UNKNOWN;		

	send_command ( comm );

	// Save setpoint data
	ADRdata[board].dtoa[ch] = setpoint;

	return 1;

}

// function to configure the IN and OUT digital channels
// Example: 0CPA00110000   <-- 1 for input, 0 for output
//     board ID=0, PA5 and PA4 are configured for input
static void DIGconfig( int board, char *setstr ) {

	char comm[20];

	if ( strlen( setstr ) != 8 ) return;

	sprintf( comm, "%dCPA%s\r", board, setstr );

	send_command( comm );

}

// Read digital in channel
static int DIGin( int board, int ch ) {

	char 	comm[10];
	int 	bytes,
			bit;

	if ( (board < 0) || (board > 9) ) return UNKNOWN;
	if ( (ch <0) || (ch > 7) ) return UNKNOWN;

	sprintf( comm, "%dRPA%d\r", board, ch );
	
	send_command( comm );

	if ( (bytes = dev_read(fd, data, MAXCHAR_RET, 1, 0, 1, 0, 0)) <= 0) {
		ADRdata[board].dig[ch] = -1;
		return UNKNOWN;
	}
	
	bit = (data[0] - '0');

	ADRdata[board].dig[ch] = bit;

	return bit;
}


// Read all digital channels.  If a channel is set to a dig out, the read is
// what the channel was set to previously.
static int DIGinAll( int board ) {

	char 	comm[10];
	int 	bytes,
			ch,
			bit;

	if ( (board < 0) || (board > 9) ) return UNKNOWN;

	sprintf( comm, "%dRPA\r", board );
	
	send_command( comm );

	if ( (bytes = dev_read(fd, data, MAXCHAR_RET, 16, 0, 1, 0, 0)) <= 0) {
		for ( ch=0; ch<DIGchans; ch++ ) {
			ADRdata[board].dig[ch] = -1;
		}
		return UNKNOWN;
	}
	
	for ( ch=0; ch<DIGchans; ch++ ) {
		bit = (data[ch*2] - '0');
		ADRdata[board].dig[7-ch] = bit;
	}

	return 8;
}


// Function to set a digital out bit
// Channel must be configured as "out" channel in order for this function 
//  to work.
static void DIGout( int board, int ch, int bit ) {

	unsigned char comm[10];

	if ( bit == 0 )
		sprintf( comm, "%dRESPA%d\r", board, ch );
	else 
		sprintf( comm, "%dSETPA%d\r", board, ch );

	send_command( comm );

	// set the bit value in the ADRdata[].dig[] array
	ADRdata[board].dig[ch] = bit;

}

// Function to set a digital bit.  This function is called by soldrv.
// The hundreds place is for on and off.
// The tens place is adr2000 board number.
// The ones place is channel number.
// Example: 123 is to turn chan 3 of board ID 2 on.
//           23 is to turn chan 3 of board ID 2 off.
static void scdcDIGout( int add ) {

	int 	bit = 0,
			chan,
			board;

	chan = add % 10; 
	board = ((add % 100) - chan) / 10;
	if ( add >= 100 ) bit = 1;

	if ( chan > DIGchans ) return;
	else if ( board > NUMboards ) return;
	else if ( bit > 1 ) return;

	DIGout( board, chan, bit );

}

static void scdcMultDIGout( unsigned char *cmd ) {
	int n = *++cmd;
	
	while ( n-- > 0 ) {
		scdcDIGout( *++cmd );
	}

}


// Handle command line inputs
static void commandline( int argc, char ** argv ) {

	int 	text = 0, 
			aorb = 0,
			optltr,
			boardID = 0,
			baseconfig = 0,
			ach = UNDEFINED,
			dch = UNDEFINED,
			ich = UNDEFINED,
			och = UNDEFINED;
	float	val;
	char 	comm[10];

	while ((optltr = getopt(argc, argv, "I:a:b:v:d:i:o:t:p:ADX")) != -1) {
		switch( optltr ) {
			case 'I': boardID = atoi(optarg);
				break;
			case 'a': ach = atoi(optarg); aorb = 0;
				break;
			case 'b': ach = atoi(optarg); aorb = 1;
				break;
			case 'A': ach = 200;
				break;
			case 'd': dch = atoi(optarg);
				break;
			case 'D': ich = 200;
				break;
			case 'i': ich = atoi(optarg);
				break;
			case 'o': och = atoi(optarg);
				break;
			case 'v': val = atof(optarg);
				break;
			case 't': text = 1;
				sprintf( comm, "%s\r", optarg );
				break;
			case 'p': sprintf( port,"%s", optarg );
				break;
			case 'X': baseconfig = 1;
				break;
			default:
				usage();
		}
	}

	// TEXT COMMAND
	if ( text == 1 ) {
		open_port( port );
		send_command( comm );
		delay(100);
		dev_read(fd, data, MAXCHAR_RET, 40, 0, 1, 0, 0);
		printf("command: %s\ndata: %s\n", comm, data );
		exit(0);
	}
	
	// ANALOG DATA
	else if ( ach == 200 ) {
		open_port( port );
		ADin_RDall( boardID );
		printf("board ID=%d, All Analog Channels: \n   0:%0.3f, 1:%0.3f, 2:%0.3f, 3:%0.3f, 4:%0.3f, 5:%0.3f, 6:%0.3f, 7:%0.3f volts.\n",
			boardID, ADRdata[boardID].analog[0], ADRdata[boardID].analog[1], ADRdata[boardID].analog[2], ADRdata[boardID].analog[3],
			ADRdata[boardID].analog[4], ADRdata[boardID].analog[5], ADRdata[boardID].analog[6], ADRdata[boardID].analog[7]);
		exit(0);
	}
	else if ( ach != UNDEFINED ) {
		open_port( port );
		if ( aorb == 0 )
			printf("board ID=%d, Analog IN ch %d = %0.3f volts (0-5 V scale).\n", boardID,
				ach, ADin_RD( boardID, ach ) );
		else
			printf("board ID=%d, Analog IN ch %d = %0.3f volts ( +/- 5 V scale).\n", boardID,
				ach, ADin_RB( boardID, ach ) );
		exit(0);
	} 

	// DIGITAL TO ANALOG
	else if ( dch != UNDEFINED ) {
		open_port( port );
		DAset( boardID, dch, val );
		printf("board ID=%d, DtoA ch %d set to %0.3f volts.\n", boardID, dch, val );
		exit(0);
	}

	// DIGITAL
	else if ( ich == 200 ) {
		open_port( port );
		DIGinAll ( boardID );
		printf("board ID=%d, All Digital Channels: \n   ch 0:%1d, ch 1:%1d, ch 2:%1d, ch 3:%1d, ch 4:%1d, ch 5:%1d, ch 6:%1d, ch 7:%1d\n",
			boardID, ADRdata[boardID].dig[0], ADRdata[boardID].dig[1], ADRdata[boardID].dig[2], ADRdata[boardID].dig[3],
			ADRdata[boardID].dig[4], ADRdata[boardID].dig[5], ADRdata[boardID].dig[6], ADRdata[boardID].dig[7]);
		exit(0);
	}
	else if ( ich != UNDEFINED ) {
		open_port( port );
		printf( "board ID=%d, DIG In %d = %d\n", boardID, ich, DIGin( boardID, ich ));
		exit(0);
	}
	else if ( och != UNDEFINED ) {
		open_port( port );
		DIGout( boardID, och, (int) val );
		exit(0);
	}
	else if ( baseconfig == 1 ) {
		open_port( port );
		DIGconfig( boardID, "00000001");
		exit(0);
	}
	else
		return;

}


void main( int argc, char ** argv ) {

	int			boardInc = 0,
				count,
				boardnum,
				channum,
				intval,
				adrname_id, scname_id,
				i, j;

	char		*name,
				rcvMsg[RCVfromSOLD];

	pid_t		rcvPid,
				colProxy;
			
	send_id		colId;

	// a little initialization
	for (i=0; i<NUMboards; i++ )  {
		for (j=0; j<DAchans; j++ )
			ADRdata[i].dtoa[j] = BAD;
		for (j=0; j<ADchans; j++ )
			ADRanalfull[i][j] = 0;
	}

	if ( argc > 0 ) commandline( argc, argv );

	open_port ( port );

	adr2000config();

	/* attach adr2000 name */
	name = nl_make_name( ADR2000_NAME, 1 );
	adrname_id = qnx_name_attach( 0, name );
	if ( adrname_id == -1 )
		nl_error( 3, "Unable to attach name %s", name );

	/* attach scdc name */
	name = nl_make_name( "scdc", 0 );
	scname_id = qnx_name_attach( 0, name );
	if ( scname_id == -1 )
		nl_error( 1, "Unable to attach name %s", name );

	// All code below is for communications to data collection.
#ifndef DEBUG
	colId = Col_send_init ( ADR2000_NAME, &ADRdata, sizeof(ADRdata) );
	colProxy = Col_set_proxy ( ADR2000_PROXY_NUM, msg_adrRetAll );

	Col_send( colId );
#endif

	// Main loop
	while ( rcvMsg[0] != msg_adrQuit ) {

		if ( boardInc >= NUMboards ) boardInc = 0;
		if ( count >= 2 ) count = 0;

		rcvMsg[0] = msg_adrNoMsg;
		rcvPid = Creceive( 0, &rcvMsg, RCVfromSOLD );

		if ( rcvPid != -1 ) {

			switch ( rcvMsg[0] ) {

				case DASCMD:
					reply_byte( rcvPid, REP_OK );
					scdcDIGout( rcvMsg[2] );
					Col_send( colId );
					break;

				case SC_MULTCMD:
					reply_byte( rcvPid, REP_OK );
					scdcMultDIGout( rcvMsg );
					Col_send( colId );
					break;

				case msg_adrNoMsg:
					reply_byte( rcvPid, REP_OK );
					break;

				case msg_adrQuit:
					reply_byte( rcvPid, REP_OK );
					break;
				
				case msg_adrRetAll:
					Col_send( colId );
					break;

				case msg_adrSetDig:
					Reply( rcvPid, "", 0 );
					DIGout( rcvMsg[1], rcvMsg[2], rcvMsg[3] );
					Col_send( colId );
					break;

				case msg_adrSetDtoA:
					Reply( rcvPid, "", 0 );
					boardnum = rcvMsg[1];
					channum = rcvMsg[2];
					intval = (rcvMsg[3]-'0')*1000 + (rcvMsg[4]-'0')*100 + (rcvMsg[5]-'0')*10 + (rcvMsg[6]-'0');
					DAset( boardnum, channum, (intval/4095.0)*5.0 );
					Col_send( colId );
					break;

				default:
					Reply( rcvPid, "", 0 );
					break;

			}

		} 
		else {

			if ( count == 0 ) {
				ReadAnalog( boardInc );
#ifdef DEBUGV
				printf("board ID=%d, All Analog Channels: \n   0:%0.3f, 1:%0.3f, 2:%0.3f, 3:%0.3f, 4:%0.3f, 5:%0.3f, 6:%0.3f, 7:%0.3f volts.\n",
				boardInc, ADRdata[boardInc].analog[0], ADRdata[boardInc].analog[1], ADRdata[boardInc].analog[2], ADRdata[boardInc].analog[3],
				ADRdata[boardInc].analog[4], ADRdata[boardInc].analog[5], ADRdata[boardInc].analog[6], ADRdata[boardInc].analog[7]);
#endif
			} else {
				DIGinAll( boardInc );
#ifdef DEBUGV
				printf("board ID=%d, All Digital Channels: \n   ch 0:%1d, ch 1:%1d, ch 2:%1d, ch 3:%1d, ch 4:%1d, ch 5:%1d, ch 6:%1d, ch 7:%1d\n",
				boardInc, ADRdata[boardInc].dig[0], ADRdata[boardInc].dig[1], ADRdata[boardInc].dig[2], ADRdata[boardInc].dig[3],
				ADRdata[boardInc].dig[4], ADRdata[boardInc].dig[5], ADRdata[boardInc].dig[6], ADRdata[boardInc].dig[7]);
#endif
			}

			delay(50);  // slow it down a bit
			
			count++;
			if ( count == 1 ) boardInc++;
		}		

	}

	qnx_name_detach( 0, adrname_id );
	if ( scname_id != -1 )
		qnx_name_detach( 0, scname_id );

}

