#include <stdio.h>
#include <stdlib.h>
#include <sys/kernel.h>
#include <sys/name.h>
#include <sys/proxy.h>
#include <string.h>
#include <math.h>
#include <i86.h>
#include <unistd.h>
#include "globmsg.h"
#include "nortlib.h"
#include "soldrv.h"
#include "regnames.h"
#include "panthermsg.h"
#include "addresses.h"
#include "adr2000.h"
#include "o3ser.h"
#include "valves.h"
#include "vaisala.h"
#include "maycomm.h"
#include "reveal.h"
#include "commands.h"

void shutdownservers() {
	pid_t 	rs_pid;
 	char 	Smsg[5],
			Rmsg[10];

	// shutdown Omegas
	rs_pid = qnx_name_locate (0, NAME_TEMPS, 0, NULL);
	if (rs_pid != -1) {
		Smsg[0] = msgI_Quit;
		Send(rs_pid, Smsg, Rmsg, sizeof(Smsg), sizeof(Rmsg));
	}

	// shutdown smart electrometers
	rs_pid = qnx_name_locate (0, NAME_SMART, 0, NULL);
	if (rs_pid != -1) {
		Smsg[0] = msg_smartQuit;
		Send(rs_pid, Smsg, Rmsg, sizeof(Smsg), sizeof(Rmsg));
	}

	// shutdown valve server
	rs_pid = qnx_name_locate (0, NAME_VALVE, 0, NULL);
	if (rs_pid != -1) {
		Smsg[0] = msg_valveQuit;
		Send(rs_pid, Smsg, Rmsg, sizeof(Smsg), sizeof(Rmsg));
	}

	// shutdown ADR2000 board
	rs_pid = qnx_name_locate (0, NAME_ADR2000, 0, NULL);
	if (rs_pid != -1) {
		Smsg[0] = msg_adrQuit;
		Send(rs_pid, Smsg, Rmsg, sizeof(Smsg), sizeof(Rmsg));
	}

	// shutdown Ozone serial driver
	rs_pid = qnx_name_locate (0, NAME_OZONE, 0, NULL);
	if (rs_pid != -1) {
		Smsg[0] = msg_o3quit;
		Send(rs_pid, Smsg, Rmsg, sizeof(Smsg), sizeof(Rmsg));
	}

	// shutdown OzoneX serial driver
	rs_pid = qnx_name_locate (0, NAME_OZONEX, 0, NULL);
	if (rs_pid != -1) {
		Smsg[0] = msg_o3quit;
		Send(rs_pid, Smsg, Rmsg, sizeof(Smsg), sizeof(Rmsg));
	}

	// shutdown Vaisal serial driver
	rs_pid = qnx_name_locate (0, NAME_VAISALA, 0, NULL);
	if (rs_pid != -1) {
		Smsg[0] = msg_RHquit;
		Send(rs_pid, Smsg, Rmsg, sizeof(Smsg), sizeof(Rmsg));
	}

	// shutdown Maycomm TDL serial driver
	rs_pid = qnx_name_locate (0, NAME_MAYCOMM, 0, NULL);
	if (rs_pid != -1) {
		Smsg[0] = msg_TDLquit;
		Send(rs_pid, Smsg, Rmsg, sizeof(Smsg), sizeof(Rmsg));
	}

	// shutdown REVEAL ethernet driver
	rs_pid = qnx_name_locate (0, NAME_REVEAL, 0, NULL);
	if (rs_pid != -1) {
		Smsg[0] = msg_RVLquit;
		Send(rs_pid, Smsg, Rmsg, sizeof(Smsg), sizeof(Rmsg));
	}

	// shutdown NASDAT ethernet driver
	rs_pid = qnx_name_locate (0, NAME_NASDAT, 0, NULL);
	if (rs_pid != -1) {
		Smsg[0] = msg_RVLquit;
		Send(rs_pid, Smsg, Rmsg, sizeof(Smsg), sizeof(Rmsg));
	}

}

