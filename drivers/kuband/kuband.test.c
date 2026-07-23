#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <varargs.h>
#include <unistd.h>
#include <sys/dev.h>
#include <sys/name.h>
#include <sys/proxy.h>
#include <sys/kernel.h>
#include <math.h>
#include <time.h>
#include "kuband.h"

#define	KU_MAXDATA	2048
#define BADDATA	"nan"

char	kuMSG[KU_MAXDATA];

int		sockfd;
int		testnum = 0;
int		port = 4600;		// default port
char	ipadd[100];			// IP address

struct sockaddr_in 	name;
struct hostent 		*hp;


// test code
//long Time = 1;
float flow_M1 = 40.1;
float flow_M1_sp = 70.0;
float flow_BF1 = 0.1;
float flow_BF1_sp = 40.0;
float pres_BP1 = 80.1;
float pres_BP1_sp = 80;
float pres_SL = 40.1;
float temp_gasB_N = 40.1;
float temp_SL1 = 40.1;
float temp_gasB_C = 40.1;
float flow_SL = 40.1;
float flow_M2 = 40.1;
float flow_M2_sp = 40.1;
float flow_BF2 = 40.1;
float flow_BF2_sp = 40.1;
float pres_PUMP = 40.1;
float pres_BP2_sp = 40.1;
float pres_ECD2 = 40.1;
float ecdA_CH1 = 40.1;
float ecdA_CH2 = 40.1;
float temp_pump = 40.1;
float temp_SL2 = 40.1;
float temp_amb = 40.1;
float pres_extern = 40.1;
float volt_1234 = 40.1;
float presL_dope = 40.1;
float presL_cal = 40.1;
float presL_N2 = 40.1;
float presH_123 = 40.1;
float volt_5 = 40.132;
float volt_15 = 40.231;
float volt_28 = 40.122;
float CH2_ECD = 40.1;
float CH2_Col = 40.1;
float CH2_Post = 40.1;
float CH1_ECD = 40.1;
float CH1_Col = 40.1;
int GCstate = 1;
int ssv = 2;
int valv_calSSV = 0;
long tdlrec = 2322;
float tdlP = 40.1;
float tdlT = 40.1;
float tdlsH2O = 40.1;
float tdllH2O = 40.1;
float tdlsAmp = 40.1;
float tdlsPow = 40.1;
float tdlsPos = 40.1;
float tdlsZer = 40.1;
float tdllAmp = 40.1;
float tdllPow = 40.1;
float tdllPos = 40.1;
float tdllZer = 40.1;
float tdlbH2O = 40.1;
float H2O_Pelt = 25.0;
float o3 = 40.1;
float o3temp = 40.1;
float o3pres = 40.1;
float o3best = 40.1;
float o3lmpv = 40.1;
float o3lmpsd = 40.1;


// Handle command line inputs
static void commandline( int argc, char ** argv ) {

	int	optltr;

	while ((optltr = getopt(argc, argv, "p:hi:t:")) != -1) {
		switch( optltr ) {
			case 'p': 	port = atoi(optarg); 			break;
			case 'i':	sprintf(ipadd, "%s", optarg);	break;
			case 't':	testnum = atoi(optarg);			break;
			case 'h': 	usage();						break;
			default: 	usage();
		}
	}
}

static void usage() {
	printf("USAGE: kuband [-t num] [-p port] [-i IPaddress]\n");
	printf("       -p port        (default 4600)\n");
	printf("       -i IPaddress	  name or IP address of host computer\n");
	printf("       -t num		  send test data packet this many times.\n");
	printf("       -h             help\n\n");
	printf("    examples:\n");
	printf("       kuband -i 198.11.145.122\n");  
	printf("          sends data to IP address on default port\n");
	printf("       kuband -p 1533 -i 198.11.145.122\n");
	printf("          sends data to port 1533 on IP address 198.11.145.122\n\n");
	exit(0);
}


