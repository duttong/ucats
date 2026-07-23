/* extmain.skel include file for extraction
 * $Log: extmain.skel,v $
 * Revision 1.19  1999/11/18 19:30:33  nort
 * Added <math.h> for floor() as generated for conversions
 *
 * Revision 1.18  1995/10/18  02:05:48  nort
 * Changes to nlcon_display()
 *
 * Revision 1.17  1995/10/06  16:40:02  nort
 * Changes to nlcon_disp()
 * Old change to ROWS() and FRACSECS() macros
 *
 * Revision 1.16  1994/08/29  20:29:28  nort
 * Changes for OUI
 *
 * Revision 1.15  1993/09/27  18:55:31  nort
 * Cleaned up RCS log
 * Cleaned up rcsid[] with Watcom pragmas
 * Added #include <string.h> for memcpy prototype.
 *
 * Revision 1.14  1993/05/19  19:04:51  nort
 * Changed OPT_CON_INIT to OPT_CONSOLE_INIT to allow judicious
 * redefinition for TMA.
 */
#include <stdio.h>
#include <string.h>
#include <sys/kernel.h>
#include <unistd.h>
#include <math.h>
#include "oui.h"
#include "dbr.h"
#include "globmsg.h"
#include "msg.h"
#pragma off (unreferenced)
  static char emrcsid[] =
	"$Id: extmain.skel,v 1.19 1999/11/18 19:30:33 nort Exp nort $";
#pragma on (unreferenced)



 typedef unsigned short UINT;


 typedef unsigned char UCHAR;

 typedef unsigned char UNYBL;


 typedef unsigned long InjFile;

InjFile ITXFileNum;

 typedef unsigned long ULONG;
	unsigned short InjectingInc = 0;

#include <sys/types.h>
#include "adr2000.h"
pid_t adr_proxy = 0;

ADRstruct adr2000[NUMboards];

float ADRanalog( int add ) {
	int board, ch;

	if ( add < 10 ) 
		board = 0;
	else if ( add < 20 )
		board = 1;
	else if ( add < 30 )
		board = 2;
	else
		board = 3;
	ch = add % 10;

	return adr2000[board].analog[ch];
}

float ADRdtoa( int add ) {
	int board, ch;

	if ( add < 10 ) 
		board = 0;
	else if ( add < 20 )
		board = 1;
	else if ( add < 30 )
		board = 2;
	else
		board = 3;
	ch = add % 10;

	return adr2000[board].dtoa[ch];
}

short ADRdig( int add ) {
	int board, ch;

	if ( add < 10 ) 
		board = 0;
	else if ( add < 20 )
		board = 1;
	else if ( add < 30 )
		board = 2;
	else
		board = 3;
	ch = add % 10;

	// -1 is used for NULL data in the adr2000 driver
	// set -1 to 2 for indexing the bittxt.tmc arrays.
	if ( adr2000[board].dig[ch] < 0 )
		return 2;
	else
		return adr2000[board].dig[ch];

}



 typedef float adrA;

 typedef short adrD;

 typedef float adrDA;
#include <math.h>
#include <sys/name.h>
#include <sys/kernel.h>
#include <sys/types.h>
#include <stdlib.h>
#include "smart.h"
#include "regnames.h"
#include "panthermsg.h"
#include "addresses.h"

#define 		ECDOFFLINE 		-9999
#define			NUMSECSXAXIS	 280

pid_t			ECDresp_proxy;

chrom_packet 	ECDresp[MAXDET];

long int 		DetAvgCt1=0, DetAvgCt2=0, DetAvgCt3=0,
		 		DetAvgOffline1=0, DetAvgOffline2=0, DetAvgOffline3=0,
	 			ecd_sum1=0, ecd_sum2=0, ecd_sum3=0,
				ecdA_CH2save=0, ecdA_CH1save=0, ecdA_CH3save=0;
float			ecdCH2x = 0.0, ecdCH1x = 0.0, ecdCH3x = 0.0;
int				currPoint[MAXDET];

// function gets the data from shared data array with smart driver
long int GC_Ctr_Pull( int elecADD ) {
	long ecdDATA;
	
	if ( currPoint[elecADD] >= MAXPOINTS ) currPoint[elecADD] = 0;

	// new data
	if ( currPoint[elecADD] < ECDresp[elecADD].numpnts ) {
		ecdDATA = ECDresp[elecADD].resp[currPoint[elecADD]];
		currPoint[elecADD]++;
	} 
	else {
		ecdDATA = ECDOFFLINE;
		currPoint[elecADD] = 0;
		ECDresp[elecADD].numpnts = -1;
	}

	return ecdDATA;	
}




















 typedef long GC_Freq;
 typedef long GC_Ctr;