// Set an electrometers bias
int elec_bias ( int elec_num, int bias_value ) {

	pid_t	gc_pid;
	static char	GCmsg[3];
	static char Rmsg[3];
	
	GCmsg[0] = msg_smartSetBias;
	GCmsg[1] = elec_num;
	GCmsg[2] = bias_value;

	gc_pid = qnx_name_locate (0, NAME_SMART, 0, NULL);
	if (gc_pid == -1)
		return 0;

	Send(gc_pid, GCmsg, Rmsg, sizeof(GCmsg), sizeof(Rmsg));

	return 1;
} 

// Reset electrometer
int elec_reset ( int elec_num ) {

	pid_t	gc_pid;
	static char GCmsg[3];
	static char Rmsg[3];
	
	GCmsg[0] = msg_smartReset;
	GCmsg[1] = elec_num;
	GCmsg[2] = 0;

	gc_pid = qnx_name_locate (0, NAME_SMART, 0, NULL);
	if (gc_pid == -1)
		return 0;

	Send(gc_pid, GCmsg, Rmsg, sizeof(GCmsg), sizeof(Rmsg));

	return 1;

}

// Set SP1 (set point 1) on a Omega temperature controller.
void setOmegaSP1 ( int address, float valueF ) {

	unsigned char OmegaMsg[4];
	char	Rmsg[3];
	int 	value;
	pid_t 	rs_pid;

	value = floor(10*valueF);

	OmegaMsg[0] = msg_changeSp1;
	OmegaMsg[1] = address;
	OmegaMsg[2] = value>>8;
	OmegaMsg[3] = value&255;

	//printf("msg to OMEGA: value1 = %d, value2 = %d, %d\n", OmegaMsg[2], OmegaMsg[3], OmegaMsg[2]*256+OmegaMsg[3]);

	rs_pid = qnx_name_locate (0, NAME_TEMPS, 0, NULL);
	if ( rs_pid != -1 )
		Send(rs_pid, OmegaMsg, Rmsg, sizeof(OmegaMsg), sizeof(Rmsg));

}

void OmegaReset ( int address ) {

	unsigned char OmegaMsg[2];
	char	Rmsg[3];
	pid_t 	rs_pid;

	OmegaMsg[0] = msg_OmegaReset;
	OmegaMsg[1] = address;

	rs_pid = qnx_name_locate (0, NAME_TEMPS, 0, NULL);
	if ( rs_pid != -1 )
		Send(rs_pid, OmegaMsg, Rmsg, sizeof(OmegaMsg), sizeof(Rmsg));

}

// Set digital out bit on ADR2000 board
void ADRdigSet( int board, int chan, int val )  {

	unsigned char adrMsg[4];
	char	Rmsg[3];
	pid_t 	rs_pid;

	adrMsg[0] = msg_adrSetDig;
	adrMsg[1] = board;
	adrMsg[2] = chan;
	adrMsg[3] = val;

	rs_pid = qnx_name_locate (0, NAME_ADR2000, 0, NULL);
	if ( rs_pid != -1 )
		Send(rs_pid, adrMsg, Rmsg, sizeof(adrMsg), sizeof(Rmsg));

}

// Set digital to analog channel on ADR2000 board
void ADRdtoaSet( int board, int chan, float val )  {

	unsigned char adrMsg[7];
	char	Rmsg[3];
	pid_t 	rs_pid;
	int		analogunits;

	if ( val > 5.0 ) val = 5.0;
	else if ( val < 0.0 ) val = 0.0;

	analogunits = floor(( val / 5 ) * 4095);

	sprintf( adrMsg, "%c%c%c%04d\n", msg_adrSetDtoA, board, chan, analogunits );

	rs_pid = qnx_name_locate (0, NAME_ADR2000, 0, NULL);
	if ( rs_pid != -1 )
		Send(rs_pid, adrMsg, Rmsg, sizeof(adrMsg), sizeof(Rmsg));

}

void SetFlow( unsigned int board, unsigned int ch, float setpoint ) {

	float volts;

	// convert flow setpoint to volts (0 to 5V scale)
	volts = 4/150.0 * setpoint +1.01;
	
	ADRdtoaSet( board, ch, volts );

}


void SetPress( unsigned int board, unsigned int ch, float setpoint ) {

	float volts;

	// convert press setpoint to volts (0 to 5V scale)
	volts = 5.0/2070.0 * setpoint;
	
	ADRdtoaSet( board, ch, volts );

}