static int OpenSock( ) {

	/* Create socket on which to send. */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sockfd < 0) {
		perror("opening datagram socket");
		return 0;
	}
	
	
	/*  for broadcast
	if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval)) <0) {
		perror("setsockopt SO_REUSEADDR");
		return(0);
	}
	if (setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&optval,sizeof(optval)) <0) {
		perror("setsockopt SO_BROADCAST");
		return(0);
	}
	*/


	/*
	 * Construct name,  with no wildcards,  of the socket  to send to.
	 *  Gethostbyname()  returns  a structure  including  the network address
	 * of the specified host.   The port number is taken from the command
	 * line.
	*/
	hp = gethostbyname(ipadd);
	if (hp == 0) {
		fprintf(stderr, "%s: unknown host\n", ipadd);
		return 0;
	}

	memcpy(&name.sin_addr, hp->h_addr, hp->h_length);
	name.sin_family = AF_INET;
	name.sin_port = htons(port);

	/*
	// for TCP stream
	if ( connect( sockfd, (struct sockaddr *)&name, sizeof(name) ) < 0 ) {
		perror("can't connect socket");
		return 0;
	}
	*/

	printf("datagram socket opened to %s on port %d\n", ipadd, port);
	return 1;

}

int SendDatatoSock() {

	int bytes;

//	printf("len = %d, buff = %s\n", strlen(buff), buff);

	/* Send message. */
	bytes = sendto(sockfd, kuMSG, strlen(kuMSG), 0, (struct sockaddr *)&name, sizeof(name));
	if ( bytes < 0 ) {	
		perror("can't send datagram message");
		return 0;
	}

//	printf("%d bytes sent\n", bytes);
	return bytes;

}


// used to incremant data //
void testcode(int inc) {

	int sign = inc-(inc/2*2);
	if (sign == 0) sign = -1;

	//Time += 1;
	flow_M1 += sign*rand()/(float)RAND_MAX;
	flow_BF1 += sign*rand()/(float)RAND_MAX;
	pres_BP1 += sign*rand()/(float)RAND_MAX;
	pres_SL += sign*rand()/(float)RAND_MAX;
	temp_gasB_N += sign*rand()/(float)RAND_MAX;
	temp_SL1 += sign*rand()/(float)RAND_MAX;
	temp_gasB_C += sign*rand()/(float)RAND_MAX;
	flow_SL += sign*rand()/(float)RAND_MAX;
	flow_M2 += sign*rand()/(float)RAND_MAX;
	flow_BF2 += sign*rand()/(float)RAND_MAX;
	

}