GC_Freq ecdA_CH1, ecdA_CH2, ecdA_CH3;
 typedef float VOL5;
 typedef float TEMP;
 typedef float FLOW;
 typedef float PRESS;
 typedef float ANLU;
 typedef float ANLU3;



 typedef adrA VOLTS;


 typedef adrA VOLTS512;


 typedef adrA VOLTSPM;



 typedef adrA VOLTS28;


 typedef adrA MBAR;


 typedef adrA MBARpnu;


 typedef adrA MBARpnuSL;


 typedef adrDA MBARsp;

 typedef adrA CELS;


 typedef adrA SCCM;

 typedef adrA SCCMpnu;

 typedef adrDA SCCMsp;

 typedef adrDA SCCMspPN;

 typedef adrA SCCMsl;


 typedef adrA PSI;

 typedef adrDA PSIsp;

 typedef adrA PSIBpnu;

 typedef adrDA PSIBspPN;

 typedef adrA PSIL;
 typedef adrA PSIH;
#include <sys/types.h>
pid_t rs485_proxy;
int Omega485[14];

short OmegaArray ( int add ) {
	return Omega485[add];
}



 typedef short OmegaT;

 typedef short OmegaTsp;

 typedef adrD DigBit;
 typedef DigBit Bit_HI_LO;
 typedef DigBit Bit_Op_Cl;
 typedef DigBit Bit_Cl_Op;
 typedef DigBit Bit_On_Off;
 typedef DigBit Bit_Air_Cal;
#include <sys/types.h>
#include "addresses.h"
pid_t valco_proxy;
// valvePos[0], [1] and [2] are for SSVs, valvePos[3] and on are for GSVs
// The valco driver returns 1, 2, or 3 for GSV positions.
int valvePos[10] = {0,0,0,3,3,3,3,3,3,3};


 typedef short valvT;
 typedef DigBit valvetext;
 typedef DigBit valvetext_inv;
#include <sys/types.h>
#include "o3ser.h"
pid_t o3_proxy = 0;
pid_t o3x_proxy = 0;

O3struct ozone;
O3Xstruct ozonex;


 typedef float o3float;
 typedef float o3float2;
 typedef long o3lint;
 typedef short o3int;
 typedef short o3int4;
#include <sys/types.h>
#include "maycomm.h"
pid_t maycomm_proxy = 0;

TDLstruct tdl;

#define USECD  200    // use lines CD when the corrected long path is less than 200 ppm
#define USEShort  2000    // use short path when the corrected long path is greater than 2000 ppm
#define ZeroOffset -3.6   // zero offset for lines CD, switched from -6.6 on 5/28/2022


 typedef float tdlfloa9;
 typedef float tdlfloat;
 typedef float tdlfloas;
 typedef float tdlfloa7;
 typedef short tdlint6;
 typedef  long tdlint8;
float old_tdl_best;
#include <sys/types.h>
#include "vaisala.h"
pid_t vaisala_proxy = 0;

RHstruct vai;



 typedef float vaifloat; /* edf2ext.awk reading o3xdata.edf */
  #include <stdlib.h>
  #include "ssp.h"
  #include "tmctime.h"

  #define Ct24_Long(x) (0xFFFFFF & *(TMLONG *)&x)
  #define Ct24_Double(x) (double)Ct24_Long(x)
  #define To_Double(x) (double)(x)
  #define EXTRACTION_INIT initialize()
  #define EXTRACTION_TERM terminate()
  #define ALL_SPSS

  static double ext_delta = 0.;

  static sps_ptr edf_ss_open( char *name, int width ) {
	sps_ptr ss;

	ss = ss_open( name );
	if ( ss_error( ss ) ) {
	  ss = ss_create( name, SPT_INCREASING, width, 0 );
	  if ( ss_error( ss ) )
	    msg( 3, "Unable to create spreadsheet %s", name );
	  errno = 0;
	  msg( 0, "Creating spreadsheet %s.sps", name );
	} else if ( ss_width( ss ) != width )
	  msg( 3,
	    "Existing spreadsheet %s.sps not of width %d", width );
	else msg( 0, "Appending to spreadsheet %s.sps", name );
	return ss;
  }

  sps_ptr o3xout;
  void initialize(void) {
	{
	  char *s;
	  s = getenv("EXT_DELTA");
	  if (s != NULL) {
		ext_delta=atof(s);
		msg(MSG, "Using Time Delta of %lf", ext_delta);
	  }
	}
	o3xout = edf_ss_open( "o3xout", 13 );
	ss_set_column(o3xout, 0, "%14.11lt", "Time");
	ss_set_column(o3xout, 1, "%12.1f", "o3xyy");
	ss_set_column(o3xout, 2, "%12.1f", "o3xmm");
	ss_set_column(o3xout, 3, "%12.1f", "o3xdd");
	ss_set_column(o3xout, 4, "%12.1f", "o3xhh");
	ss_set_column(o3xout, 5, "%12.1f", "o3xmin");
	ss_set_column(o3xout, 6, "%12.1f", "o3xss");
	ss_set_column(o3xout, 7, "%12.1f", "o3x");
	ss_set_column(o3xout, 8, "%12.1f", "o3xtemp");
	ss_set_column(o3xout, 9, "%12.1f", "o3xpres");
	ss_set_column(o3xout, 10, "%12.1f", "o3xbest");
	ss_set_column(o3xout, 11, "%12.3f", "o3xflowa");
	ss_set_column(o3xout, 12, "%12.3f", "o3xflowb");
  }
  void terminate(void) {
	ss_close(o3xout);
  }

