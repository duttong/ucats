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
#include "globmsg.h"
#include "collect.h"

#include "maycomm.h"


#define BAUD          115200
#define PAR           "none"
#define BITS               8
#define STOPB              1

#define PACKETSIZE       115    // number of chars returned in a normal packet
#define MAXCHAR_RET      500    // largest packet that can be returned
#define RCVfromSRVR        2    // max number of bytes a command from the server can be.
#define NAN               -1

int     fd;
long    rec = 0;
char    port[30] = "/dev/ser8"; // Default port
char    data[MAXCHAR_RET];
char    dataAlt[MAXCHAR_RET];

// make the TDL struct handle multiple records
TDLstruct TDL[NUM_TDL_RECS];

static void usage() {
    printf("USAGE: maycomm [-p serial port] [-t incs] [-h]\n");
    printf("       -p serial port (default /dev/ser8)\n");
    printf("       -t inc         test mode with number of increments.\n");
    printf("       -h             help\n\n");
    printf("    examples:\n");
    printf("       maycomm -p /dev/ser2   runs the driver on serial port 2.\n");
    printf("       maycomm -t 10          when the maycomm is polling, read 10 times.\n\n");
    exit(0);
}


static void config_port() {

    char    comm[200];

    sprintf(comm, "stty +raw <%s\n", port);
    if (system(comm) == -1)
        printf("config_port error: %s\n", comm);

    sprintf(comm, "stty +sane -osflow -ihflow -ohflow -lkhflow <%s\n", port);
    if (system(comm) == -1)
        printf("config_port error: %s\n", comm);

    sprintf(comm, "stty baud=%ld par=%s bits=%d stopb=%d <%s\n", BAUD, PAR, BITS, STOPB, port);
    if (system(comm) == -1)
        printf("config_port error: %s\n", comm);

}

static int open_port() {

    config_port();

    printf("opening port: %s\n", port);
    
    if ((fd = open(port , O_RDWR)) == -1) {
        perror("maycomm could not open serial port");
        exit(-1);
    } 

    tcflush(fd, TCIOFLUSH);
    return 0;

}

static void nullarrays() {

    int i;
    for (i=0; i<MAXCHAR_RET; i++)
        data[i] = dataAlt[i] = '\0';

}

static void NANrecs() {
    
    int i;
    for (i=0; i<NUM_TDL_RECS; i++) {
        TDL[i].rec =        NAN;    // record number 
        TDL[i].time =       NAN;
        TDL[i].H2O_sh =     NAN;
        TDL[i].H2O_B =      NAN;
        TDL[i].H2O_lg =     NAN;
        TDL[i].H2O_CD =     NAN;
        TDL[i].p =          NAN;
        TDL[i].t =          NAN;
        TDL[i].t_elec =     NAN;
        TDL[i].amp =        NAN;
        TDL[i].pow =        NAN;
        TDL[i].pos =        NAN;
        TDL[i].zer =        NAN;
        TDL[i].posB =       NAN;
    }

}

// function rotates the recs forward, i=i+1
static void PopRecs() {

    int i;

    for (i=0; i<NUM_TDL_RECS-1; i++) {
        TDL[i].rec =    TDL[i+1].rec;   // record number 
        TDL[i].time =   TDL[i+1].time;
        TDL[i].H2O_sh = TDL[i+1].H2O_sh;
        TDL[i].H2O_B =  TDL[i+1].H2O_B;
        TDL[i].H2O_lg = TDL[i+1].H2O_lg;
        TDL[i].H2O_CD = TDL[i+1].H2O_CD;
        TDL[i].p =      TDL[i+1].p;
        TDL[i].t =      TDL[i+1].t;
        TDL[i].t_elec = TDL[i+1].t_elec;
        TDL[i].amp =    TDL[i+1].amp;
        TDL[i].pow =    TDL[i+1].pow;
        TDL[i].pos =    TDL[i+1].pos;
        TDL[i].zer =    TDL[i+1].zer;
        TDL[i].posB =   TDL[i+1].posB;    
    }

    // NAN last record.
    TDL[NUM_TDL_RECS].rec =     NAN;
    TDL[NUM_TDL_RECS].time =    NAN;
    TDL[NUM_TDL_RECS].H2O_sh =  NAN;
    TDL[NUM_TDL_RECS].H2O_B =   NAN;
    TDL[NUM_TDL_RECS].H2O_lg =  NAN;
    TDL[NUM_TDL_RECS].H2O_CD =  NAN;
    TDL[NUM_TDL_RECS].p =       NAN;
    TDL[NUM_TDL_RECS].t =       NAN;
    TDL[NUM_TDL_RECS].t_elec =  NAN;
    TDL[NUM_TDL_RECS].amp =     NAN;
    TDL[NUM_TDL_RECS].pow =     NAN;
    TDL[NUM_TDL_RECS].pos =     NAN;
    TDL[NUM_TDL_RECS].zer =     NAN;
    TDL[NUM_TDL_RECS].posB =    NAN;
}


int checkfordata() {
    
    int bytes;

    nullarrays();

    bytes = dev_read(fd, data, MAXCHAR_RET, PACKETSIZE, 0, 4, 0, 0);
    if (bytes > 0) {
        // if too small look for more data
        if (bytes < PACKETSIZE) {
            delay(100);
            dev_read(fd, dataAlt, MAXCHAR_RET, PACKETSIZE, 0, 3, 0, 0);
            data[bytes] = *dataAlt;
            return parsedata(); 
        }
        return parsedata();
    }

    return 0;
}

