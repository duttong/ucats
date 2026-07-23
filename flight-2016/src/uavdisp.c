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
	else
		board = 2;
	ch = add % 10;

	return adr2000[board].analog[ch];
}

float ADRdtoa( int add ) {
	int board, ch;

	if ( add < 10 ) 
		board = 0;
	else if ( add < 20 )
		board = 1;
	else
		board = 2;
	ch = add % 10;

	return adr2000[board].dtoa[ch];
}

short ADRdig( int add ) {
	int board, ch;

	if ( add < 10 ) 
		board = 0;
	else if ( add < 20 )
		board = 1;
	else
		board = 2;
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

long int 		DetAvgCt1=0, DetAvgCt2=0,
		 		DetAvgOffline1=0, DetAvgOffline2=0,
	 			ecd_sum1=0, ecd_sum2=0,
				ecdA_CH2save=0, ecdA_CH1save=0;
float			ecdCH2x = 0.0, ecdCH1x = 0.0;
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

GC_Freq ecdA_CH2, ecdA_CH1;
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


 typedef adrDA MBARsp;

 typedef adrA CELS;


 typedef adrA SCCM;

 typedef adrDA SCCMsp;

 typedef adrA SCCMsl;


 typedef adrA PSI;

 typedef adrDA PSIsp;

 typedef adrA PSIL;
 typedef adrA PSIH;
#include <sys/types.h>
pid_t rs485_proxy;
int Omega485[12];

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

#define USELONGPATH  900    // use the long path TDL when short path less than 900 ppm
#define OffsetShortPath 2   // offset to match long and short at crossover (was 102)


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



 typedef float vaifloat;
#include "integrate.h"
#include "tmctime.h"
#include "nl_dsp.h"

/* make sure the defined INTPEAKS in integrate.c
   equals the number of peaks integrated */

intStruct N2Oint;	/* channel 2 */
intStruct CH4int;	/* channel 1 */
intStruct SF6int;	/* channel 2 */





int old_ssv1min;	
int old_ssv2min; typedef float MixRatio;

MixRatio MR_CH4;
MixRatio MR_N2O;
MixRatio MR_SF6;



int secondhalf;
  char * Air_Cal_text[3] = { "Air", "Cal", "---" };
  char * HI_LO_text[2] = { "LO", "HI" };
  char * Op_Cl_text[3] = { " Open", "Close", "-----" };
  char * Cl_Op_text[3] = { "Close", " Open", "-----" };
  char * On_Off_text[3] = { "Off", " On", "---" };
  char * Offline_text[2] = { "---", "---" };
  char * SrtSequence_off_text[2] = { "   Off", "SrtSeq" };
  char * Load_Inject_text[3] = { " Load ", "Inject" ,"ERROR " };
  char * Inject_Load_text[3] = { "Inject", " Load " ,"ERROR " };
  char * Inj1_Inj2_text[3] = { "Inj1 ", "Inj2 ", "ERROR" };
  char * Inj2_Inj1_text[3] = { "Inj2 ", "Inj1 ", "ERROR" };
  char * BF_IN_text[2] = { "IN", "BF" };
  char * IN_BF_text[2] = { "BF", "IN" };
  char * Heat_Cool_text[2] = { "Heat", "Cool" };
  char * GCstate_text[3] = { "No Injections", " Start Inject", "             " };

  #include "rtgapi.h"
  rtg_t *chromCH2_rtg[2];
  int chromCH2_rtginc = 1;
  rtg_t *chromCH1_rtg[2];
  int chromCH1_rtginc = 1;
  rtg_t *ozoneConc_rtg[2];
  int ozoneConc_rtginc = 1;
  rtg_t *ozonePres_rtg[2];
  int ozonePres_rtginc = 1;
  rtg_t *ozoneTemp_rtg[2];
  int ozoneTemp_rtginc = 1;
  rtg_t *ozoneXConc_rtg[2];
  int ozoneXConc_rtginc = 1;
  rtg_t *ozoneXPres_rtg[2];
  int ozoneXPres_rtginc = 1;
  rtg_t *ozoneXTemp_rtg[2];
  int ozoneXTemp_rtginc = 1;
  rtg_t *TDLbest_rtg[2];
  int TDLbest_rtginc = 1;
  void rtgext_init( void ) {
    chromCH2_rtg[0] = rtg_init( "chromCH2/0" );
    chromCH2_rtg[1] = rtg_init( "chromCH2/1" );
    chromCH1_rtg[0] = rtg_init( "chromCH1/0" );
    chromCH1_rtg[1] = rtg_init( "chromCH1/1" );
    ozoneConc_rtg[0] = rtg_init( "ozoneConc/0" );
    ozoneConc_rtg[1] = rtg_init( "ozoneConc/1" );
    ozonePres_rtg[0] = rtg_init( "ozonePres/0" );
    ozonePres_rtg[1] = rtg_init( "ozonePres/1" );
    ozoneTemp_rtg[0] = rtg_init( "ozoneTemp/0" );
    ozoneTemp_rtg[1] = rtg_init( "ozoneTemp/1" );
    ozoneXConc_rtg[0] = rtg_init( "ozoneXConc/0" );
    ozoneXConc_rtg[1] = rtg_init( "ozoneXConc/1" );
    ozoneXPres_rtg[0] = rtg_init( "ozoneXPres/0" );
    ozoneXPres_rtg[1] = rtg_init( "ozoneXPres/1" );
    ozoneXTemp_rtg[0] = rtg_init( "ozoneXTemp/0" );
    ozoneXTemp_rtg[1] = rtg_init( "ozoneXTemp/1" );
    TDLbest_rtg[0] = rtg_init( "TDLbest/0" );
    TDLbest_rtg[1] = rtg_init( "TDLbest/1" );
  }

  #define N_CONSOLES 2

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
unsigned char V8 = 0x1;
unsigned char V9 = 0x1;
unsigned char V10 = 0x1;
unsigned char V11 = 0x1;
unsigned char V12 = 0x3;
unsigned char V13 = 0x1;
unsigned char V14 = 0x1;
unsigned char V15 = 0x1;
unsigned char V16 = 0x3;
unsigned char V17 = 0x3;
unsigned char V18 = 0x3;
unsigned char V19 = 0x1;
unsigned char V20 = 0x1;
unsigned char V21 = 0x1;
unsigned char V22 = 0x1;
unsigned char V23 = 0x1;
ULONG CHROMtime;
ULONG O3count;
o3float o3pres;
o3float o3x;
o3float o3xtemp;
o3float o3xpres;
o3float o3best;
tdlint8   tdlrec;
tdlfloat  tdl_longH2O;
union {
  struct {
    UINT MFCtr;
    GC_Ctr GC_Ctr_CH1;
    GC_Ctr GC_Ctr_CH2;
    ULONG CUMSEC;
    SCCMsp flow_M1_sp;
    UCHAR GCstate;
    UCHAR RunState;
    PSIH presH_123;
    PSIL presL_cal;
    UINT CurrInj;
    OmegaT CH2_Col;
    UINT Synch;
  } U0;
  struct {
    char U2[10];
    SCCM flow_M1;
    SCCM flow_BF1;
    SCCMsp flow_BF1_sp;
    PSI pres_BP1;
    UINT CurrFile;
    ULONG CHROMtime;
  } U1;
  struct {
    char U4[10];
    CELS temp_SL1;
    MBAR pres_ECD2;
    CELS temp_gasB_C;
    CELS temp_gasB_N;
    PSIsp pres_BP1_sp;
    OmegaT CH1_ECD;
  } U3;
  struct {
    char U6[10];
    PSIsp pres_BP2_sp;
    CELS temp_SL2;
    SCCM flow_M2;
    SCCMsp flow_M2_sp;
    MBAR pres_SL;
    OmegaT CH1_Col;
  } U5;
  struct {
    char U8[10];
    PSIL presL_N2;
    CELS temp_amb;
    MBAR pres_extern;
    SCCM flow_BF2;
    SCCMsl flow_SL;
    OmegaT H2O_Pelt;
  } U7;
  struct {
    char U10[10];
    VOLTS28 volt_28;
    VOLTS512 volt_5;
    OmegaT CH2_ECD;
    OmegaTsp CH2_ECD_Sp;
    MBAR pres_PUMP;
    SCCMsp flow_BF2_sp;
    OmegaTsp CH2_Col_Sp;
  } U9;
  struct {
    char U12[10];
    OmegaTsp H2O_Pelt_Sp;
    Bit_HI_LO InitShutdown;
    Bit_HI_LO KeySwitch;
    Bit_HI_LO ManSwitch;
    Bit_Cl_Op N2_IN;
    o3float o3temp;
    OmegaTsp CH2_Post_Sp;
    CELS temp_pump;
    OmegaTsp CH1_ECD_Sp;
  } U11;
  struct {
    char U14[10];
    Bit_On_Off PumpSwitch;
    Bit_Op_Cl SLoopIN;
    Bit_Cl_Op SLoopOUT;
    Bit_Air_Cal ssv;
    o3float o3xtemp;
    VOLTS512 volt_1234;
    VOLTSPM volt_15;
    OmegaTsp CH1_Col_Sp;
  } U13;
  struct {
    char U16[10];
    o3int4 o3xflowb;
    o3int4 o3xflowa;
    ULONG O3count;
    o3float o3xbest;
    OmegaT CH2_Post;
    o3float o3;
    PSIL presL_dope;
  } U15;
  struct {
    char U18[10];
    o3float o3best;
    o3float o3xpres;
    tdlfloa7  tdl_H2OB;
    o3int o3mm;
    o3float2 o3lmpv;
    valvetext valv_CH2;
    valvetext valv_CH1;
  } U17;
  struct {
    char U20[10];
    char U21[2];
    ULONG maycX;
    tdlint6  tdl_pow;
    tdlint6  tdl_amp;
    o3float2 o3lmpsd;
    o3int o3ss;
    valvT valv_calSSV;
    o3float o3pres;
  } U19;
  struct {
    char U23[10];
    tdlfloat  tdl_H2OCD;
    tdlfloat  tdl_longH2O;
    ULONG vaisX;
    o3float o3x;
    o3int o3yy;
    o3int o3dd;
    o3int o3hh;
  } U22;
  struct {
    char U25[10];
    tdlint6  tdl_posB;
    tdlint6  tdl_zer;
    tdlint6  tdl_pos;
    tdlfloat tdl_best;
    o3int o3min;
    o3int o3xhh;
    o3int o3xmin;
    o3int o3xmm;
    o3int o3xss;
    o3int4 o3xyy;
  } U24;
  struct {
    char U27[20];
    o3int o3xdd;
    tdlfloa7  tdl_shortH2O;
    tdlfloa9  tdl_time;
    char U28[2];
  } U26;
  struct {
    char U30[20];
    tdlfloas tdl_elecT;
    tdlfloas tdl_t;
    tdlfloas tdl_p;
  } U29;
  struct {
    char U32[20];
    vaifloat vaiT;
    vaifloat vaiRH;
  } U31;
} *home;
/* doub icvt for MixRatio -> MixRatio */
double _CVT_0( MixRatio x ) {
  return (double) floor(  x  * 1E1 + .5 );
}
char *SL_6_1_f_4( long int x) {
  static char obuf[7];
  int neg;
  int iov;

  if (x < -9999 || x > 99999) return("******");
  if (x < 0) { neg = 1; x = -x; }
  else neg = 0;
  obuf[6] = '\0';
  obuf[5] = (x % 10) + '0';
  iov = x/10;
  obuf[4] = '.';
  obuf[3] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) {
    if (neg) { obuf[2] = '-'; goto space1; }
    else goto space2;
  }
  obuf[2] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) {
    if (neg) { obuf[1] = '-'; goto space0; }
    else goto space1;
  }
  obuf[1] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) {
    if (neg) { obuf[0] = '-'; goto nospace; }
    else goto space0;
  }
  obuf[0] = (iov % 10) + '0';
  goto nospace;
  space2: obuf[2] = ' ';
  space1: obuf[1] = ' ';
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}
/* _CVT_1() int tcvt MixRatio -> MixRatio */
char *_CVT_1(MixRatio x) {
  double iv;

  iv = _CVT_0( x );
  if ( iv < -9999 || iv > 99999 )
	return "******";
  return SL_6_1_f_4( iv );
}
/* doub icvt for vaifloat -> vaifloat */
double _CVT_2( vaifloat x ) {
  return (double) floor(  x  * 1E1 + .5 );
}
/* _CVT_3() int tcvt vaifloat -> vaifloat */
char *_CVT_3(vaifloat x) {
  double iv;

  iv = _CVT_2( x );
  if ( iv < -9999 || iv > 99999 )
	return "******";
  return SL_6_1_f_4( iv );
}
char *SS_6_224_d_0( short int x) {
  static char obuf[7];
  int neg;

  if (x < 0) { neg = 1; x = -x; }
  else neg = 0;
  obuf[6] = '\0';
  obuf[5] = (x % 10) + '0';
  x /= 10;
  if (x == 0) {
    if (neg) { obuf[4] = '-'; goto space3; }
    else goto space4;
  }
  obuf[4] = (x % 10) + '0';
  x /= 10;
  if (x == 0) {
    if (neg) { obuf[3] = '-'; goto space2; }
    else goto space3;
  }
  obuf[3] = (x % 10) + '0';
  x /= 10;
  if (x == 0) {
    if (neg) { obuf[2] = '-'; goto space1; }
    else goto space2;
  }
  obuf[2] = (x % 10) + '0';
  x /= 10;
  if (x == 0) {
    if (neg) { obuf[1] = '-'; goto space0; }
    else goto space1;
  }
  obuf[1] = (x % 10) + '0';
  x /= 10;
  if (x == 0) {
    if (neg) { obuf[0] = '-'; goto nospace; }
    else goto space0;
  }
  obuf[0] = (x % 10) + '0';
  goto nospace;
  space4: obuf[4] = ' ';
  space3: obuf[3] = ' ';
  space2: obuf[2] = ' ';
  space1: obuf[1] = ' ';
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}
/* doub icvt for tdlfloa7 -> tdlfloa7 */
double _CVT_4( tdlfloa7 x ) {
  return (double) floor(  x  * 1E1 + .5 );
}
char *SL_7_1_f_4( long int x) {
  static char obuf[8];
  int neg;
  int iov;

  if (x < -99999 || x > 999999) return("*******");
  if (x < 0) { neg = 1; x = -x; }
  else neg = 0;
  obuf[7] = '\0';
  obuf[6] = (x % 10) + '0';
  x /= 10;
  obuf[5] = '.';
  obuf[4] = (x % 10) + '0';
  iov = x/10;
  if (iov == 0) {
    if (neg) { obuf[3] = '-'; goto space2; }
    else goto space3;
  }
  obuf[3] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) {
    if (neg) { obuf[2] = '-'; goto space1; }
    else goto space2;
  }
  obuf[2] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) {
    if (neg) { obuf[1] = '-'; goto space0; }
    else goto space1;
  }
  obuf[1] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) {
    if (neg) { obuf[0] = '-'; goto nospace; }
    else goto space0;
  }
  obuf[0] = (iov % 10) + '0';
  goto nospace;
  space3: obuf[3] = ' ';
  space2: obuf[2] = ' ';
  space1: obuf[1] = ' ';
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}
/* _CVT_5() int tcvt tdlfloa7 -> tdlfloa7 */
char *_CVT_5(tdlfloa7 x) {
  double iv;

  iv = _CVT_4( x );
  if ( iv < -99999 || iv > 999999 )
	return "*******";
  return SL_7_1_f_4( iv );
}
/* doub icvt for tdlfloas -> tdlfloas */
double _CVT_6( tdlfloas x ) {
  return (double) floor(  x  * 1E2 + .5 );
}
char *SL_6_2_f_4( long int x) {
  static char obuf[7];
  int neg;
  int iov;

  if (x < -9999 || x > 99999) return("******");
  if (x < 0) { neg = 1; x = -x; }
  else neg = 0;
  obuf[6] = '\0';
  obuf[5] = (x % 10) + '0';
  iov = x/10;
  obuf[4] = (iov % 10) + '0';
  iov /= 10;
  obuf[3] = '.';
  obuf[2] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) {
    if (neg) { obuf[1] = '-'; goto space0; }
    else goto space1;
  }
  obuf[1] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) {
    if (neg) { obuf[0] = '-'; goto nospace; }
    else goto space0;
  }
  obuf[0] = (iov % 10) + '0';
  goto nospace;
  space1: obuf[1] = ' ';
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}
/* _CVT_7() int tcvt tdlfloas -> tdlfloas */
char *_CVT_7(tdlfloas x) {
  double iv;

  iv = _CVT_6( x );
  if ( iv < -9999 || iv > 99999 )
	return "******";
  return SL_6_2_f_4( iv );
}
/* doub icvt for tdlfloat -> tdlfloat */
double _CVT_8( tdlfloat x ) {
  return (double) floor(  x  * 1E2 + .5 );
}
char *SL_8_2_f_4( long int x) {
  static char obuf[9];
  int neg;
  int iov;

  if (x < -999999 || x > 9999999) return("********");
  if (x < 0) { neg = 1; x = -x; }
  else neg = 0;
  obuf[8] = '\0';
  obuf[7] = (x % 10) + '0';
  x /= 10;
  obuf[6] = (x % 10) + '0';
  x /= 10;
  obuf[5] = '.';
  obuf[4] = (x % 10) + '0';
  iov = x/10;
  if (iov == 0) {
    if (neg) { obuf[3] = '-'; goto space2; }
    else goto space3;
  }
  obuf[3] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) {
    if (neg) { obuf[2] = '-'; goto space1; }
    else goto space2;
  }
  obuf[2] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) {
    if (neg) { obuf[1] = '-'; goto space0; }
    else goto space1;
  }
  obuf[1] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) {
    if (neg) { obuf[0] = '-'; goto nospace; }
    else goto space0;
  }
  obuf[0] = (iov % 10) + '0';
  goto nospace;
  space3: obuf[3] = ' ';
  space2: obuf[2] = ' ';
  space1: obuf[1] = ' ';
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}
/* _CVT_9() int tcvt tdlfloat -> tdlfloat */
char *_CVT_9(tdlfloat x) {
  double iv;

  iv = _CVT_8( x );
  if ( iv < -999999 || iv > 9999999 )
	return "********";
  return SL_8_2_f_4( iv );
}
char *SS_4_224_d_0( short int x) {
  static char obuf[5];
  int neg;

  if (x < -999 || x > 9999) return("****");
  if (x < 0) { neg = 1; x = -x; }
  else neg = 0;
  obuf[4] = '\0';
  obuf[3] = (x % 10) + '0';
  x /= 10;
  if (x == 0) {
    if (neg) { obuf[2] = '-'; goto space1; }
    else goto space2;
  }
  obuf[2] = (x % 10) + '0';
  x /= 10;
  if (x == 0) {
    if (neg) { obuf[1] = '-'; goto space0; }
    else goto space1;
  }
  obuf[1] = (x % 10) + '0';
  x /= 10;
  if (x == 0) {
    if (neg) { obuf[0] = '-'; goto nospace; }
    else goto space0;
  }
  obuf[0] = (x % 10) + '0';
  goto nospace;
  space2: obuf[2] = ' ';
  space1: obuf[1] = ' ';
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}
/* _CVT_10() int tcvt o3int4 -> o3int4 */
char *_CVT_10(o3int4 x) {
  if ( x < -999 || x > 9999 )
	return "****";
  return SS_4_224_d_0( x );
}
char *SS_2_224_d_0( short int x) {
  static char obuf[3];
  int neg;

  if (x < -9 || x > 99) return("**");
  if (x < 0) { neg = 1; x = -x; }
  else neg = 0;
  obuf[2] = '\0';
  obuf[1] = (x % 10) + '0';
  x /= 10;
  if (x == 0) {
    if (neg) { obuf[0] = '-'; goto nospace; }
    else goto space0;
  }
  obuf[0] = (x % 10) + '0';
  goto nospace;
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}
/* _CVT_11() int tcvt o3int -> o3int */
char *_CVT_11(o3int x) {
  if ( x < -9 || x > 99 )
	return "**";
  return SS_2_224_d_0( x );
}
/* doub icvt for o3float2 -> o3float2 */
double _CVT_12( o3float2 x ) {
  return (double) floor(  x  * 1E3 + .5 );
}
char *SL_6_3_f_4( long int x) {
  static char obuf[7];
  int neg;
  int iov;

  if (x < -9999 || x > 99999) return("******");
  if (x < 0) { neg = 1; x = -x; }
  else neg = 0;
  obuf[6] = '\0';
  obuf[5] = (x % 10) + '0';
  iov = x/10;
  obuf[4] = (iov % 10) + '0';
  iov /= 10;
  obuf[3] = (iov % 10) + '0';
  iov /= 10;
  obuf[2] = '.';
  obuf[1] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) {
    if (neg) { obuf[0] = '-'; goto nospace; }
    else goto space0;
  }
  obuf[0] = (iov % 10) + '0';
  goto nospace;
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}
/* _CVT_13() int tcvt o3float2 -> o3float2 */
char *_CVT_13(o3float2 x) {
  double iv;

  iv = _CVT_12( x );
  if ( iv < -9999 || iv > 99999 )
	return "******";
  return SL_6_3_f_4( iv );
}
/* doub icvt for o3float -> o3float */
double _CVT_14( o3float x ) {
  return (double) floor(  x  * 1E1 + .5 );
}
/* _CVT_15() int tcvt o3float -> o3float */
char *_CVT_15(o3float x) {
  double iv;

  iv = _CVT_14( x );
  if ( iv < -9999 || iv > 99999 )
	return "******";
  return SL_6_1_f_4( iv );
}
char *US_3_224_u_0( unsigned short int x) {
  static char obuf[4];

  if (x > 999) return("***");
  obuf[3] = '\0';
  obuf[2] = (x % 10) + '0';
  x /= 10;
  if (x == 0) goto space1;
  obuf[1] = (x % 10) + '0';
  x /= 10;
  if (x == 0) goto space0;
  obuf[0] = (x % 10) + '0';
  goto nospace;
  space1: obuf[1] = ' ';
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}
/* _CVT_16() int tcvt valvT -> valvT */
char *_CVT_16(valvT x) {
  if ( x < 0 || x > 999 )
	return "***";
  return US_3_224_u_0( x );
}
char *SS_6_1_f_4( short int x) {
  static char obuf[7];
  int neg;

  if (x < -9999) return("******");
  if (x < 0) { neg = 1; x = -x; }
  else neg = 0;
  obuf[6] = '\0';
  obuf[5] = (x % 10) + '0';
  x /= 10;
  obuf[4] = '.';
  obuf[3] = (x % 10) + '0';
  x /= 10;
  if (x == 0) {
    if (neg) { obuf[2] = '-'; goto space1; }
    else goto space2;
  }
  obuf[2] = (x % 10) + '0';
  x /= 10;
  if (x == 0) {
    if (neg) { obuf[1] = '-'; goto space0; }
    else goto space1;
  }
  obuf[1] = (x % 10) + '0';
  x /= 10;
  if (x == 0) {
    if (neg) { obuf[0] = '-'; goto nospace; }
    else goto space0;
  }
  obuf[0] = (x % 10) + '0';
  goto nospace;
  space2: obuf[2] = ' ';
  space1: obuf[1] = ' ';
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}
/* _CVT_17() int tcvt OmegaTsp -> OmegaTsp */
char *_CVT_17(OmegaTsp x) {
  if ( x < -9999 )
	return "******";
  return SS_6_1_f_4( x );
}
/* _CVT_18() int tcvt OmegaT -> OmegaT */
char *_CVT_18(OmegaT x) {
  if ( x < -9999 )
	return "******";
  return SS_6_1_f_4( x );
}
/* doub_cvt for PSIH -> PRESS */
double _CVT_19( PSIH x ) {
  double ov;

  if (x <= -1e-005) {
    ov = -999.9;
  } else {
    if (x <= 0) {
      ov = 99990000 * x;
    } else {
      ov = 1000 * x;
    }
  }
  return(ov);
}
/* doub icvt for PSIH -> PRESS */
double _CVT_20( PSIH x ) {
  return (double) floor( _CVT_19( x ) * 1E1 + .5 );
}
/* _CVT_21() int tcvt PSIH -> PRESS */
char *_CVT_21(PSIH x) {
  double iv;

  iv = _CVT_20( x );
  if ( iv < -9999 || iv > 99999 )
	return "******";
  return SL_6_1_f_4( iv );
}
/* doub_cvt for PSIL -> PRESS */
double _CVT_22( PSIL x ) {
  double ov;

  if (x <= -1e-005) {
    ov = -999.9;
  } else {
    if (x <= 0) {
      ov = 97990000 * x-20;
    } else {
      ov = 34 * x-20;
    }
  }
  return(ov);
}
/* doub icvt for PSIL -> PRESS */
double _CVT_23( PSIL x ) {
  return (double) floor( _CVT_22( x ) * 1E1 + .5 );
}
/* _CVT_24() int tcvt PSIL -> PRESS */
char *_CVT_24(PSIL x) {
  double iv;

  iv = _CVT_23( x );
  if ( iv < -9999 || iv > 99999 )
	return "******";
  return SL_6_1_f_4( iv );
}
/* doub_cvt for PSI -> PRESS */
double _CVT_25( PSI x ) {
  double ov;

  if (x <= -1e-005) {
    ov = -999.9;
  } else {
    if (x <= 0) {
      ov = 99990000 * x;
    } else {
      ov = 6 * x;
    }
  }
  return(ov);
}
/* doub icvt for PSI -> PRESS */
double _CVT_26( PSI x ) {
  return (double) floor( _CVT_25( x ) * 1E1 + .5 );
}
/* _CVT_27() int tcvt PSI -> PRESS */
char *_CVT_27(PSI x) {
  double iv;

  iv = _CVT_26( x );
  if ( iv < -9999 || iv > 99999 )
	return "******";
  return SL_6_1_f_4( iv );
}
/* doub_cvt for SCCMsl -> FLOW */
double _CVT_28( SCCMsl x ) {
  double ov;

  if (x <= 0.5) {
    if (x <= -0.01) {
      ov = -999.9;
    } else {
      if (x <= 0) {
        ov = 99890 * x-1;
      } else {
        ov = 2 * x-1;
      }
    }
  } else {
    if (x <= 1.2) {
      ov = 62.571429 * x-31.285714;
    } else {
      if (x <= 1.8) {
        ov = 101 * x-77.4;
      } else {
        ov = 139 * x-145.8;
      }
    }
  }
  return(ov);
}
/* doub icvt for SCCMsl -> FLOW */
double _CVT_29( SCCMsl x ) {
  return (double) floor( _CVT_28( x ) * 1E1 + .5 );
}
/* _CVT_30() int tcvt SCCMsl -> FLOW */
char *_CVT_30(SCCMsl x) {
  double iv;

  iv = _CVT_29( x );
  if ( iv < -9999 || iv > 99999 )
	return "******";
  return SL_6_1_f_4( iv );
}
/* doub_cvt for SCCMsp -> FLOW */
double _CVT_31( SCCMsp x ) {
  double ov;

  if (x <= 0.99999) {
    ov = -999.9;
  } else {
    if (x <= 1) {
      ov = 99990000 * x-99990000;
    } else {
      ov = 37.5 * x-37.5;
    }
  }
  return(ov);
}
/* doub icvt for SCCMsp -> FLOW */
double _CVT_32( SCCMsp x ) {
  return (double) floor( _CVT_31( x ) * 1E1 + .5 );
}
/* _CVT_33() int tcvt SCCMsp -> FLOW */
char *_CVT_33(SCCMsp x) {
  double iv;

  iv = _CVT_32( x );
  if ( iv < -9999 || iv > 99999 )
	return "******";
  return SL_6_1_f_4( iv );
}
/* doub_cvt for SCCM -> FLOW */
double _CVT_34( SCCM x ) {
  double ov;

  if (x <= 0) {
    if (x <= -0.01) {
      ov = -999.9;
    } else {
      ov = 99890 * x-1;
    }
  } else {
    if (x <= 0.5) {
      ov = 2 * x-1;
    } else {
      ov = 75 * x-37.5;
    }
  }
  return(ov);
}
/* doub icvt for SCCM -> FLOW */
double _CVT_35( SCCM x ) {
  return (double) floor( _CVT_34( x ) * 1E1 + .5 );
}
/* _CVT_36() int tcvt SCCM -> FLOW */
char *_CVT_36(SCCM x) {
  double iv;

  iv = _CVT_35( x );
  if ( iv < -9999 || iv > 99999 )
	return "******";
  return SL_6_1_f_4( iv );
}
/* doub_cvt for CELS -> TEMP */
double _CVT_37( CELS x ) {
  double ov;

  if (x <= -1e-005) {
    ov = -999.9;
  } else {
    if (x <= 0) {
      ov = 1.0989e+008 * x+99;
    } else {
      ov = -28.6 * x+99;
    }
  }
  return(ov);
}
/* doub icvt for CELS -> TEMP */
double _CVT_38( CELS x ) {
  return (double) floor( _CVT_37( x ) * 1E1 + .5 );
}
/* _CVT_39() int tcvt CELS -> TEMP */
char *_CVT_39(CELS x) {
  double iv;

  iv = _CVT_38( x );
  if ( iv < -9999 || iv > 99999 )
	return "******";
  return SL_6_1_f_4( iv );
}
/* doub_cvt for MBAR -> PRESS */
double _CVT_40( MBAR x ) {
  double ov;

  if (x <= 0) {
    if (x <= -2e-005) {
      ov = -999.9;
    } else {
      ov = 49945000 * x-1;
    }
  } else {
    if (x <= 0.2) {
      ov = 5 * x-1;
    } else {
      ov = 451.35135 * x-90.27027;
    }
  }
  return(ov);
}
/* doub icvt for MBAR -> PRESS */
double _CVT_41( MBAR x ) {
  return (double) floor( _CVT_40( x ) * 1E1 + .5 );
}
/* _CVT_42() int tcvt MBAR -> PRESS */
char *_CVT_42(MBAR x) {
  double iv;

  iv = _CVT_41( x );
  if ( iv < -9999 || iv > 99999 )
	return "******";
  return SL_6_1_f_4( iv );
}
/* doub_cvt for VOLTS28 -> VOL5 */
double _CVT_43( VOLTS28 x ) {
  double ov;

  if (x <= -1e-005) {
    ov = -999.9;
  } else {
    if (x <= 0) {
      ov = 99990000 * x;
    } else {
      ov = 6.8 * x;
    }
  }
  return(ov);
}
/* doub icvt for VOLTS28 -> VOL5 */
double _CVT_44( VOLTS28 x ) {
  return (double) floor( _CVT_43( x ) * 1E1 + .5 );
}
/* _CVT_45() int tcvt VOLTS28 -> VOL5 */
char *_CVT_45(VOLTS28 x) {
  double iv;

  iv = _CVT_44( x );
  if ( iv < -9999 || iv > 99999 )
	return "******";
  return SL_6_1_f_4( iv );
}
/* doub_cvt for VOLTSPM -> VOL5 */
double _CVT_46( VOLTSPM x ) {
  double ov;

  if (x <= -5.0001) {
    ov = -999.9;
  } else {
    if (x <= -5) {
      ov = 9840000 * x+49199984;
    } else {
      ov = 3.18 * x;
    }
  }
  return(ov);
}
/* doub icvt for VOLTSPM -> VOL5 */
double _CVT_47( VOLTSPM x ) {
  return (double) floor( _CVT_46( x ) * 1E1 + .5 );
}
/* _CVT_48() int tcvt VOLTSPM -> VOL5 */
char *_CVT_48(VOLTSPM x) {
  double iv;

  iv = _CVT_47( x );
  if ( iv < -9999 || iv > 99999 )
	return "******";
  return SL_6_1_f_4( iv );
}
/* doub_cvt for VOLTS512 -> VOL5 */
double _CVT_49( VOLTS512 x ) {
  double ov;

  if (x <= -1e-005) {
    ov = -999.9;
  } else {
    if (x <= 0) {
      ov = 99990000 * x;
    } else {
      ov = 3.16 * x;
    }
  }
  return(ov);
}
/* doub icvt for VOLTS512 -> VOL5 */
double _CVT_50( VOLTS512 x ) {
  return (double) floor( _CVT_49( x ) * 1E1 + .5 );
}
/* _CVT_51() int tcvt VOLTS512 -> VOL5 */
char *_CVT_51(VOLTS512 x) {
  double iv;

  iv = _CVT_50( x );
  if ( iv < -9999 || iv > 99999 )
	return "******";
  return SL_6_1_f_4( iv );
}
char *SL_6_224_d_8( long int x) {
  static char obuf[7];
  int neg;
  int iov;

  if (x < -99999 || x > 999999) return("******");
  if (x < 0) { neg = 1; x = -x; }
  else neg = 0;
  obuf[6] = '\0';
  obuf[5] = (x % 10) + '0';
  x /= 10;
  if (x == 0) {
    if (neg) { obuf[4] = '-'; goto space3; }
    else goto space4;
  }
  obuf[4] = (x % 10) + '0';
  iov = x/10;
  if (iov == 0) {
    if (neg) { obuf[3] = '-'; goto space2; }
    else goto space3;
  }
  obuf[3] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) {
    if (neg) { obuf[2] = '-'; goto space1; }
    else goto space2;
  }
  obuf[2] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) {
    if (neg) { obuf[1] = '-'; goto space0; }
    else goto space1;
  }
  obuf[1] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) {
    if (neg) { obuf[0] = '-'; goto nospace; }
    else goto space0;
  }
  obuf[0] = (iov % 10) + '0';
  goto nospace;
  space4: obuf[4] = ' ';
  space3: obuf[3] = ' ';
  space2: obuf[2] = ' ';
  space1: obuf[1] = ' ';
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}
/* _CVT_52() int tcvt GC_Freq -> GC_Freq */
char *_CVT_52(GC_Freq x) {
  if ( x < -99999 || x > 999999 )
	return "******";
  return SL_6_224_d_8( x );
}
char *UL_6_0_u_0( unsigned long int x) {
  static char obuf[7];
  int iov;

  if (x > 999999) return("******");
  obuf[6] = '\0';
  obuf[5] = (x % 10) + '0';
  x /= 10;
  if (x == 0) goto space4;
  obuf[4] = (x % 10) + '0';
  iov = x/10;
  if (iov == 0) goto space3;
  obuf[3] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) goto space2;
  obuf[2] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) goto space1;
  obuf[1] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) goto space0;
  obuf[0] = (iov % 10) + '0';
  goto nospace;
  space4: obuf[4] = ' ';
  space3: obuf[3] = ' ';
  space2: obuf[2] = ' ';
  space1: obuf[1] = ' ';
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}
/* _CVT_53() int tcvt ULONG -> ULONG */
char *_CVT_53(ULONG x) {
  if ( x > 999999 )
	return "******";
  return UL_6_0_u_0( x );
}
char *US_5_0_u_0( unsigned short int x) {
  static char obuf[6];
  int iov;

  obuf[5] = '\0';
  obuf[4] = (x % 10) + '0';
  iov = x/10;
  if (iov == 0) goto space3;
  obuf[3] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) goto space2;
  obuf[2] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) goto space1;
  obuf[1] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) goto space0;
  obuf[0] = (iov % 10) + '0';
  goto nospace;
  space3: obuf[3] = ' ';
  space2: obuf[2] = ' ';
  space1: obuf[1] = ' ';
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}

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
    case 1: /* MaycommInc */
      V23 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* MaycommTog */
      V7 &= ~0x1;
      break;
    case 1: /* MaycommInc */ {
        V23 &= ~0x1;
        {
          rtg_increment( TDLbest_rtginc, 2 );
        }
      }
      break;
  }
}
static void VSET_3_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 2: /* OzoneTog */
      V4 |= 0x1;
      break;
    case 1: /* OzoneInc */ {
        V22 |= 0x1;
        V21 |= 0x1;
        V20 |= 0x1;
        V18 |= 0x1;
        V17 |= 0x1;
        V16 |= 0x1;
      }
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* OzoneTog */
      V4 &= ~0x1;
      break;
    case 1: /* OzoneInc */ {
        V22 &= ~0x1;
        V21 &= ~0x1;
        V20 &= ~0x1;
        V18 &= ~0x1;
        V17 &= ~0x1;
        V16 &= ~0x1;
        {
          rtg_increment( ozoneConc_rtginc, 2 );
          rtg_increment( ozonePres_rtginc, 2 );
          rtg_increment( ozoneTemp_rtginc, 2 );
          rtg_increment( ozoneXConc_rtginc, 2 );
          rtg_increment( ozoneXPres_rtginc, 2 );
          rtg_increment( ozoneXTemp_rtginc, 2 );
        }
      }
      break;
  }
}
static void VSET_2_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 2: /* GCTog */
      V2 |= 0x1;
      break;
    case 1: /* GCInc */ {
        V14 |= 0x1;
        V13 |= 0x1;
      }
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* GCTog */
      V2 &= ~0x1;
      break;
    case 1: /* GCInc */ {
        V14 &= ~0x1;
        V13 &= ~0x1;
        {
          rtg_increment( chromCH2_rtginc, 2 );
          rtg_increment( chromCH1_rtginc, 2 );
        }
      }
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
    case 4: /* Injecting2 */
      V11 |= 0x1;
      break;
    case 3: /* Injection */ {
        V12 |= 0x1;
        V1 |= 0x1;
      }
      break;
    case 2: /* Injecting1 */ {
        V10 |= 0x1;
        V3 |= 0x1;
      }
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 4: /* Injecting2 */ {
        V11 &= ~0x1;
        { secondhalf = 1; }
      }
      break;
    case 3: /* Injection */ {
        V12 &= ~0x1;
        V1 &= ~0x1;
      }
      break;
    case 2: /* Injecting1 */ {
        V10 &= ~0x1;
        V3 &= ~0x1;
        { secondhalf = 0; }
      }
      break;
    case 1: /* NotInjecting */ {
        {
        
        	N2Oint.mol = "n2o";		
        	N2Oint.pnum = 0;		
        	N2Oint.strt = 43;		
        	N2Oint.stop = 67;		
        	N2Oint.calval = 328.73;	
        	N2Oint.calssv = 1;		
        	N2Oint.delay = 0;		
        	N2Oint.rt_a = 1.0;		
        	N2Oint.rt_b = 0.0;		
        
        	CH4int.mol = "ch4";		
        	CH4int.pnum = 1;		
        	CH4int.strt = 3;		
        	CH4int.stop = 25;		
        	CH4int.calval = 1914.5;	
        	CH4int.calssv = 1;		
        	CH4int.delay = 70;		
        	CH4int.rt_a = 1.0;		
        	CH4int.rt_b = 0.0;		
        
        	SF6int.mol = "sf6";		
        	SF6int.pnum = 2;		
        	SF6int.strt = 30;		
        	SF6int.stop = 43;		
        	SF6int.calval = 9.024;	
        	SF6int.calssv = 1;		
        	SF6int.delay = 0;		
        	SF6int.rt_a = 1.0;		
        	SF6int.rt_b = 0.0;		
        
        } { secondhalf = 0; }
      }
      break;
  }
}
static void tminitfunc(void) {VSET_0_(1);VSET_1_(1);VSET_2_(1);VSET_3_(1);VSET_4_(1);VSET_5_(1);
  cdisplay(0,10,27,Inject_Load_text[0]);
  cdisplay(0,11,13,_CVT_52(0));
  cdisplay(0,12,13,_CVT_36(0));
  cdisplay(0,12,20,_CVT_33(0));
  cdisplay(0,13,13,_CVT_36(0));
  cdisplay(0,13,20,_CVT_33(0));
  cdisplay(0,15,13,_CVT_42(0));
  cdisplay(0,16,13,_CVT_18(0));
  cdisplay(0,16,20,_CVT_17(0));
  cdisplay(0,17,13,_CVT_18(0));
  cdisplay(0,17,20,_CVT_17(0));
  cdisplay(0,18,13,_CVT_51(0));
  cdisplay(0,20,7,_CVT_1(0));
  cdisplay(0,10,66,Inject_Load_text[0]);
  cdisplay(0,11,52,_CVT_52(0));
  cdisplay(0,12,52,_CVT_36(0));
  cdisplay(0,12,59,_CVT_33(0));
  cdisplay(0,13,52,_CVT_36(0));
  cdisplay(0,13,59,_CVT_33(0));
  cdisplay(0,15,52,_CVT_42(0));
  cdisplay(0,16,52,_CVT_18(0));
  cdisplay(0,16,59,_CVT_17(0));
  cdisplay(0,17,52,_CVT_18(0));
  cdisplay(0,17,59,_CVT_17(0));
  cdisplay(0,18,52,_CVT_18(0));
  cdisplay(0,18,59,_CVT_17(0));
  cdisplay(0,20,46,_CVT_1(0));
  cdisplay(0,20,63,_CVT_1(0));
  cdisplay(0,2,37,_CVT_39(0));
  cdisplay(0,3,37,_CVT_39(0));
  cdisplay(0,4,37,_CVT_39(0));
  cdisplay(0,5,37,_CVT_39(0));
  cdisplay(0,6,37,_CVT_39(0));
  cdisplay(0,7,37,_CVT_39(0));
  cdisplay(0,1,20,Air_Cal_text[0]);
  cdisplay(0,2,12,_CVT_30(0));
  cdisplay(0,3,12,_CVT_42(0));
  cdisplay(0,4,6,Op_Cl_text[0]);
  cdisplay(0,4,18,Cl_Op_text[0]);
  cdisplay(0,6,11,_CVT_16(0));
  cdisplay(0,7,11,Cl_Op_text[0]);
  cdisplay(0,1,62,_CVT_51(0));
  cdisplay(0,2,62,_CVT_48(0));
  cdisplay(0,3,62,_CVT_45(0));
  cdisplay(0,4,56,_CVT_24(0));
  cdisplay(0,4,71,_CVT_24(0));
  cdisplay(0,5,56,_CVT_24(0));
  cdisplay(0,5,71,_CVT_27(0));
  cdisplay(0,6,62,_CVT_21(0));
  cdisplay(0,7,62,_CVT_42(0));
  cdisplay(0,8,62,_CVT_42(0));
  cdisplay(0,22,15,_CVT_53(0));
  cdisplay(0,23,15,_CVT_53(0));
  cdisplay(0,24,16,US_5_0_u_0(0));
  cdisplay(0,22,38,HI_LO_text[0]);
  cdisplay(0,23,38,HI_LO_text[0]);
  cdisplay(0,24,38,On_Off_text[0]);
  cdisplay(0,23,50,_CVT_15(0));
  cdisplay(0,23,63,_CVT_15(0));
  cdisplay(0,24,50,_CVT_15(0));
  cdisplay(0,24,63,_CVT_15(0));
  cdisplay(0,25,53,_CVT_15(0));
  cdisplay(0,25,67,_CVT_15(0));
  cdisplay(0,26,53,_CVT_15(0));
  cdisplay(0,26,67,_CVT_15(0));
  cdisplay(0,27,56,_CVT_13(0));
  cdisplay(0,27,68,_CVT_13(0));
  cdisplay(0,28,57,_CVT_10(0));
  cdisplay(0,28,66,_CVT_10(0));
  cdisplay(0,29,53,_CVT_10(0));
  cdisplay(0,29,58,_CVT_11(0));
  cdisplay(0,29,61,_CVT_11(0));
  cdisplay(0,29,64,_CVT_11(0));
  cdisplay(0,29,67,_CVT_11(0));
  cdisplay(0,29,70,_CVT_11(0));
  cdisplay(1,2,7,_CVT_7(0));
  cdisplay(1,2,14,_CVT_7(0));
  cdisplay(1,3,9,_CVT_7(0));
  cdisplay(1,4,11,_CVT_9(0));
  cdisplay(1,6,9,_CVT_18(0));
  cdisplay(1,7,9,_CVT_17(0));
  cdisplay(1,2,30,_CVT_5(0));
  cdisplay(1,3,30,_CVT_5(0));
  cdisplay(1,4,32,SS_6_224_d_0(0));
  cdisplay(1,5,32,SS_6_224_d_0(0));
  cdisplay(1,6,32,SS_6_224_d_0(0));
  cdisplay(1,7,32,SS_6_224_d_0(0));
  cdisplay(1,2,47,_CVT_9(0));
  cdisplay(1,3,47,_CVT_9(0));
  cdisplay(1,4,47,SS_6_224_d_0(0));
  cdisplay(1,6,47,_CVT_3(0));
  cdisplay(1,7,47,_CVT_3(0));
}
#define TMINITFUNC tminitfunc()