#ifdef CONSOLE_INIT
  #error CONSOLE_INIT is obsolete
#endif
#ifdef MSG_LABEL
  #error MSG_LABEL is obsolete
#endif

#ifdef N_CONSOLES
  #include "nl_cons.h"
  #ifndef DATA_ATTR
	#define DATA_ATTR 7
  #endif

  #define cdisplay(d,r,c,s) nlcon_display(d,r,c,s,DATA_ATTR)
  #define display_(d,r,c,t,v,s) {\
	static t sv_;\
	if (v != sv_) { cdisplay(d,r,c,s); sv_ = v; }\
  }
#endif


unsigned char V0 = 0x1;
unsigned char V1 = 0x1;
unsigned char V2 = 0x1;
unsigned char V3 = 0x1;
unsigned char V4 = 0x1;
unsigned char V5 = 0x3;
unsigned char V6 = 0x1;
unsigned char V7 = 0x1;
unsigned char V8 = 0x3;
unsigned char V9 = 0x1;
unsigned char V10 = 0x3;
ULONG CHROMtime;
o3float o3pres;
o3float o3x;
o3float o3xtemp;
o3float o3xpres;
o3int4 o3xflowa;
o3int4 o3xflowb;
o3float o3best;
o3float o3xbest;
tdlfloa7  tdl_shortH2O;
tdlfloat  tdl_longH2O;
tdlfloat  tdl_H2OCD;
tdlfloa7 tdl_p;
union {
  struct {
    UINT MFCtr;
    GC_Ctr GC_Ctr_CH1;
    GC_Ctr GC_Ctr_CH2;
    GC_Ctr GC_Ctr_CH3;
    ULONG CHROMtime;
    ULONG CUMSEC;
    UINT CurrFile;
    UINT CurrInj;
    SCCMspPN flow_M1_sp;
    SCCMpnu flow_M2;
    UCHAR GCstate;
    UCHAR RunState;
    Bit_Cl_Op N2_IN;
    OmegaT CH3_ECD;
    UINT Synch;
  } U0;
  struct {
    char U2[14];
    PSIBpnu pres_BP1;
    PSIBspPN pres_BP1_sp;
    SCCMpnu flow_M1;
    SCCMspPN flow_BF1_sp;
    SCCMpnu flow_BF2;
    MBARpnu pres_ECD1;
    OmegaT CH3_Col;
  } U1;
  struct {
    char U4[14];
    CELS temp_SL2;
    CELS temp_amb;
    SCCMpnu flow_BF1;
    CELS temp_gasB_N;
    MBARpnu pres_ECD2;
    CELS temp_SL1;
    OmegaT CH1_ECD;
  } U3;
  struct {
    char U6[14];
    SCCMpnu flow_M3;
    MBAR pres_PUMP;
    SCCMsl flow_SL;
    PSIBspPN pres_BP2_sp;
    CELS temp_pump;
    SCCMspPN flow_M2_sp;
    OmegaT CH1_Col;
  } U5;
  struct {
    char U8[14];
    SCCMpnu flow_BF3;
    SCCMspPN flow_M3_sp;
    PSIBpnu pres_BP2;
    VOLTS512 volt_1234;
    PSIBpnu pres_BP3;
    SCCMspPN flow_BF2_sp;
    OmegaT CH2_Col;
  } U7;
  struct {
    char U10[14];
    MBAR pres_extern;
    SCCMspPN flow_BF3_sp;
    CELS temp_gasB_C;
    PSIH presH_123;
    PSIL presL_cal;
    MBARpnu pres_ECD3;
    OmegaT CH2_ECD;
  } U9;
  struct {
    char U12[14];
    PSIL presL_N2;
    CELS temp_SL3;
    MBARpnuSL pres_SL;
    Bit_HI_LO FailDummy;
    Bit_Cl_Op SLoopIN;
    VOLTSPM volt_15;
    PSIL presL_dope;
    OmegaTsp CH3_ECD_Sp;
  } U11;
  struct {
    char U14[14];
    VOLTS512 volt_5;
    OmegaT CH3_Post;
    OmegaTsp CH3_Post_Sp;
    o3float o3xtemp;
    Bit_On_Off PumpSwitch;
    Bit_On_Off H2OPump;
    Bit_Op_Cl SLoopOUT;
    Bit_HI_LO InitShutdown;
    VOLTS28 volt_28;
    OmegaTsp CH3_Col_Sp;
  } U13;
  struct {
    char U16[14];
    o3int4 o3xflowb;
    o3int4 o3xflowa;
    o3float o3xpres;
    o3int o3xss;
    o3int4 o3xyy;
    o3float o3x;
    Bit_Cl_Op H2OValve;
    Bit_Air_Cal ssv;
    Bit_HI_LO ManSwitch;
    valvetext valv_CH1;
    OmegaTsp CH1_ECD_Sp;
  } U15;
  struct {
    char U18[14];
    o3int o3xdd;
    o3int o3xhh;
    o3int o3xmin;
    o3int o3xmm;
    tdlfloa7  tdl_shortH2O;
    o3float o3best;
    valvT valv_calSSV;
    valvetext_inv valv_CH3;
    valvetext valv_CH2;
    o3float o3;
  } U17;
  struct {
    char U20[14];
    tdlfloat  tdl_longH2O;
    tdlfloa7  tdl_H2OB;
    tdlint6  tdl_amp;
    tdlfloas tdl_elecT;
    tdlfloas tdl_t;
    tdlfloa7 tdl_p;
    o3float o3temp;
  } U19;
  struct {
    char U22[14];
    tdlint6  tdl_posB;
    tdlint6  tdl_zer;
    tdlint6  tdl_pos;
    tdlint6  tdl_pow;
    tdlfloat tdl_longcorr;
    tdlfloa9  tdl_time;
    ULONG O3count;
    o3float o3xbest;
    OmegaTsp CH1_Col_Sp;
  } U21;
  struct {
    char U24[14];
    tdlfloat tdl_best;
    tdlfloat tdl_CDcorr;
    ULONG vaisX;
    tdlfloat tdl_shortcorr;
    tdlint8   tdlrec;
    ULONG maycX;
    OmegaTsp CH2_Col_Sp;
  } U23;
  struct {
    char U26[30];
    vaifloat vaiT;
    vaifloat vaiRH;
    OmegaTsp CH2_ECD_Sp;
  } U25;
  struct {
    char U28[36];
    o3float o3pres;
  } U27;
  struct {
    char U30[36];
    o3float2 o3lmpv;
  } U29;
  struct {
    char U32[36];
    o3float2 o3lmpsd;
  } U31;
  struct {
    char U34[36];
    o3int o3dd;
    Bit_On_Off O3Pump;
  } U33;
  struct {
    char U36[36];
    o3int o3min;
    o3int o3yy;
  } U35;
  struct {
    char U38[36];
    o3int o3ss;
    o3int o3mm;
  } U37;
  struct {
    char U40[36];
    tdlfloat  tdl_H2OCD;
  } U39;
  struct {
    char U42[38];
    o3int o3hh;
  } U41;
} *home;