int parsedata() {

    char    *p;
    char    *delims = {" "};
    char    buffer[MAXCHAR_RET];
    int     i = 0;

    strcpy(buffer, data);

    // if rec is not NAN the data hasn't been read from the TMC side yet.
    // add new data to another index.
    if (TDL[i].rec != NAN) {
		printf("rec = %d time = %f, H2O = %f\n", TDL[i].rec, TDL[i].time, TDL[i].H2O_sh);
        i = 1;
	}

    if ((p = strtok(buffer, delims)) != NULL)
        TDL[i].time = atof(p);
    else 
        return 0;
        
    p = strtok(NULL, delims);
    TDL[i].H2O_sh = atof(p);
    p = strtok(NULL, delims);
    TDL[i].H2O_B = atof(p);
    p = strtok(NULL, delims);
    TDL[i].H2O_lg = atof(p);
    p = strtok(NULL, delims);
    TDL[i].H2O_CD = atof(p);
    
    p = strtok(NULL, delims);
    TDL[i].p = atof(p);
    p = strtok(NULL, delims);
    TDL[i].t = atof(p);
    p = strtok(NULL, delims);
    TDL[i].t_elec = atof(p);
    
    p = strtok(NULL, delims);
    TDL[i].amp = atoi(p);
    p = strtok(NULL, delims);
    TDL[i].pow = atoi(p);
    p = strtok(NULL, delims);
    TDL[i].pos = atoi(p);
    p = strtok(NULL, delims);
    TDL[i].zer = atoi(p);
    p = strtok(NULL, delims);
    TDL[i].posB = atoi(p);

    // record number is added to TDL[i] data 
    // it is used to determine if new data has
    // been acquired.
    TDL[i].rec = rec++;

    return 1;
}

// Handle command line inputs
static void commandline(int argc, char ** argv) {

    int optltr,
		i = 0,
        test = 0, 
        inc = 0,
        maxinc;

    FILE *fdtest;

    while ((optltr = getopt(argc, argv, "p:t:h")) != -1) {
        switch(optltr) {
            case 'p':   sprintf(port,"%s", optarg);             break;
            case 't':   test = 1; maxinc = atoi(optarg);        break;
            case 'h':   usage();                                break;
            default:    usage();
        }
    }

    // test command
    if (test) {
        open_port();
        fdtest = fopen("maycomm.out", "w");
        delay(2000);
        tcflush(fd, TCIOFLUSH);

        while(inc < maxinc) {
            if (checkfordata()) {
                inc++;
                for(i=0; i<NUM_TDL_RECS-1; i+=1) {
                    printf("raw: %s\n", data);
                    printf("H2O sh/B/lg/CD: %4.1f/%4.1f/%4.1f/%4.1f\n", 
                        TDL[i].H2O_sh, TDL[i].H2O_B, TDL[i].H2O_lg, TDL[i].H2O_CD);
                    printf("Cell P: %4.1f Cell T: %4.1f elect_T: %4.1f\n", 
                        TDL[i].p, TDL[i].t, TDL[i].t_elec);
                    printf("2f amp, power, zero, pos, posB: %u %u %u %d %3d\n\n", 
                        TDL[i].amp, TDL[i].pow, TDL[i].zer, TDL[i].pos, TDL[i].posB);

                    fprintf(fdtest, "H2O sh/B/lg/CD: %4.1f/%4.1f/%4.1f/%4.1f\n", 
                        TDL[i].H2O_sh, TDL[i].H2O_B, TDL[i].H2O_lg, TDL[i].H2O_CD);
                    fprintf(fdtest, "Cell P: %4.1f Cell T: %4.1f elect_T: %4.1f\n", 
                        TDL[i].p, TDL[i].t, TDL[i].t_elec);
                    fprintf(fdtest, "2f amp, power, zero, pos, posB: %u %u %u %d %3d\n\n", 
                        TDL[i].amp, TDL[i].pow, TDL[i].zer, TDL[i].pos, TDL[i].posB);
                }
                NANrecs();
            }
        }

        fclose(fdtest);
        exit(0);
    }

}




void main(int argc, char ** argv) {

    char        *name,
                rcvMsg[RCVfromSRVR];

    int         name_id;

    send_id     colId;

    pid_t       colProxy,
                rcvPid;

    if (argc > 0) 
        commandline(argc, argv);

    open_port();
    delay(2000);
    tcflush(fd, TCIOFLUSH);

    NANrecs();

    /* attach maycomm name */
    name = nl_make_name("maycomm", 1);
    name_id = qnx_name_attach(0, name);
    if (name_id == -1)
        nl_error(3, "Unable to attach name %s", name);

    colId = Col_send_init("tdl", &TDL, sizeof(TDL));
    colProxy = Col_set_proxy (12, msg_TDLcol);

    Col_send(colId);

    // Main loop
    while (rcvMsg[0] != msg_TDLquit) {

        rcvMsg[0] = msg_TDLnomsg;
        rcvPid = Creceive(0, &rcvMsg, RCVfromSRVR);

        if (rcvPid != -1) {

            switch (rcvMsg[0]) {
    
                case msg_TDLquit:
                    close(fd);
                    exit(0);

                case msg_TDLcol:
					if (TDL[0].rec != NAN) {
	                    Col_send(colId);
    	                PopRecs();
					}
                    break;
            }
        }
        else {
    
            delay(200);
            checkfordata();
        }

    }




}