static void nullfunc(void);
static void EF1_0(void) {
  {
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
  {if (!(V12)) {
    {
    	
    		if (( home->U0.GC_Ctr_CH1 != ECDOFFLINE ) && ( secondhalf )) {
    			integrate( 0, home->U0.GC_Ctr_CH1, CH4int, CHROMtime, old_ssv2min );
    		}
    
    		if ( home->U0.GC_Ctr_CH2 != ECDOFFLINE ) {
    			integrate( 0, home->U0.GC_Ctr_CH2, N2Oint, CHROMtime, old_ssv1min );
    		}
    
    		if ( home->U0.GC_Ctr_CH2 != ECDOFFLINE ) {
    			integrate( 0, home->U0.GC_Ctr_CH2, SF6int, CHROMtime, old_ssv1min );
    		}
    
    	}
  }
  
  }
  if ( home->U0.GC_Ctr_CH2 >= 0 )if (!(V13)) {
    {
      	rtg_report( chromCH2_rtg[ chromCH2_rtginc ], ecdCH2x, home->U0.GC_Ctr_CH2 );
    }
  }
  if ( home->U0.GC_Ctr_CH1 >= 0 )if (!(V14)) {
    {
      	rtg_report( chromCH1_rtg[ chromCH1_rtginc ], ecdCH1x, home->U0.GC_Ctr_CH1 );
    }
  }
}

static void BF8_0(void) {
  EF1_0();
  {
      if (maycomm_proxy != 0)  Trigger (maycomm_proxy);
  }
  display_(1,2,7, 
   tdlfloas,home->U29.tdl_t,_CVT_7(home->U29.tdl_t));
  display_(1,2,14, 
   tdlfloas,home->U29.tdl_elecT,_CVT_7(home->U29.tdl_elecT));
  display_(1,3,9,
   
   tdlfloas,home->U29.tdl_p,_CVT_7(home->U29.tdl_p));
  display_(1,4,32, 
   tdlint6,home->U19.tdl_amp,SS_6_224_d_0(home->U19.tdl_amp));
  display_(1,5,32,
   tdlint6,home->U19.tdl_pow,SS_6_224_d_0(home->U19.tdl_pow));
  display_(1,6,32,
   tdlint6,home->U24.tdl_pos,SS_6_224_d_0(home->U24.tdl_pos));
  display_(1,7,32,
   tdlint6,home->U24.tdl_zer,SS_6_224_d_0(home->U24.tdl_zer));
  display_(1,4,47,
   tdlint6,home->U24.tdl_posB,SS_6_224_d_0(home->U24.tdl_posB));
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
    	}
  }
  
  	if ( ecdCH2x > NUMSECSXAXIS ) { VSET_2_(2);
  		ecdCH1x = 0.0;
  		ecdCH2x = 0.0;
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
  	} {
    display_(0,11,52,
    
    GC_Freq,ecdA_CH2,_CVT_52(ecdA_CH2));
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
  	} {
    display_(0,11,13,
    
    GC_Freq,ecdA_CH1,_CVT_52(ecdA_CH1));
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
  { 
  	MR_N2O = MRres( 0 ); {
    display_(0,20,46,
    MixRatio,MR_N2O,_CVT_1(MR_N2O));
  }
  }
  { 
  	MR_CH4 = MRres( 1 ); {
    display_(0,20,7,
    
    MixRatio,MR_CH4,_CVT_1(MR_CH4));
  }
  }
  { 
  	MR_SF6 = MRres( 2 ); {
    display_(0,20,63,
    MixRatio,MR_SF6,_CVT_1(MR_SF6));
  }
  }
}