static void VSET_5_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 2: /* VaisalaTog */
      V9 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* VaisalaTog */
      V9 &= ~0x1;
      break;
  }
}
static void VSET_4_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 2: /* MaycommTog */
      V7 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* MaycommTog */
      V7 &= ~0x1;
      break;
  }
}
static void VSET_3_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 2: /* OzoneTog */
      V4 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* OzoneTog */
      V4 &= ~0x1;
      break;
  }
}
static void VSET_2_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 2: /* GCTog */
      V2 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* GCTog */
      V2 &= ~0x1;
      break;
  }
}
static void VSET_1_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
  }
  oldstate = newstate;
  switch (newstate) {
  }
}
static void VSET_0_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 3: /* Injection */
      V1 |= 0x1;
      break;
    case 2: /* Injecting1 */
      V3 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 3: /* Injection */
      V1 &= ~0x1;
      break;
    case 2: /* Injecting1 */
      V3 &= ~0x1;
      break;
  }
}
static void tminitfunc(void) {VSET_0_(1);VSET_1_(1);VSET_2_(1);VSET_3_(1);VSET_4_(1);VSET_5_(1);
}
#define TMINITFUNC tminitfunc()

static void nullfunc(void);
static void EF1_0(void) {
  {
  	if (home->U0.GC_Ctr_CH3 >= 0) {
  		ecd_sum3 += home->U0.GC_Ctr_CH3;
  		DetAvgCt3++;
  		ecdCH3x += 0.1;
  	} 
  	if (home->U0.GC_Ctr_CH2 >= 0) {
  		ecd_sum1 += home->U0.GC_Ctr_CH2;
  		DetAvgCt1++;
  		ecdCH2x += 0.1;
  	} 
  	if (home->U0.GC_Ctr_CH1 >= 0) {
  		ecd_sum2 += home->U0.GC_Ctr_CH1;
  		DetAvgCt2++;
  		ecdCH1x += 0.1;
  	}
  }
}

