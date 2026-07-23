#include "globmsg.h"

/*
From the manual...

An example of the serial port output is as follows (no line break is in the actual output):
40353.75 13994.1 1914.4 220421.89 73.04 802.49 39.95 28.82 22.00 3643 9230 345
35 9230 155 35 <CR><LF>

It is defined by this C format specifier:
"%9.2f %7.1f %7.1f %8.2f %8.2f %7.2f %6.2f %6.2f %6.2f %6u %6d %3d %6d %6d %3d
%6d \r\n",

The order of parameters, left to right, is:
1) System clock time in seconds.
2) H2O in ppmv (from short path integrated area, valid ~6,000 ppmv to 50,000 ppmv)
3) H2O in ppmv (from line B 2f, valid ~1,000 ppmv to 50,000 ppmv)
4) H2O in ppmv (from long path integrated area, valid ~1,000 ppmv to 200 ppmv)
5) H2O in ppmv (from long path lines C/D, valid ~200 ppmv and below)
6) Cell pressure in mbar
7) Cell temperature in C
8) Electronics box inside air temperature in C
9) Spare T sensor (unconnected but is available (10K at 25C thermistor)
10) Peak to peak raw 2f signal amplitude in A/D counts (0-65535) for long path channel
11) Laser power proxy in A/D counts (0-32767)
12) Position of the H2O line D within the 0-511 point scan (long path channel)
13) DC spectrum output at laser off (null) pulse for long path channel
14) Laser power proxy in A/D counts (0-32767 … same as long path value)
15) Position of H2O line D within the 0-511 point scan (short path channel)
16) DC spectrum output at laser off (null) pulse for short path channel
18/19) Carriage Return + Linefeed pair to terminate the record

*/

typedef struct {
	long	rec;		// record number
	float   time;
	float   H2O_sh;
	float   H2O_B;
	float   H2O_lg;
	float   H2O_CD;
	float	p;			// pressure in cell
	float	t;			// temp in cell
	float   t_elec;
	//float   t_spare;
	unsigned int amp;
	unsigned int pow;
	unsigned int pos;
	unsigned int zer;
	//unsigned int ampDup;
	unsigned int posB;
	//unsigned int posDup;
} TDLstruct;

enum {
	msg_TDLquit = MAX_GLOBMSG,
	msg_TDLnomsg,
	msg_TDLcol
};

#define NUM_TDL_RECS	2