static void BF128_0(void) {
  BF16_0();
  {
  	if (o3_proxy != 0)	Trigger ( o3_proxy );
  }
}

static void BF8_1(void) {
  memcpy(&tdlrec, home->U26.U28, 2);
  tdl_longH2O = home->U22.tdl_longH2O;
  V8 &= ~0x1;
  EF1_0();
  display_(1,2,30,
   tdlfloa7,home->U26.tdl_shortH2O,_CVT_5(home->U26.tdl_shortH2O));
  display_(1,3,30,
   tdlfloa7,home->U17.tdl_H2OB,_CVT_5(home->U17.tdl_H2OB));
  display_(1,2,47,
   tdlfloat,tdl_longH2O,_CVT_9(tdl_longH2O));
  display_(1,3,47,
   tdlfloat,home->U22.tdl_H2OCD,_CVT_9(home->U22.tdl_H2OCD));
}

static void EF8_2(void) {
  memcpy(((char*)(&tdlrec))+2, home->U19.U21, 2);
  EF1_0();
  home->U19.maycX++;
  {if (!(V7)) {
    { VSET_4_(1);}
  }
  
      if (home->U19.maycX >= 120) {
          home->U19.maycX = 0; VSET_4_(2);
      }
  }
  if (!(V8)) {
    {
    	old_tdl_best = home->U24.tdl_best;
        home->U24.tdl_best = tdl_longH2O;
        if (home->U24.tdl_best < 0) home->U24.tdl_best = 0;
    }
  }
  if (( home->U24.tdl_best != old_tdl_best ) && (home->U24.tdl_best > 0)) {if (!(V23)) {
    {
      	rtg_report( TDLbest_rtg[ TDLbest_rtginc ], home->U19.maycX, home->U24.tdl_best );
    }
  }
  }
  display_(1,4,11,
  
   tdlfloat,home->U24.tdl_best,_CVT_9(home->U24.tdl_best));
}