static void BF8_0(void) {
  tdl_H2OCD = home->U39.tdl_H2OCD;
  tdl_p = home->U19.tdl_p;
  V8 &= ~0x2;
  EF1_0();
  {
      if (maycomm_proxy != 0)  Trigger (maycomm_proxy);
  }
}

static void BF16_0(void) {
  BF8_0();
  {
  	if (adr_proxy != 0)  Trigger ( adr_proxy );
  }
  {
  	if (ECDresp_proxy != 0) Trigger ( ECDresp_proxy );
  }
  {if (!(V2)) {
    { VSET_2_(1);
    	}
  }if (!(V3)) {
    V3 |= 0x1;
    { VSET_2_(2);
    		ecdCH1x = 0.0;
    		ecdCH2x = 0.0;
    		ecdCH3x = 0.0;
    	}
  }
  
  	if ( ecdCH2x > NUMSECSXAXIS ) { VSET_2_(2);
  		ecdCH1x = 0.0;
  		ecdCH2x = 0.0;
  		ecdCH3x = 0.0;
  	}
  }
  {
  	if ( DetAvgCt1 > 0 ) {
  		ecdA_CH2 = ecd_sum1/DetAvgCt1;
  		ecdA_CH2save = ecdA_CH2;
  		DetAvgCt1 = 0;
  		ecd_sum1 = 0;
  		DetAvgOffline1 = 0;
  	} 
  	else if (( ecdA_CH2save > 0 ) && ( DetAvgOffline1 < 1 )) {
  		DetAvgOffline1++;
  		ecdA_CH2 = ecdA_CH2save;
  	}
  	else {
  		ecdA_CH2 = ECDOFFLINE;
  		ecdA_CH2save = 0;
  	}
  
  	if ( DetAvgCt2 > 0 ) {
  		ecdA_CH1 = ecd_sum2/DetAvgCt2;
  		ecdA_CH1save = ecdA_CH1;
  		DetAvgCt2 = 0;
  		ecd_sum2 = 0;
  		DetAvgOffline2 = 0;
  	} 
  	else if (( ecdA_CH1save > 0 ) && ( DetAvgOffline2 < 1 )) {
  		DetAvgOffline2++;
  		ecdA_CH1 = ecdA_CH1save;
  	}
  	else {
  		ecdA_CH1 = ECDOFFLINE;
  		ecdA_CH1save = 0;
  	}
  
  	if ( DetAvgCt3 > 0 ) {
  		ecdA_CH3 = ecd_sum3/DetAvgCt3;
  		ecdA_CH3save = ecdA_CH3;
  		DetAvgCt3 = 0;
  		ecd_sum3 = 0;
  		DetAvgOffline3 = 0;
  	} 
  	else if (( ecdA_CH3save > 0 ) && ( DetAvgOffline3 < 1 )) {
  		DetAvgOffline3++;
  		ecdA_CH3 = ecdA_CH3save;
  	}
  	else {
  		ecdA_CH3 = ECDOFFLINE;
  		ecdA_CH3save = 0;
  	}
  
  }
  {
  	if (rs485_proxy != 0) 
  		Trigger ( rs485_proxy );
  
  }
  {
  	if (o3x_proxy != 0)	 Trigger ( o3x_proxy );
  }
  {
  	if (vaisala_proxy != 0)  Trigger ( vaisala_proxy );
  }
}

static void BF128_0(void) {
  BF16_0();
  {
  	if (o3_proxy != 0)	Trigger ( o3_proxy );
  }
}

static void BF8_1(void) {
  tdl_shortH2O = home->U17.tdl_shortH2O;
  tdl_longH2O = home->U19.tdl_longH2O;
  V8 &= ~0x1;
  EF1_0();
  home->U23.maycX++;
  {if (!(V7)) {
    { VSET_4_(1);}
  }
  
      if (home->U23.maycX >= 120) {
          home->U23.maycX = 0; VSET_4_(2);
      }
  }
}

static void BF8_2(void) {
  EF1_0();
  if (!(V8)) {
    {
    	home->U23.tdl_shortcorr = -824 + 1.160*tdl_shortH2O;
    	home->U21.tdl_longcorr = -9.62 + .776*tdl_longH2O*(1 + .0003*tdl_p) + .00099*tdl_longH2O*tdl_longH2O/(1 + .00176*tdl_p);
    	home->U23.tdl_CDcorr = ZeroOffset + (.778*tdl_H2OCD + .00132*tdl_H2OCD*tdl_H2OCD)/(1 + .000268*tdl_p);
        home->U23.tdl_best = home->U21.tdl_longcorr;
    
        if (home->U21.tdl_longcorr < USECD) home->U23.tdl_best = home->U23.tdl_CDcorr;
        if (home->U21.tdl_longcorr > USEShort) home->U23.tdl_best = home->U23.tdl_shortcorr;
    }
  }
}