// from:
// http://stackoverflow.com/questions/3090316/remove-blank-spaces-in-a-string-in-on
static void removeSpaces (char *str) {
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


void genKUpacket() {

	char Time[20], Date[20];
	struct tm *gm;
	time_t t;
	
	// current time
	t = time(NULL);
	gm = gmtime(&t);
	
	sprintf(Date, "%04d/%02d/%02d", gm->tm_year+1900, gm->tm_mon+1, gm->tm_mday);
	sprintf(Time, "%02d:%02d:%02d", gm->tm_hour, gm->tm_min, gm->tm_sec);

	sprintf(kuMSG, "#UCATS#Date=%s,Time=%s", Date, Time);
	format_f("flow_M1=%6.1f", flow_M1, 0);
	format_f("flow_M1_sp=%6.1f", flow_M1_sp, 0);
	format_f("flow_BF1=%6.1f", flow_BF1, 0);
	format_f("flow_BF1_sp=%6.1f", flow_BF1_sp, 0);
	format_f("pres_BP1=%6.1f", pres_BP1, 0);
	format_f("pres_BP1_sp=%6.1f", pres_BP1_sp, 0);
	format_f("pres_SL=%6.1f", pres_SL, 0);
	format_f("temp_gasB_N=%6.1f", temp_gasB_N, 0);
	format_f("temp_SL1=%6.1f", temp_SL1, 0);
	format_f("temp_gasB_C=%6.1f", temp_gasB_C, 0);
	format_f("flow_SL=%6.1f", flow_SL, 0);
	format_f("flow_M2=%6.1f", flow_M2, 0);
	format_f("flow_M2_sp=%6.1f", flow_M2_sp, 0);
	format_f("flow_BF2=%6.1f", flow_BF2, 0);
	format_f("flow_BF2_sp=%6.1f", flow_BF2_sp, 0);
	format_f("pres_PUMP=%6.1f", pres_PUMP, 0);
	format_f("pres_BP2_sp=%6.1f", pres_BP2_sp, 0);
	format_f("pres_ECD2=%6.1f", pres_ECD2, 0);
	format_f("ecdA_CH1=%6.1f", ecdA_CH1, 0);
	format_f("ecdA_CH2=%6.1f", ecdA_CH2, 0);
	format_f("temp_pump=%6.1f", temp_pump, 0);
	format_f("temp_SL2=%6.1f", temp_SL2, 0);
	format_f("temp_amb=%6.1f", temp_amb, 0);
	format_f("pres_extern=%6.1f", pres_extern, 0);
	format_f("volt_1234=%6.1f", volt_1234, 0);
	format_f("presL_dope=%6.1f", presL_dope, 0);
	format_f("presL_cal=%6.1f", presL_cal, 0);
	format_f("presL_N2=%6.1f", presL_N2, 0);
	format_f("presH_123=%6.1f", presH_123, 0);
	format_f("volt_5=%7.3f", volt_5, 0);
	format_f("volt_15=%6.2f", volt_15, 0);
	format_f("volt_28=%6.2f", volt_28, 0);
	format_f("CH2_ECD=%6.1f", CH2_ECD, 0);
	format_f("CH2_Col=%6.1f", CH2_Col, 0);
	format_f("CH2_Post=%6.1f", CH2_Post, 0);
	format_f("CH1_ECD=%6.1f", CH1_ECD, 0);
	format_f("CH1_Col=%6.1f", CH1_Col, 0);
	format_d("GCstate=%02d", GCstate, 0);
	format_d("ssv=%d", ssv, 0);
	format_d("valv_calSSV=%d", valv_calSSV, 0);
	format_d("tdlrec=%d", tdlrec, 0);
	format_f("tdlP=%6.1f", tdlP, 0);
	format_f("tdlT=%6.1f", tdlT, 0);
	format_f("tdlsH2O=%6.1f", tdlsH2O, 0);
	format_f("tdllH2O=%6.1f", tdllH2O, 0);
	format_f("tdlsAmp=%6.1f", tdlsAmp, 0);
	format_f("tdlsPow=%6.1f", tdlsPow, 0);
	format_f("tdlsPos=%6.1f", tdlsPos, 0);
	format_f("tdlsZer=%6.1f", tdlsZer, 0);
	format_f("tdllAmp=%6.1f", tdllAmp, 0);
	format_f("tdllPow=%6.1f", tdllPow, 0);
	format_f("tdllPos=%6.1f", tdllPos, 0);
	format_f("tdllZer=%6.1f", tdllZer, 0);
	format_f("tdlbH2O=%6.1f", tdlbH2O, 0);
	format_f("H2O_Pelt=%6.1f", H2O_Pelt, 0);
	format_f("o3=%6.1f", o3, -50);
	format_f("o3temp=%6.1f", o3temp, 0);
	format_f("o3pres=%6.1f", o3pres, 0);
	format_f("o3best=%6.1f", o3best, -50);
	format_f("o3lmpv=%6.1f", o3lmpv, 0);
	format_f("o3lmpsd=%6.1f", o3lmpsd, 0);

	strcat(kuMSG, "\n");
	
	removeSpaces(kuMSG);

}

void BadData(char *fmt) {
	int i;
	char tmp[50];
	
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

// appends float value > bad, val to kuMSG using supplied printf format string, fmt
void format_f(char *fmt, float val, float bad) {
	char tmp[50];
	
	// crudely handle bad numbers...	
	if ( val > bad ) {
		sprintf(tmp, fmt, val);
		strcat(kuMSG, ",");
		strcat(kuMSG, tmp);
	} else {
		BadData(fmt);
	}
}

// appends long value > 0, val to kuMSG using supplied printf format string, fmt
void format_d(char *fmt, long val, long bad) {
	char tmp[50];

	// crudely handle bad numbers...	
	if ( val > bad ) {
		sprintf(tmp, fmt, val);
		strcat(kuMSG, ",");
		strcat(kuMSG, tmp);
	} else {
		BadData(fmt);
	}
}


void send2link() {

	printf("length = %d\n", strlen(kuMSG));
	printf("%s", kuMSG);
	SendDatatoSock();

}

void main( int argc, char ** argv ) {

	int i;

	if ( argc > 1 ) 
		commandline( argc, argv );
	else
		usage();

	OpenSock();
	
	for(i=0; i<testnum; i++) {
		genKUpacket();
		send2link();
		testcode(i);
		delay(1000);
	}
		
}	