static void BF16_2(void) {
  CHROMtime = home->U1.CHROMtime; {
    V12 &= ~0x2;
    V0 &= ~0x1;
  }
  EF8_2();
  display_(0,22,15,
  
   ULONG,CHROMtime,_CVT_53(CHROMtime));
  display_(1,6,47, 
   vaifloat,home->U31.vaiT,_CVT_3(home->U31.vaiT));
  display_(1,7,47,
  
   vaifloat,home->U31.vaiRH,_CVT_3(home->U31.vaiRH));
}

static void BF16_3(void) {
  o3x = home->U22.o3x;
  o3xtemp = home->U13.o3xtemp;
  o3xpres = home->U17.o3xpres; {
    V19 &= ~0x1;
    V6 &= ~0x1;
  }
  EF1_0();
  display_(0,10,27,
  
   valvetext,home->U17.valv_CH1,Inject_Load_text[home->U17.valv_CH1]);
  display_(0,10,66,
   valvetext,home->U17.valv_CH2,Inject_Load_text[home->U17.valv_CH2]);
  display_(0,6,11,
   valvT,home->U19.valv_calSSV,_CVT_16(home->U19.valv_calSSV));
  display_(0,24,50, 
  
  
   o3float,o3x,_CVT_15(o3x));
  display_(0,26,53, 
   o3float,o3xpres,_CVT_15(o3xpres));
  display_(0,26,67, 
   o3float,o3xtemp,_CVT_15(o3xtemp));
  display_(0,28,57, 
   o3int4,home->U15.o3xflowa,_CVT_10(home->U15.o3xflowa));
  display_(0,28,66, 
   o3int4,home->U15.o3xflowb,_CVT_10(home->U15.o3xflowb));
}