static void BF16_3(void) {
  o3x = home->U15.o3x;
  o3xtemp = home->U13.o3xtemp;
  o3xpres = home->U15.o3xpres;
  o3xflowa = home->U15.o3xflowa;
  o3xflowb = home->U15.o3xflowb; {
    V10 &= ~0x1;
    V6 &= ~0x1;
  }
  EF1_0();
}

static void BF16_4(void) {
  CHROMtime = home->U0.CHROMtime;
  V0 &= ~0x1;
  EF1_0();
  home->U0.CUMSEC++;
}

static void BF16_6(void) {
  o3xbest = home->U21.o3xbest;
  o3best = home->U17.o3best; {
    V10 &= ~0x2;
    V5 &= ~0x1;
  }
  EF1_0();
  home->U21.O3count++;
  {if (!(V4)) {
    { VSET_3_(1); }
  }
  
  	if ( home->U21.O3count >= 60*60/10 ) { 
  		home->U21.O3count = 0; VSET_3_(2);
  	}
  }
  if (!(V6)) {
    {
    	o3xbest = 0.970*((o3x-3.0) * o3xpres)/(o3xpres*1.1471 - 244.54) ;
    }
  }
}

static void BF16_13(void) {
  EF1_0();
  home->U23.vaisX++;
  {if (!(V9)) {
    { VSET_5_(1); }
  }
  
  	if ( home->U23.vaisX >= 120 ) { 
  		home->U23.vaisX = 0; VSET_5_(2);
  	}
  }
}

static void BF16_14(void) {
  EF1_0();
  { ITXFileNum = home->U0.CurrInj * 1000 + home->U0.CurrFile;
  }
}

static void EF16_15(void) {
  EF1_0();
  {
    	if ( home->U0.GCstate == 0 ) VSET_0_(1);
  	else if ( home->U0.GCstate == 1 ) VSET_0_(2);
  	else if ( home->U0.GCstate == 2 ) VSET_0_(3);
  	else if ( home->U0.GCstate == 3 ) VSET_0_(4);
  }
  {
  	if ( home->U0.RunState == 0 ) VSET_1_(1);
  	else if ( home->U0.RunState == 1 ) VSET_1_(2);
  }
  if (!(V0)) {
    {if (!(V1)) {
      { CHROMtime++; InjectingInc = 0; }
    }
      if ((home->U0.GCstate == 1) || (home->U0.GCstate == 3)) { 
    	if (InjectingInc == 0 ) {
    		CHROMtime = 1; 
    		InjectingInc = 1;
    	}
    	else CHROMtime += 1;
      }
    }
  }
  if (!(V10)) {
    {
      ss_insert_value(o3xout, dtime()+ext_delta, 0);
      ss_set(o3xout, 1, home->U15.o3xyy);
      ss_set(o3xout, 2, home->U17.o3xmm);
      ss_set(o3xout, 3, home->U17.o3xdd);
      ss_set(o3xout, 4, home->U17.o3xhh);
      ss_set(o3xout, 5, home->U17.o3xmin);
      ss_set(o3xout, 6, home->U15.o3xss);
      ss_set(o3xout, 7, o3x);
      ss_set(o3xout, 8, o3xtemp);
      ss_set(o3xout, 9, o3xpres);
      ss_set(o3xout, 10, o3xbest);
      ss_set(o3xout, 11, o3xflowa);
      ss_set(o3xout, 12, o3xflowb);
    }
  }
}

static void BF128_47(void) {
  o3pres = home->U27.o3pres;
  V5 &= ~0x2;
  EF16_15();
}

static void BF128_79(void) {
  EF16_15();
  if (!(V5)) {
    {
    	o3best = (home->U17.o3 * o3pres)/(o3pres*.9996 + 7.9);
    }
  }
}

