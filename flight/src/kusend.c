#include <stdio.h>
#include <stdlib.h>
#include <sys/kernel.h>
#include <sys/name.h>
#include <sys/proxy.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "regnames.h"
#include "nortlib.h"
#include "kuband.h"

#define BADDATA	"nan"
#define MAX_FMT	25			// max length of variable name and fmt string

// adds date and time to KuMSG packet and sends to UDP driver
// original function used before the SABRE mission
int send2kuband_org(char *pkt, char *kuMSG) {

	char Time[20], Date[20], Rmsg[5];
	char msg[KUDATA_MAXDATA];
	struct tm *gm;
	time_t t;
	pid_t 	rs_pid;
	
	// current time
	t = time(NULL);
	gm = gmtime(&t);
	
	sprintf(Date, "%04d/%02d/%02d", gm->tm_year+1900, gm->tm_mon+1, gm->tm_mday);
	sprintf(Time, "%02d:%02d:%02d", gm->tm_hour, gm->tm_min, gm->tm_sec);
	sprintf(msg, "x#UCATS_%s#Date=%s,Time=%s%s", pkt, Date, Time, kuMSG);

	removeSpaces(&msg);

	msg[0] = msg_KUdata;		// data message

	// find KUDATA ethernet driver
	if ((rs_pid = qnx_name_locate (0, NAME_KUDATA, 0, NULL)) == -1) {
		// can't find 
		//perror("can't locate kudata");
		return 0;
	}

	Send(rs_pid, &msg, &Rmsg, sizeof(msg), sizeof(Rmsg));

	return 1;
	
}

// adds date and time to KuMSG packet and sends to UDP driver
int send2kuband(char *pkt, char *kuMSG) {

	char dt[20], Rmsg[5];
	char msg[KUDATA_MAXDATA];
	struct tm *gm;
	time_t t;
	pid_t 	rs_pid;
	
	// current time
	t = time(NULL);
	gm = gmtime(&t);
	
	sprintf(dt, "%04d%02d%02dT%02d%02d%02d", gm->tm_year+1900, gm->tm_mon+1, gm->tm_mday, gm->tm_hour, gm->tm_min, gm->tm_sec);
	sprintf(msg, "x#UC%s#%s%s", pkt, dt, kuMSG);

	removeSpaces(&msg);

	msg[0] = msg_KUdata;		// data message

	// find KUDATA ethernet driver
	if ((rs_pid = qnx_name_locate (0, NAME_KUDATA, 0, NULL)) == -1) {
		// can't find 
		//perror("can't locate kudata");
		return 0;
	}

	Send(rs_pid, &msg, &Rmsg, sizeof(msg), sizeof(Rmsg));

	return 1;
	
}


// inserts BADDATA string into kuMSG 
// original function 230111
/*
static void BadData_org(char *kuMSG, char *fmt) {
	int i;
	char tmp[MAX_FMT];
	
	strcpy(tmp, fmt);	
	strcat(kuMSG, ",");
	
	for(i=0; i<strlen(tmp); i++) {
		if (tmp[i] == '=') {
			tmp[i+1] = '\0';
			break;
		}
	}
	strcat(kuMSG, tmp);
	strcat(kuMSG, BADDATA);	
}
*/

// simple append nan
static void BadData(char *kuMSG, char *fmt) {
	
	strcat(kuMSG, ",");
	strcat(kuMSG, BADDATA);	
}

// appends float value > bad, val to kuMSG using supplied printf format string, fmt
void KUformat_f(char *kuMSG, char *fmt, float val, float bad) {
	char tmp[MAX_FMT];
	
	// crudely handle bad numbers...	
	if ( val > bad ) {
		sprintf(tmp, fmt, val);
		strcat(kuMSG, ",");
		strcat(kuMSG, tmp);
	} else {
		BadData(kuMSG, fmt);
	}
}

// appends long value > 0, val to kuMSG using supplied printf format string, fmt
void KUformat_d(char *kuMSG, char *fmt, long val, long bad) {
	char tmp[MAX_FMT];

	// crudely handle bad numbers...	
	if ( val > bad ) {
		sprintf(tmp, fmt, val);
		strcat(kuMSG, ",");
		strcat(kuMSG, tmp);
	} else {
		BadData(kuMSG, fmt);
	}
}

// from:
// http://stackoverflow.com/questions/3090316/remove-blank-spaces-in-a-string-in-on
static void removeSpaces(char *str) {
    // Set up two pointers.

    char *src = str;
    char *dst = src;

    // Process all characters to end of string.
    while (*src != '\0') {
        // If it's not a space, transfer and increment destination.

        if (*src != ' ')
            *dst++ = *src;

        // Increment source no matter what.
        src++;
    }

    // Terminate the new string.
    *dst = '\0';
}

