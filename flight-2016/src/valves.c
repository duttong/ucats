#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <signal.h>
#include <process.h>
#include <math.h>
#include <sys/name.h>
#include <sys/kernel.h>
#include "valves.h"
#include "regnames.h"
#include "panthermsg.h"

FILE 	*fpGC = NULL;

int switch_gsv( int valveID, int valvePos ) {
	char 	msg[3],
			Rmsg[3];
	pid_t	valve_pid;

	msg[0] = msg_gsvSwitch;
	msg[1] = valvePos;		// valve position (1 or 2)
	msg[2] = valveID;	
	
	valve_pid = qnx_name_locate (0, NAME_VALVE, 0, NULL);

	if (valve_pid == -1) {
//		printf("unable to find valve server pid =-1 \n");
		return 1;
	}
	
	Send( valve_pid, msg, Rmsg, sizeof(msg), sizeof(Rmsg) );

	return 0;
}

int switch_ssv( int valveID, int valvePos ) {
	char 	msg[3],
			Rmsg[3];
	pid_t	valve_pid;

	msg[0] = msg_ssvSwitch;
	msg[1] = valvePos;		// valve position (1-6)
	msg[2] = valveID;		// 0, 1 or 2
	
	valve_pid = qnx_name_locate (0, NAME_VALVE, 0, NULL);

	if (valve_pid == -1) {
//		printf("unable to find valve server pid =-1 \n");
		return 1;
	}
	
	Send( valve_pid, msg, Rmsg, sizeof(msg), sizeof(Rmsg) );

	return 0;
}