static void (*efuncs[128])() = {
  BF128_0,
  BF8_1,
  BF8_2,
  BF16_3,
  BF16_4,
  EF1_0,
  BF16_6,
  EF1_0,
  BF8_0,
  BF8_1,
  BF8_2,
  EF1_0,
  EF1_0,
  BF16_13,
  BF16_14,
  EF16_15,
  BF16_0,
  BF8_1,
  BF8_2,
  BF16_3,
  BF16_4,
  EF1_0,
  BF16_6,
  EF1_0,
  BF8_0,
  BF8_1,
  BF8_2,
  EF1_0,
  EF1_0,
  BF16_13,
  BF16_14,
  EF16_15,
  BF16_0,
  BF8_1,
  BF8_2,
  BF16_3,
  BF16_4,
  EF1_0,
  BF16_6,
  EF1_0,
  BF8_0,
  BF8_1,
  BF8_2,
  EF1_0,
  EF1_0,
  BF16_13,
  BF16_14,
  BF128_47,
  BF16_0,
  BF8_1,
  BF8_2,
  BF16_3,
  BF16_4,
  EF1_0,
  BF16_6,
  EF1_0,
  BF8_0,
  BF8_1,
  BF8_2,
  EF1_0,
  EF1_0,
  BF16_13,
  BF16_14,
  EF16_15,
  BF16_0,
  BF8_1,
  BF8_2,
  BF16_3,
  BF16_4,
  EF1_0,
  BF16_6,
  EF1_0,
  BF8_0,
  BF8_1,
  BF8_2,
  EF1_0,
  EF1_0,
  BF16_13,
  BF16_14,
  BF128_79,
  BF16_0,
  BF8_1,
  BF8_2,
  BF16_3,
  BF16_4,
  EF1_0,
  BF16_6,
  EF1_0,
  BF8_0,
  BF8_1,
  BF8_2,
  EF1_0,
  EF1_0,
  BF16_13,
  BF16_14,
  EF16_15,
  BF16_0,
  BF8_1,
  BF8_2,
  BF16_3,
  BF16_4,
  EF1_0,
  BF16_6,
  EF1_0,
  BF8_0,
  BF8_1,
  BF8_2,
  EF1_0,
  EF1_0,
  BF16_13,
  BF16_14,
  EF16_15,
  BF16_0,
  BF8_1,
  BF8_2,
  BF16_3,
  BF16_4,
  EF1_0,
  BF16_6,
  EF1_0,
  BF8_0,
  BF8_1,
  BF8_2,
  EF1_0,
  EF1_0,
  BF16_13,
  BF16_14,
  EF16_15
};

static void IVF8_0(void) {
  V8 |= 0x2;
}
static void IVF8_1(void) {
  V8 |= 0x1;
}
static void IVF16_3(void) { {
    V10 |= 0x1;
    V6 |= 0x1;
  }
}
static void IVF16_4(void) {
  V0 |= 0x1;
}
static void IVF16_6(void) { {
    V10 |= 0x2;
    V5 |= 0x1;
  }
}
static void IVF128_47(void) {
  V5 |= 0x2;
}
#define IVFUNCS
static void (*ivfuncs[128])() = {
  IVF8_0,
  IVF8_1,
  nullfunc,
  IVF16_3,
  IVF16_4,
  nullfunc,
  IVF16_6,
  nullfunc,
  IVF8_0,
  IVF8_1,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  IVF8_0,
  IVF8_1,
  nullfunc,
  IVF16_3,
  IVF16_4,
  nullfunc,
  IVF16_6,
  nullfunc,
  IVF8_0,
  IVF8_1,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  IVF8_0,
  IVF8_1,
  nullfunc,
  IVF16_3,
  IVF16_4,
  nullfunc,
  IVF16_6,
  nullfunc,
  IVF8_0,
  IVF8_1,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  IVF128_47,
  IVF8_0,
  IVF8_1,
  nullfunc,
  IVF16_3,
  IVF16_4,
  nullfunc,
  IVF16_6,
  nullfunc,
  IVF8_0,
  IVF8_1,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  IVF8_0,
  IVF8_1,
  nullfunc,
  IVF16_3,
  IVF16_4,
  nullfunc,
  IVF16_6,
  nullfunc,
  IVF8_0,
  IVF8_1,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  IVF8_0,
  IVF8_1,
  nullfunc,
  IVF16_3,
  IVF16_4,
  nullfunc,
  IVF16_6,
  nullfunc,
  IVF8_0,
  IVF8_1,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  IVF8_0,
  IVF8_1,
  nullfunc,
  IVF16_3,
  IVF16_4,
  nullfunc,
  IVF16_6,
  nullfunc,
  IVF8_0,
  IVF8_1,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  IVF8_0,
  IVF8_1,
  nullfunc,
  IVF16_3,
  IVF16_4,
  nullfunc,
  IVF16_6,
  nullfunc,
  IVF8_0,
  IVF8_1,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc
};

static void nullfunc(void){}
#define TRN 160
#define TRD 1
#define LOWLIM (-1440)
#define HIGHLIM (1440)
#define NBROW 42
#define NROWMINF 1
#define NSECSPER 1
#define NROWSPER 16
#define SYNCHVAL 0xABB4
#define NROWMAJF 128
#define MFSECNUM 16
#define MFSECDEN 1
#define SECDRIFT 90
#define COPY_MFCtr
#define MFCtr home->U0.MFCtr

#ifndef EXTRACTION_INIT
  #define EXTRACTION_INIT
#endif
#ifndef OPT_EXT_INIT
  #define OPT_EXT_INIT
