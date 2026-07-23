#include <stdio.h>
#include <stdlib.h>
#include <sys/kernel.h>
#include <sys/name.h>
#include <sys/proxy.h>
#include <string.h>
#include <math.h>
#include <i86.h>

typedef struct {
	char			*mol;		// mol name
	unsigned int	pnum;		// peak number
	unsigned int	strt;		// start point in integration window
	unsigned int	stop;		// stop point "
	float			calval;		// cal tank value for peak
	unsigned int	calssv;		// cal ssv position
	unsigned int	delay;		// use for wrap around chromatography
	float			rt_a;		// use to calibrate 1-pt real-time int to post-proc int (slope)
	float			rt_b;		// use to calibrate 1-pt real-time int to post-proc int (intercept)
} intStruct;

double stats( int peaknum, int p1, int p2, int lstpt );
double subtractbaseline( int peaknum );
double hght( int peaknum );
void resetintfile( intStruct peak );
double integrate ( int toFile, long resp, intStruct peak, long t, short ssv );
double MRres( int peaknum );
double MRres_cal( int peaknum, float a, float b );
