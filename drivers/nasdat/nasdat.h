#include "globmsg.h"

#define NASDAT_NAME		"nasdat"		// name of the driver when registered with QNX
#define	NASDAT_MAXDATA	500			// maximum packet size sent to the NASDAT driver

// messages used in uav.cmd
enum {
	msg_RVLquit = MAX_GLOBMSG,
	msg_RVLnomsg,
	msg_RVLdata,
};

int send2nasdat( char *Smsg );
void nasdat_format_f( char *nasdatMSG, char *fmt, float val );
void nasdat_format_l( char *nasdatMSG, char *fmt, long val );
