#include "globmsg.h"

#define REVEAL_NAME		"reveal"		// name of the driver when registered with QNX
#define	REVEAL_MAXDATA	100				// maximum packet size sent to the reveal driver

// messages used in uav.cmd
enum {
	msg_RVLquit = MAX_GLOBMSG,
	msg_RVLnomsg,
	msg_RVLdata,
};

int send2reveal( char *Smsg );
