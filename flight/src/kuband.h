#include "globmsg.h"

#define KUDATA_NAME		"kudata"		// name of the driver when registered with QNX
#define	KUDATA_MAXDATA	1024			// maximum packet size sent to the KUDATA driver

// messages used in uav.cmd
enum {
	msg_KUquit = MAX_GLOBMSG+100,
	msg_KUnomsg,
	msg_KUdata,
};

void KUformat_f(char *kuMSG, char *fmt, float val, float bad);
void KUformat_d(char *kuMSG, char *fmt, long val, long bad);
int send2kuband(char *pkt, char *kuMSG);
