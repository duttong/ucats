#include <stdio.h>
#include <stdlib.h>
#include <sys/kernel.h>
#include <sys/name.h>
#include <sys/proxy.h>
#include <string.h>
#include <unistd.h>
#include "regnames.h"
#include "nortlib.h"
#include "nasdat.h"

// send data to the nasdat driver
int send2nasdat( char *Smsg ) {
	pid_t 	rs_pid;
 	char 	Rmsg[5];
	char	rvl[NASDAT_MAXDATA];

	strcpy(rvl, Smsg );
	rvl[0] = msg_RVLdata;		// data message

	// find NASDAT ethernet driver
	if ((rs_pid = qnx_name_locate (0, NAME_NASDAT, 0, NULL)) == -1) {
		// can't find 
		//perror("can't locate nasdat");
		return 0;
	}

	Send(rs_pid, &rvl, &Rmsg, sizeof(rvl), sizeof(Rmsg));

	return 1;
}


// appends float value > 0, val to nasdatMSG using supplied printf format string, fmt
void nasdat_format_f( char *nasdatMSG, char *fmt, float val ) {
	char t[NASDAT_MAXDATA];

	// crudely handle bad numbers...	
	if ( val > 0 ) {
		sprintf(t, "%s,%s", nasdatMSG, fmt);
		sprintf(nasdatMSG, t, val);
	} else {
		strcat(nasdatMSG, ",nan");
	}
}

// appends float value pos or neg, val to nasdatMSG using supplied printf format string, fmt
void nasdat_format_a( char *nasdatMSG, char *fmt, float val ) {
	char t[NASDAT_MAXDATA];

	// crudely handle bad numbers...	
	if ( val > -50 ) {
		sprintf(t, "%s,%s", nasdatMSG, fmt);
		sprintf(nasdatMSG, t, val);
	} else {
		strcat(nasdatMSG, ",nan");
	}
}

// appends long int, val to nasdatMSG using supplied printf format string, fmt
void nasdat_format_l( char *nasdatMSG, char *fmt, long val ) {
	char t[NASDAT_MAXDATA];
	
	// crudely handle bad numbers...	
	if ( val >= 0 ) {
		sprintf(t, "%s,%s", nasdatMSG, fmt);
		sprintf(nasdatMSG, t, val);
	} else {
		strcat(nasdatMSG, ",nan");
	}
}