static void BF16_4(void) {
  EF1_0();
  home->U0.CUMSEC++;
  display_(0,13,13,
   SCCM,home->U1.flow_BF1,_CVT_36(home->U1.flow_BF1));
  display_(0,13,20,
   SCCMsp,home->U1.flow_BF1_sp,_CVT_33(home->U1.flow_BF1_sp));
  display_(0,17,13,
   OmegaT,home->U5.CH1_Col,_CVT_18(home->U5.CH1_Col));
  display_(0,13,52,
   SCCM,home->U7.flow_BF2,_CVT_36(home->U7.flow_BF2));
  display_(0,13,59,
   SCCMsp,home->U9.flow_BF2_sp,_CVT_33(home->U9.flow_BF2_sp));
  display_(0,23,15,
   ULONG,home->U0.CUMSEC,_CVT_53(home->U0.CUMSEC));
}

static void BF16_5(void) {
  EF1_0();
  display_(0,12,13,
  
  
  
  
   SCCM,home->U1.flow_M1,_CVT_36(home->U1.flow_M1));
  display_(0,12,20,
   SCCMsp,home->U0.flow_M1_sp,_CVT_33(home->U0.flow_M1_sp));
  display_(0,17,20,
   OmegaTsp,home->U13.CH1_Col_Sp,_CVT_17(home->U13.CH1_Col_Sp));
  display_(0,12,52,
  
  
  
   SCCM,home->U5.flow_M2,_CVT_36(home->U5.flow_M2));
  display_(0,12,59,
   SCCMsp,home->U5.flow_M2_sp,_CVT_33(home->U5.flow_M2_sp));
  display_(0,2,12,
   SCCMsl,home->U7.flow_SL,_CVT_30(home->U7.flow_SL));
}

