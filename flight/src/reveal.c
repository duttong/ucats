#include <stdio.h>
#include <stdlib.h>
#include <sys/kernel.h>
#include <sys/name.h>
#include <sys/proxy.h>
#include <string.h>
#include <unistd.h>
#include "regnames.h"
#include "nortlib.h"
#include "reveal.h"
#include "msg.h"

// send data to the reveal driver
int send2reveal( char *Smsg ) {
	pid_t 	rs_pid;
 	char 	Rmsg[5];
	char	rvl[REVEAL_MAXDATA];

	strcpy(rvl, Smsg );
	rvl[0] = msg_RVLdata;		// data message

	// find REVEAL ethernet driver
	if ((rs_pid = qnx_name_locate (0, NAME_REVEAL, 0, NULL)) == -1) {
		// can't find 
		//perror("can't locate reveal");
		return 0;
	}

//	msg( 0, "*** REVEAL:%s, %d", rvl, strlen(rvl) );

	Send(rs_pid, &rvl, &Rmsg, sizeof(rvl), sizeof(Rmsg));

	return 1;
}