#endif
#ifndef EXTRACTION_TERM
  #define EXTRACTION_TERM
#endif
#ifndef TMINITFUNC
  #define TMINITFUNC
#endif

static unsigned int next_minor_frame, majf_row;
#if (NROWMINF != 1)
  static unsigned int minf_row = 0;
#endif
#ifdef NEED_TIME_FUNCS
  static unsigned short CurMFC;
#endif


void main(int argc, char **argv) {
  oui_init_options(argc, argv);

  TMINITFUNC;
  BEGIN_MSG;
  EXTRACTION_INIT;
  DC_operate();
  EXTRACTION_TERM;
  DONE_MSG;
}


#define MKDCTV(x,y) ((x<<8)|y)
#define DCTV(x,y) MKDCTV(DCT_##x,DCV_##y)

/* The main thing we need to do is reset our row counter on TM START */
void DC_DASCmd(unsigned char type, unsigned char val) {
  switch (MKDCTV(type, val)) {
	case DCTV(TM,TM_START):
	  next_minor_frame = majf_row = 0;
	  #if (NROWMINF != 1)
		minf_row = 0;
	  #endif
	  break;
	case DCTV(TM,TM_END):
	case DCTV(QUIT,QUIT):
	default:
	  break;
  }
}

#define incmod(x,y) if (x==((y)-1)) x = 0; else x++

void DC_data(dbr_data_type *dr_data) {
  unsigned short nrows;

  for (nrows = dr_data->n_rows, home = (void *) &dr_data->data[0];
	   nrows > 0;
	   nrows--, home ++) {

	/* First check the minor frame counter if necessary */
	#if (NROWMINF != 1)
	if (minf_row == 0) {
	#endif
	  COPY_MFCtr /* Needs to be defined by TMC */
	  #ifdef NEED_TIME_FUNCS
		CurMFC = MFCtr;
	  #endif
	  {
		unsigned short delta;
		
		delta = MFCtr - next_minor_frame;
		if (delta != 0) {
		  #ifdef IVFUNCS
			if (delta > NROWMAJF/NROWMINF) delta = NROWMAJF;
			else delta *= NROWMINF;
			/* delta is now the number of rows skipped up to a maximum of
			  nrowmajf. While invalidating, I don't need to update
			  minf_row, since the final will be 0, same as before.
			  MFCtr is already set, and majf_row is updated.
			*/
			while (delta-- > 0)
			  ivfuncs[majf_row]();
		  #endif
		  majf_row = (((unsigned short)MFCtr) % (NROWMAJF/NROWMINF))
							  * NROWMINF;
		}
	  }
	  next_minor_frame = MFCtr+1;
	#if (NROWMINF != 1)
	}
	#endif
	
	/* Now process the row */
	efuncs[majf_row]();
	incmod(majf_row, NROWMAJF);
	#if (NROWMINF != 1)
	  incmod(minf_row, NROWMINF);
	#endif
  }
}

#ifdef __WATCOMC__
  #pragma off (unreferenced)
#endif

void DC_tstamp(tstamp_type *tstamp) { /* Nothing to do! */ }

void DC_other(unsigned char *msg_ptr, int sent_tid) {
  unsigned char rep_msg = DAS_UNKN;

  Reply(sent_tid, &rep_msg, 1);
}

#ifdef __WATCOMC__
  #pragma on (unreferenced)
#endif

#ifdef NEED_TIME_FUNCS
  #if (NROWMINF != 1)
	#define ROWS(x) (((unsigned long)(x))*NROWMINF+minf_row)
  #else
	#define ROWS(x) (x)
  #endif
  #if (NSECSPER != 1)
	#define FRACSECS(x) (((unsigned long)ROWS(x))*NSECSPER)
  #else
	#define FRACSECS(x) ROWS(x)
  #endif
  long itime(void) {
	  return(dbr_info.t_stmp.secs +
		FRACSECS(CurMFC-dbr_info.t_stmp.mfc_num)
	#if (NROWSPER != 1)
		  / NROWSPER
	#endif
		  );
  }
  double dtime(void) {
	  return(dbr_info.t_stmp.secs +
		(double) FRACSECS(CurMFC-dbr_info.t_stmp.mfc_num)
	#if (NROWSPER != 1)
		  / NROWSPER
	#endif
		  );
  }
  double etime(void) {
	double t;
	static double t0 = -1e9;
	
	t = dtime();
	if (t0 == -1e9) t0 = t;
	return(t - t0);
  }
#endif

dbr_info_type dbr_info = {
  "", /* tmid */
  42, /* NBMINF */
  42, /* NBROW */
  128, /* NROWSMAJF */
  1, /* NSECSPER */
  16, /* NROWSPER */
  0, 1, /* MFC lsb col, msb col */
  0xABB4, /* Synch Value */
  0 /* not inverted */
};