static void BF16_6(void) {
  O3count = home->U15.O3count;
  o3best = home->U17.o3best; {
    V18 &= ~0x2;
    V17 &= ~0x2;
    V16 &= ~0x2;
    V5 &= ~0x1;
  }
  EF1_0();
  O3count++;
  {if (!(V4)) {
    { VSET_3_(1); }
  }
  
  	if ( O3count >= 60*60/10 ) { 
  		O3count = 0; VSET_3_(2);
  	}
  }
  if (!(V6)) {
    {
    	home->U15.o3xbest = 0.927*((o3x-3.0) * o3xpres)/(o3xpres*1.00095 + 3.23) ;
    }
  }
  if (!(V19)) {
    if ( o3xpres > 0 ) {if (!(V20)) {
      {
        	rtg_report( ozoneXConc_rtg[ ozoneXConc_rtginc ], O3count, o3x );
      }
    }if (!(V21)) {
      {
        	rtg_report( ozoneXPres_rtg[ ozoneXPres_rtginc ], O3count, o3xpres );
      }
    }if (!(V22)) {
      {
        	rtg_report( ozoneXTemp_rtg[ ozoneXTemp_rtginc ], O3count, o3xtemp );
      }
    }
    }
  }
  display_(0,16,13,
   OmegaT,home->U3.CH1_ECD,_CVT_18(home->U3.CH1_ECD));
  display_(0,5,71,
   PSI,home->U1.pres_BP1,_CVT_27(home->U1.pres_BP1));
  display_(0,23,63, 
  
   o3float,o3best,_CVT_15(o3best));
  display_(0,24,63,
   o3float,home->U15.o3xbest,_CVT_15(home->U15.o3xbest));
}

