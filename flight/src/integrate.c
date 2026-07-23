#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "nortlib.h"
#include "integrate.h"
#include "tmctime.h"

#define		INTPEAKS		5		// number of peaks that can be integrated
#define		MAXECDPTS		16
#define 	CHROMSUB		MAXECDPTS*30	// 16 hz * 30 seconds

static double ichrom[CHROMSUB][INTPEAKS];		// chrom array

static double prvCalH[INTPEAKS];				// prev cals height
static double prvMR[INTPEAKS];					// prev air MR
static int intinc[INTPEAKS];
static int init = 0;

typedef struct {
	double 	max;
	int 	maxpt;
	double 	min;
	int 	minpt;
	int 	lstpt;
	double	m;
	double	b;
} INTresStruct;

static INTresStruct res;

// returns the max and min via res array between p1 and p2
double stats( int ch, int p1, int p2 ) {
	int i;
	double max, min;
	int maxpt, minpt;

	max = ichrom[p1][ch];
	maxpt = p1;
	min = 10000000;
	minpt = 0;
	
	for (i=p1; i<=p2; i++) {
		if ( ichrom[i][ch] > max ) {
			max = ichrom[i][ch];
			maxpt = i;
		}
		if ( ichrom[i][ch] < min ) {
			min = ichrom[i][ch];
			minpt = i;
		}
	}

	res.max = max;
	res.maxpt = maxpt;
	res.min = min;
	res.minpt = minpt;

	return max;
}

double subtractbaseline( int ch ) {

	int i, lstpt;
	int top, pt1x, pt2x;
	double pt1y, pt2y, stepin;

	// find last data point in ichrom array
	for(i=0; i<CHROMSUB; i++) {
		if ( ichrom[i][ch] <= -1 ) {
			lstpt = i-1;
			break;	
		}
	}
	res.lstpt = lstpt;
	stepin = lstpt/10;

	// first a crude baseline subtraction from the two outermost points
	res.m = ( ichrom[lstpt][ch] - ichrom[0][ch] ) / ( lstpt - 0 );
	res.m /= 10;	
	res.b = ichrom[0][ch] - res.m * 0;

	// subtract baseline
	for( i=0; i<=lstpt; i++ )
		ichrom[i][ch] -= (res.m * i + res.b);

	stats( ch, stepin, lstpt-stepin );
	top = res.maxpt;

	// left side of peak
	stats( ch, 0, top );
	pt1x = res.minpt;
	pt1y = res.min;

	// right side of peak
	stats( ch, top+1, lstpt );
	pt2x = res.minpt;
	pt2y = res.min;

	res.m = ( pt2y - pt1y ) / ( pt2x - pt1x ) / 10;		// divided by 10 Hz
	res.b = pt1y - res.m * pt1x;

	// subtract baseline
	for( i=0; i<=lstpt; i++ )
		ichrom[i][ch] -= (res.m * i + res.b);

	stats( ch, stepin, lstpt-stepin );
	
	return res.max;

}

// returns the peak height
double hght( int ch ) {

	double max;

	max = subtractbaseline( ch );

	return max;
}

// opens a new integration result file
// this function will overwrite old files.
void resetintfile( intStruct peak ) {
	FILE *int_file = NULL;
	char intfile[30];

	sprintf( intfile, "int-%s", peak.mol );

	if ((int_file = fopen( intfile, "w" )) == NULL)
		printf ("=====Cannot open %s\n", intfile);

	fprintf( int_file, "%s_date, %s_time, %s_SSV, %s_ret, %s_H, %s_conc\n", 
		peak.mol, peak.mol, peak.mol, peak.mol, peak.mol, peak.mol );

	fclose( int_file );

}

// calculates the mixing ratio of current injection
double integrate ( int toFile, long resp, intStruct peak, long t, short ssv ) {
	FILE *int_file = NULL;
	//FILE *tfile = NULL;
	double H = 0.0;
	double MR = 0.0;
	float ret = 0.;
	int i, ch = peak.pnum;
	struct tm *tmbuf;
	char tstr[40];
	long int TT;
	char intfile[30];

	// initialization
	if ( init == 0 ) {
		for ( i=0; i<=INTPEAKS; i++ )
			prvCalH[i] = -1;
		init = 1; 
	}

	// integration result file */
	sprintf( intfile, "int-%s", peak.mol );

	// in range
	if ( t < peak.strt ) {
		for ( i=0; i<CHROMSUB; i++ ) { ichrom[i][ch] = -1; }
		intinc[ch] = 0;
	}
	else if (( t >= peak.strt ) && ( t <= peak.stop ) && ( resp >= 0 )) {
		ichrom[intinc[ch]++][ch] = resp * 1.0;
	}
	else if (( t > peak.stop ) && ( intinc[ch] > 0 )) { 
		
		// peak height
		H = hght( ch );
		H = ( res.maxpt == 0 ) ? -1 : H;
		if ( H > 1000000 ) H = -1;

		if ( ssv != peak.calssv ) {
			if ( prvCalH[ch] == -1 )
				MR = -1;
			else
				MR = (H / prvCalH[ch]) * peak.calval;
			prvMR[ch] = MR * peak.rt_a + peak.rt_b;		/* apply rt to post proc calibration */
		}
		else if ( ssv == peak.calssv ) {
			prvCalH[ch] = H;
		}

		if ( toFile ) {
			if ((int_file = fopen( intfile, "a+" )) == NULL)
				printf ("=====Cannot open %s\n", intfile);
	
			// inject time
			TT = itime() - t - peak.delay +1;		// +1 to sync to itx files
			tmbuf = gmtime( &TT );

			// retention time
			ret = peak.strt + peak.delay + res.maxpt/10.;
			
			sprintf( tstr, "%02d-%02d-%04d, %02d:%02d:%02d", tmbuf->tm_mon+1, tmbuf->tm_mday, tmbuf->tm_year + 1900,
					tmbuf->tm_hour, tmbuf->tm_min, tmbuf->tm_sec );

			if ( ssv == peak.calssv ) {
				fprintf( int_file, "%s, %3u, %6.1f, %10.2lf, %7.2lf\n", tstr, ssv, ret, H, peak.calval );
			} else {
				fprintf( int_file, "%s, %3u, %6.1f, %10.2lf, %7.2lf\n", tstr, ssv, ret, H, prvMR[ch] );
			}
			fclose( int_file );

			/* for debugging */
			/*
			if (( ch == 3 ) && (tmbuf->tm_hour == 16) && (tmbuf->tm_min == 25)) {
				printf("%s m = %lf\n", peak.mol, res.m);
				tfile = fopen( "chrom.txt", "w" );
				//fprintf( tfile, "%f %d %lf %lf\n", res.max, res.maxpt, res.m, res.b );
				for(i=0; i<intinc[ch]-1; i++ )
					fprintf( tfile, "%10.2lf\n", ichrom[i][ch] );
				fclose( tfile );
			}
			*/

		}

		intinc[ch] = 0;

		return prvMR[ch];
	}

	return 0;

}

// used to return current mixing ratio to TMC
double MRres( int ch ) {

	return prvMR[ch];

}