static void BF16_7(void) {
  EF1_0();
  display_(0,15,13,
   MBAR,home->U3.pres_ECD2,_CVT_42(home->U3.pres_ECD2));
  display_(0,16,20,
   OmegaTsp,home->U11.CH1_ECD_Sp,_CVT_17(home->U11.CH1_ECD_Sp));
  display_(0,15,52,
   MBAR,home->U3.pres_ECD2,_CVT_42(home->U3.pres_ECD2));
  display_(0,3,12,
   MBAR,home->U5.pres_SL,_CVT_42(home->U5.pres_SL));
  display_(0,7,62,
   MBAR,home->U7.pres_extern,_CVT_42(home->U7.pres_extern));
  display_(0,8,62,
   MBAR,home->U9.pres_PUMP,_CVT_42(home->U9.pres_PUMP));
}

static void BF16_10(void) {
  EF8_2();
  display_(0,4,56,
   PSIL,home->U0.presL_cal,_CVT_24(home->U0.presL_cal));
  display_(0,4,71,
   PSIL,home->U15.presL_dope,_CVT_24(home->U15.presL_dope));
  display_(0,6,62,
   PSIH,home->U0.presH_123,_CVT_21(home->U0.presH_123));
}

static void BF16_11(void) {
  EF1_0();
  display_(0,17,52,
   OmegaT,home->U0.CH2_Col,_CVT_18(home->U0.CH2_Col));
  display_(0,2,37,
   CELS,home->U7.temp_amb,_CVT_39(home->U7.temp_amb));
  display_(0,3,37,
   CELS,home->U11.temp_pump,_CVT_39(home->U11.temp_pump));
  display_(0,4,37,
   CELS,home->U3.temp_gasB_N,_CVT_39(home->U3.temp_gasB_N));
  display_(0,5,37,
  
   CELS,home->U3.temp_gasB_C,_CVT_39(home->U3.temp_gasB_C));
  display_(0,5,56,
   PSIL,home->U7.presL_N2,_CVT_24(home->U7.presL_N2));
}

static void BF16_12(void) {
  EF1_0();
  home->U22.vaisX++;
  {if (!(V9)) {
    { VSET_5_(1); }
  }
  
  	if ( home->U22.vaisX >= 120 ) { 
  		home->U22.vaisX = 0; VSET_5_(2);
  	}
  }
  display_(0,18,13,
  
  
  
  
   VOLTS512,home->U13.volt_1234,_CVT_51(home->U13.volt_1234));
  display_(0,17,59,
   OmegaTsp,home->U9.CH2_Col_Sp,_CVT_17(home->U9.CH2_Col_Sp));
  display_(0,6,37,
   CELS,home->U3.temp_SL1,_CVT_39(home->U3.temp_SL1));
  display_(0,7,37,
   CELS,home->U5.temp_SL2,_CVT_39(home->U5.temp_SL2));
  display_(0,2,62,
   VOLTSPM,home->U13.volt_15,_CVT_48(home->U13.volt_15));
}

static void BF16_13(void) {
  EF1_0();
  { ITXFileNum = home->U0.CurrInj * 1000 + home->U1.CurrFile;
  }
  display_(0,16,52,
  
  
  
  
   OmegaT,home->U9.CH2_ECD,_CVT_18(home->U9.CH2_ECD));
  display_(0,16,59,
  
   OmegaTsp,home->U9.CH2_ECD_Sp,_CVT_17(home->U9.CH2_ECD_Sp));
  display_(0,18,52,
   OmegaT,home->U15.CH2_Post,_CVT_18(home->U15.CH2_Post));
  display_(0,18,59,
   OmegaTsp,home->U11.CH2_Post_Sp,_CVT_17(home->U11.CH2_Post_Sp));
  display_(0,1,62,
   VOLTS512,home->U9.volt_5,_CVT_51(home->U9.volt_5));
  display_(0,3,62,
   VOLTS28,home->U9.volt_28,_CVT_45(home->U9.volt_28));
  display_(0,24,16,
   UINT,home->U0.CurrInj,US_5_0_u_0(home->U0.CurrInj));
  display_(1,6,9,
   OmegaT,home->U7.H2O_Pelt,_CVT_18(home->U7.H2O_Pelt));
}

static void BF16_14(void) {
  EF1_0();
  display_(0,7,11,
   Bit_Cl_Op,home->U11.N2_IN,Cl_Op_text[home->U11.N2_IN]);
  display_(0,22,38,
  
  
   Bit_HI_LO,home->U11.ManSwitch,HI_LO_text[home->U11.ManSwitch]);
  display_(0,23,38,
   Bit_HI_LO,home->U11.KeySwitch,HI_LO_text[home->U11.KeySwitch]);
  display_(0,29,53, 
   o3int4,home->U24.o3xyy,_CVT_10(home->U24.o3xyy));
  display_(0,29,58, 
   o3int,home->U24.o3xmm,_CVT_11(home->U24.o3xmm));
  display_(0,29,61, 
   o3int,home->U26.o3xdd,_CVT_11(home->U26.o3xdd));
  display_(0,29,64, 
   o3int,home->U24.o3xhh,_CVT_11(home->U24.o3xhh));
  display_(0,29,67,
   o3int,home->U24.o3xmin,_CVT_11(home->U24.o3xmin));
  display_(0,29,70,
   o3int,home->U24.o3xss,_CVT_11(home->U24.o3xss));
  display_(1,7,9,
   OmegaTsp,home->U11.H2O_Pelt_Sp,_CVT_17(home->U11.H2O_Pelt_Sp));
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
    	old_ssv2min = home->U13.ssv;
    	old_ssv1min = home->U13.ssv;
    }
  }
  if (!(V11)) {
    {
    	old_ssv1min = home->U13.ssv;
    }
  }
  display_(0,1,20,
  
  
   Bit_Air_Cal,home->U13.ssv,Air_Cal_text[home->U13.ssv]);
  display_(0,4,6,
   Bit_Op_Cl,home->U13.SLoopIN,Op_Cl_text[home->U13.SLoopIN]);
  display_(0,4,18,
   Bit_Cl_Op,home->U13.SLoopOUT,Cl_Op_text[home->U13.SLoopOUT]);
  display_(0,24,38,
  
   Bit_On_Off,home->U13.PumpSwitch,On_Off_text[home->U13.PumpSwitch]);
}

static void BF128_15(void) {
  o3pres = home->U19.o3pres; {
    V15 &= ~0x1;
    V5 &= ~0x2;
  }
  EF16_15();
  display_(0,25,53, 
   o3float,o3pres,_CVT_15(o3pres));
  display_(0,27,56, 
   o3float2,home->U17.o3lmpv,_CVT_13(home->U17.o3lmpv));
  display_(0,27,68, 
   o3float2,home->U19.o3lmpsd,_CVT_13(home->U19.o3lmpsd));
}

static void BF128_31(void) {
  EF16_15();
  if (!(V5)) {
    {
    	o3best = (home->U15.o3 * o3pres)/(o3pres*.9996 + 7.9);
    }
  }
  if (!(V15)) {
    if ( o3pres > 0 ) {if (!(V16)) {
      {
        	rtg_report( ozoneConc_rtg[ ozoneConc_rtginc ], O3count, home->U15.o3 );
      }
    }if (!(V17)) {
      {
        	rtg_report( ozonePres_rtg[ ozonePres_rtginc ], O3count, o3pres );
      }
    }if (!(V18)) {
      {
        	rtg_report( ozoneTemp_rtg[ ozoneTemp_rtginc ], O3count, home->U11.o3temp );
      }
    }
    }
  }
  display_(0,23,50,
  
  
   o3float,home->U15.o3,_CVT_15(home->U15.o3));
  display_(0,25,67, 
   o3float,home->U11.o3temp,_CVT_15(home->U11.o3temp));
}

static void (*efuncs[128])() = {
  BF128_0,
  BF8_1,
  BF16_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  BF8_0,
  BF8_1,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  BF128_15,
  BF16_0,
  BF8_1,
  BF16_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  BF8_0,
  BF8_1,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  BF128_31,
  BF16_0,
  BF8_1,
  BF16_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  BF8_0,
  BF8_1,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  EF16_15,
  BF16_0,
  BF8_1,
  BF16_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  BF8_0,
  BF8_1,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  EF16_15,
  BF16_0,
  BF8_1,
  BF16_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  BF8_0,
  BF8_1,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  EF16_15,
  BF16_0,
  BF8_1,
  BF16_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  BF8_0,
  BF8_1,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  EF16_15,
  BF16_0,
  BF8_1,
  BF16_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  BF8_0,
  BF8_1,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  EF16_15,
  BF16_0,
  BF8_1,
  BF16_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  BF8_0,
  BF8_1,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  EF16_15
};

static void IVF8_1(void) {
  V8 |= 0x1;
}
static void IVF16_2(void) { {
    V12 |= 0x2;
    V0 |= 0x1;
  }
}
static void IVF16_3(void) { {
    V19 |= 0x1;
    V6 |= 0x1;
  }
}
static void IVF16_6(void) { {
    V18 |= 0x2;
    V17 |= 0x2;
    V16 |= 0x2;
    V5 |= 0x1;
  }
}
static void IVF128_15(void) { {
    V15 |= 0x1;
    V5 |= 0x2;
  }
}
#define IVFUNCS
static void (*ivfuncs[128])() = {
  nullfunc,
  IVF8_1,
  IVF16_2,
  IVF16_3,
  nullfunc,
  nullfunc,
  IVF16_6,
  nullfunc,
  nullfunc,
  IVF8_1,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  IVF128_15,
  nullfunc,
  IVF8_1,
  IVF16_2,
  IVF16_3,
  nullfunc,
  nullfunc,
  IVF16_6,
  nullfunc,
  nullfunc,
  IVF8_1,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  IVF8_1,
  IVF16_2,
  IVF16_3,
  nullfunc,
  nullfunc,
  IVF16_6,
  nullfunc,
  nullfunc,
  IVF8_1,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  IVF8_1,
  IVF16_2,
  IVF16_3,
  nullfunc,
  nullfunc,
  IVF16_6,
  nullfunc,
  nullfunc,
  IVF8_1,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  IVF8_1,
  IVF16_2,
  IVF16_3,
  nullfunc,
  nullfunc,
  IVF16_6,
  nullfunc,
  nullfunc,
  IVF8_1,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  IVF8_1,
  IVF16_2,
  IVF16_3,
  nullfunc,
  nullfunc,
  IVF16_6,
  nullfunc,
  nullfunc,
  IVF8_1,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  IVF8_1,
  IVF16_2,
  IVF16_3,
  nullfunc,
  nullfunc,
  IVF16_6,
  nullfunc,
  nullfunc,
  IVF8_1,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  nullfunc,
  IVF8_1,
  IVF16_2,
  IVF16_3,
  nullfunc,
  nullfunc,
  IVF16_6,
  nullfunc,
  nullfunc,
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
#define NBROW 34
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
  34, /* NBMINF */
  34, /* NBROW */
  128, /* NROWSMAJF */
  1, /* NSECSPER */
  16, /* NROWSPER */
  0, 1, /* MFC lsb col, msb col */
  0xABB4, /* Synch Value */
  0 /* not inverted */
};
