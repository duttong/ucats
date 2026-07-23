/* colmain.skel Skeleton for collection main program
 * $Log: colmain.skel,v $
 * Revision 1.20  1995/10/18  02:05:30  nort
 * Changes to nlcon_display()
 *
 * Revision 1.19  1995/10/06  16:40:02  nort
 * Changes to nlcon_disp()
 * Old change to ROWS() and FRACSECS() macros
 *
 * Revision 1.18  1994/08/29  20:29:15  nort
 * Added check for obsolete MSG_LABEL
 *
 * Revision 1.17  1994/08/29  20:15:12  nort
 * Mods for OUI: Moved several initializations into oui_init_options()
 * Made OPT_COL_INIT Col_init_options() and CONSOLE_INIT obsolete
 * Changed calls to msg() to nl_error(), making TMC collection independent
 * of the msg module, since nl_error is made to be redefined.
 *
 * Revision 1.16  1994/02/15  05:56:10  nort
 * Added some verbosity to COL_get_pointer()
 * I don't know why seteuid(getuid()) has been commented out:
 * I should try it again later.
 *
 * Revision 1.15  1993/09/27  18:53:20  nort
 * Added seteuid(getuid())
 * Cleaned up RCS log
 * Added cmrcsid[]
 * Added include <string.h> for memcpy prototype
 *
 * Revision 1.14  1993/03/08  18:11:45  nort
 * Added timerbd timing when available
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/kernel.h>
#include <sys/timers.h>
#include <sys/proxy.h>
#include <time.h>
#include <unistd.h>
#include "nortlib.h"
#include "oui.h"
#include "dbr.h"
#include "msg.h"
#include "globmsg.h"
#include "cc.h"
#include "collect.h"
#include "timerbd.h"
#pragma off (unreferenced)
  static char cmrcsid[] =
	"$Id: colmain.skel,v 1.20 1995/10/18 02:05:30 nort Exp nort $";
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



 typedef float vaifloat;
  #define N_INJS_PER_FILE 1




UINT CurrInj_, CurrFile_, N_Inj_in_File_, Injected_;
  #include <ctype.h>
  static UINT read_gcnum( FILE *fp ) {
    int c;
	UINT v = 0;
	
    c = getc(fp);
	while ( isspace(c) ) c = getc(fp);
	while ( isdigit(c) ) {
	  v = v*10 + c - '0';
	  c = getc(fp);
	}
	return v;
  }

  void read_gcfile( UINT *injno, UINT *fileno ) {
	FILE *fp;
	
	fp = fopen( "GCFILE.CFG", "r" );
	if ( fp != 0 ) {
	  *injno = read_gcnum( fp );
	  *fileno = read_gcnum( fp );
	  fclose( fp );
	}
  }

  void write_gcfile( UINT injno, UINT fileno ) {
	FILE *fp;
	
	fp = fopen( "GCFILE.CFG", "w" );
	fprintf( fp, "%u\n%u\n\n\n", injno, fileno );
	fclose( fp );
  }



  static char nullregion[1];
  static unsigned char far *GCstatePtr = &nullregion;

#ifdef OPT_COL_INIT
  #error OPT_COL_INIT is obsolete
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

#ifdef CONSOLE_INIT
  #error CONSOLE_INIT is obsolete
#endif


unsigned char V0 = 0x1;
unsigned char V1 = 0x1;
unsigned char V2 = 0x1;
unsigned char V3 = 0x1;
unsigned char V4 = 0x1;
unsigned char V5 = 0x1;
UINT CurrInj;
UINT CurrFile;
UCHAR GCstate;
UCHAR RunState;
ULONG CUMSEC;
ULONG CHROMtime;
UINT MFCtr, Synch;
GC_Ctr GC_Ctr_CH1;
GC_Ctr GC_Ctr_CH2;
GC_Ctr GC_Ctr_CH3;
SCCMpnu flow_M1;
SCCMspPN flow_M1_sp;
SCCMpnu flow_BF1;
SCCMspPN flow_BF1_sp;
PSIBpnu pres_BP1;
PSIBspPN pres_BP1_sp;
MBARpnu pres_ECD1;
CELS temp_gasB_N;
CELS temp_SL1;
CELS temp_amb;
SCCMsl flow_SL;
SCCMpnu flow_M2;
SCCMspPN flow_M2_sp;
SCCMpnu flow_BF2;
SCCMspPN flow_BF2_sp;
PSIBpnu pres_BP2;
PSIBspPN pres_BP2_sp;
MBARpnu pres_ECD2;
CELS temp_pump;
CELS temp_SL2;
CELS temp_gasB_C;
MBAR pres_PUMP;
SCCMpnu flow_M3;
SCCMspPN flow_M3_sp;
SCCMpnu flow_BF3;
SCCMspPN flow_BF3_sp;
PSIBpnu pres_BP3;
MBARpnu pres_ECD3;
CELS temp_SL3;
MBAR pres_extern;
MBARpnuSL pres_SL;
VOLTS512 volt_1234;
PSIL presL_dope;
PSIL presL_cal;
PSIL presL_N2;
PSIH presH_123;
VOLTS512 volt_5;
VOLTSPM volt_15;
VOLTS28 volt_28;
OmegaT CH3_ECD;
OmegaT CH3_Col;
OmegaT CH3_Post;
OmegaT CH1_ECD;
OmegaT CH1_Col;
OmegaT CH2_Col;
OmegaT CH2_ECD;
OmegaTsp CH3_ECD_Sp;
OmegaTsp CH3_Col_Sp;
OmegaTsp CH3_Post_Sp;
OmegaTsp CH1_ECD_Sp;
OmegaTsp CH1_Col_Sp;
OmegaTsp CH2_Col_Sp;
OmegaTsp CH2_ECD_Sp;
Bit_HI_LO InitShutdown;
Bit_HI_LO ManSwitch;
Bit_HI_LO FailDummy;
Bit_On_Off PumpSwitch;
Bit_Cl_Op N2_IN;
Bit_Air_Cal ssv;
Bit_Cl_Op SLoopIN;
Bit_Op_Cl SLoopOUT;
Bit_On_Off O3Pump;
Bit_On_Off H2OPump;
Bit_Cl_Op H2OValve;
valvetext valv_CH1;
valvetext valv_CH2;
valvetext_inv valv_CH3;
valvT valv_calSSV;
ULONG O3count;
o3float o3;
o3float o3temp;
o3float o3pres;
o3float2 o3lmpv;
o3float2 o3lmpsd;
o3int o3yy;
o3int o3mm;
o3int o3dd;
o3int o3hh;
o3int o3min;
o3int o3ss;
o3float o3x;
o3float o3xtemp;
o3float o3xpres;
o3int4 o3xflowa;
o3int4 o3xflowb;
o3int4 o3xyy;
o3int o3xmm;
o3int o3xdd;
o3int o3xhh;
o3int o3xmin;
o3int o3xss;
o3float o3best;
o3float o3xbest;
ULONG maycX;
tdlint8   tdlrec;
tdlfloa9  tdl_time;
tdlfloa7  tdl_shortH2O;
tdlfloa7  tdl_H2OB;
tdlfloat  tdl_longH2O;
tdlfloat  tdl_H2OCD;
tdlfloa7 tdl_p;
tdlfloas tdl_t;
tdlfloas tdl_elecT;
tdlint6  tdl_amp;
tdlint6  tdl_pow;
tdlint6  tdl_pos;
tdlint6  tdl_zer;
tdlint6  tdl_posB;
tdlfloat tdl_best;
tdlfloat tdl_shortcorr;
tdlfloat tdl_longcorr;
tdlfloat tdl_CDcorr;
ULONG vaisX;
vaifloat vaiRH;
vaifloat vaiT;
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
      V5 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* VaisalaTog */
      V5 &= ~0x1;
      break;
  }
}
static void VSET_4_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 2: /* MaycommTog */
      V4 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* MaycommTog */
      V4 &= ~0x1;
      break;
  }
}
static void VSET_3_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 2: /* OzoneTog */
      V3 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* OzoneTog */
      V3 &= ~0x1;
      break;
  }
}
static void VSET_2_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 2: /* GCTog */
      V1 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* GCTog */
      V1 &= ~0x1;
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
      V0 |= 0x1;
      break;
    case 2: /* Injecting1 */
      V2 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 3: /* Injection */
      V0 &= ~0x1;
      break;
    case 2: /* Injecting1 */
      V2 &= ~0x1;
      break;
  }
}
static void tminitfunc(void) {VSET_0_(1);VSET_1_(1);VSET_2_(1);VSET_3_(1);VSET_4_(1);VSET_5_(1);
}
#define TMINITFUNC tminitfunc()

static void nullfunc(void);
static void CF1_0(void) {
  GC_Ctr_CH3 = GC_Ctr_Pull(0x2);
  GC_Ctr_CH2 = GC_Ctr_Pull(0x1);
  GC_Ctr_CH1 = GC_Ctr_Pull(0x0);
  home->U0.GC_Ctr_CH3 = GC_Ctr_CH3;
  home->U0.GC_Ctr_CH2 = GC_Ctr_CH2;
  home->U0.GC_Ctr_CH1 = GC_Ctr_CH1;
  home->U0.MFCtr = MFCtr;
  home->U0.Synch = Synch;
}

static void EF1_0(void) {
  {
  	if (GC_Ctr_CH3 >= 0) {
  		ecd_sum3 += GC_Ctr_CH3;
  		DetAvgCt3++;
  		ecdCH3x += 0.1;
  	} 
  	if (GC_Ctr_CH2 >= 0) {
  		ecd_sum1 += GC_Ctr_CH2;
  		DetAvgCt1++;
  		ecdCH2x += 0.1;
  	} 
  	if (GC_Ctr_CH1 >= 0) {
  		ecd_sum2 += GC_Ctr_CH1;
  		DetAvgCt2++;
  		ecdCH1x += 0.1;
  	}
  }
}

static void BF8_0(void) {
  CF1_0();
  {
      tdlrec = tdl.rec;
      if (tdlrec >= 0) {
          tdl_time = tdl.time;
          tdl_shortH2O = tdl.H2O_sh;
          tdl_H2OB = tdl.H2O_B;
          tdl_longH2O = tdl.H2O_lg;
          tdl_H2OCD = tdl.H2O_CD;
          tdl_p = tdl.p;
          tdl_t = tdl.t;
          tdl_elecT = tdl.t_elec;
          tdl_amp = tdl.amp;
          tdl_pow = tdl.pow;
          tdl_pos = tdl.pos;
          tdl_zer = tdl.zer;
          tdl_posB = tdl.posB;        
      }
      else {
          tdlrec = -999;
      }
  }
  home->U39.tdl_H2OCD = tdl_H2OCD;
  home->U19.tdl_p = tdl_p;
  home->U19.tdl_t = tdl_t;
  home->U19.tdl_elecT = tdl_elecT;
  home->U19.tdl_amp = tdl_amp;
  home->U21.tdl_pow = tdl_pow;
  home->U21.tdl_pos = tdl_pos;
  home->U21.tdl_zer = tdl_zer;
  home->U21.tdl_posB = tdl_posB;
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
  {if (!(V1)) {
    { VSET_2_(1);
    	}
  }if (!(V2)) {
    V2 |= 0x1;
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

static void CF8_1(void) {
  CF1_0();
  home->U23.tdlrec = tdlrec;
  home->U21.tdl_time = tdl_time;
  home->U17.tdl_shortH2O = tdl_shortH2O;
  home->U19.tdl_H2OB = tdl_H2OB;
  home->U19.tdl_longH2O = tdl_longH2O;
  home->U23.maycX = maycX;
}

static void EF8_1(void) {
  EF1_0();
  maycX++;
  {if (!(V4)) {
    { VSET_4_(1);}
  }
  
      if (maycX >= 120) {
          maycX = 0; VSET_4_(2);
      }
  }
}

static void BF16_1(void) {
  CF8_1();
  CH1_Col = OmegaArray( 2 * 0x5 - 2 );
  home->U5.CH1_Col = CH1_Col;
  EF8_1();
}

static void CF8_2(void) {
  CF1_0();
  home->U23.tdl_shortcorr = tdl_shortcorr;
  home->U21.tdl_longcorr = tdl_longcorr;
  home->U23.tdl_CDcorr = tdl_CDcorr;
  home->U23.tdl_best = tdl_best;
}

static void EF8_2(void) {
  EF1_0();
  {
  	tdl_shortcorr = -824 + 1.160*tdl_shortH2O;
  	tdl_longcorr = -9.62 + .776*tdl_longH2O*(1 + .0003*tdl_p) + .00099*tdl_longH2O*tdl_longH2O/(1 + .00176*tdl_p);
  	tdl_CDcorr = ZeroOffset + (.778*tdl_H2OCD + .00132*tdl_H2OCD*tdl_H2OCD)/(1 + .000268*tdl_p);
      tdl_best = tdl_longcorr;
  
      if (tdl_longcorr < USECD) tdl_best = tdl_CDcorr;
      if (tdl_longcorr > USEShort) tdl_best = tdl_shortcorr;
  }
}

static void BF16_2(void) {
  CF8_2();
  {
  	vaiRH = 	vai.rh;
  	vaiT  = 	vai.t;
  }
  CH1_Col_Sp = OmegaArray( 2 * 0x5 - 1 );
  home->U25.vaiRH = vaiRH;
  home->U25.vaiT = vaiT;
  home->U21.CH1_Col_Sp = CH1_Col_Sp;
  EF8_2();
}

static void BF16_3(void) {
  CF1_0();
  {
      o3x =		ozonex.o3;
      o3xtemp =	ozonex.t;
      o3xpres =	ozonex.p;
      o3xflowa =	ozonex.flowa;
      o3xflowb =	ozonex.flowb;
      o3xyy =		ozonex.date.year;
      o3xmm =		ozonex.date.mon;
      o3xdd =		ozonex.date.day;
      o3xhh =		ozonex.time.hh;
      o3xmin =	ozonex.time.min;
      o3xss =		ozonex.time.sec;
  }
  {
  
  	valv_CH1 = valvePos[CH1gsvADD] - 1;
  	valv_CH2 = valvePos[CH2gsvADD] - 1;
  	valv_CH3 = valvePos[CH3gsvADD] - 1;
  	valv_calSSV = valvePos[CALSSVADD];
  
  	if (valco_proxy != 0) 
  		Trigger ( valco_proxy );    
  
  }
  CH1_ECD = OmegaArray( 2 * 0x7 - 2 );
  home->U15.valv_CH1 = valv_CH1;
  home->U17.valv_CH2 = valv_CH2;
  home->U17.valv_CH3 = valv_CH3;
  home->U17.valv_calSSV = valv_calSSV;
  home->U15.o3x = o3x;
  home->U13.o3xtemp = o3xtemp;
  home->U15.o3xpres = o3xpres;
  home->U15.o3xflowa = o3xflowa;
  home->U15.o3xflowb = o3xflowb;
  home->U3.CH1_ECD = CH1_ECD;
  EF1_0();
}

static void BF16_4(void) {
  CF1_0();
  CH1_ECD_Sp = OmegaArray( 2 * 0x7 - 1 );
  flow_BF2_sp = ADRdtoa(0x15);
  flow_BF2 = ADRanalog(0x15);
  flow_BF1_sp = ADRdtoa(0xB);
  flow_BF1 = ADRanalog(0xB);
  home->U15.CH1_ECD_Sp = CH1_ECD_Sp;
  home->U7.flow_BF2_sp = flow_BF2_sp;
  home->U1.flow_BF2 = flow_BF2;
  home->U1.flow_BF1_sp = flow_BF1_sp;
  home->U3.flow_BF1 = flow_BF1;
  home->U0.CUMSEC = CUMSEC;
  home->U0.CHROMtime = CHROMtime;
  EF1_0();
  CUMSEC++;
}

static void BF16_5(void) {
  CF1_0();
  CH2_Col = OmegaArray( 2 * 0x6 - 2 );
  flow_BF3_sp = ADRdtoa(0x1F);
  flow_BF3 = ADRanalog(0x1F);
  flow_M2_sp = ADRdtoa(0x14);
  flow_M2 = ADRanalog(0x14);
  flow_M1_sp = ADRdtoa(0xA);
  flow_M1 = ADRanalog(0xA);
  home->U7.CH2_Col = CH2_Col;
  home->U5.flow_M2_sp = flow_M2_sp;
  home->U0.flow_M2 = flow_M2;
  home->U0.flow_M1_sp = flow_M1_sp;
  home->U1.flow_M1 = flow_M1;
  home->U9.flow_BF3_sp = flow_BF3_sp;
  home->U7.flow_BF3 = flow_BF3;
  EF1_0();
}

static void BF16_6(void) {
  CF1_0();
  CH2_Col_Sp = OmegaArray( 2 * 0x6 - 1 );
  flow_M3_sp = ADRdtoa(0x1E);
  flow_M3 = ADRanalog(0x1E);
  flow_SL = ADRanalog(0x11);
  home->U23.CH2_Col_Sp = CH2_Col_Sp;
  home->U21.o3xbest = o3xbest;
  home->U21.O3count = O3count;
  home->U17.o3best = o3best;
  home->U5.flow_SL = flow_SL;
  home->U7.flow_M3_sp = flow_M3_sp;
  home->U5.flow_M3 = flow_M3;
  EF1_0();
  O3count++;
  {if (!(V3)) {
    { VSET_3_(1); }
  }
  
  	if ( O3count >= 60*60/10 ) { 
  		O3count = 0; VSET_3_(2);
  	}
  }
  {
  	o3xbest = 0.970*((o3x-3.0) * o3xpres)/(o3xpres*1.1471 - 244.54) ;
  }
}

static void BF16_7(void) {
  CF1_0();
  CH2_ECD = OmegaArray( 2 * 0x4 - 2 );
  pres_BP3 = ADRanalog(0x20);
  pres_BP2_sp = ADRdtoa(0x1);
  pres_BP2 = ADRanalog(0x16);
  pres_ECD1 = ADRanalog(0xD);
  pres_BP1_sp = ADRdtoa(0x0);
  pres_BP1 = ADRanalog(0xC);
  home->U9.CH2_ECD = CH2_ECD;
  home->U1.pres_ECD1 = pres_ECD1;
  home->U7.pres_BP3 = pres_BP3;
  home->U5.pres_BP2_sp = pres_BP2_sp;
  home->U7.pres_BP2 = pres_BP2;
  home->U1.pres_BP1_sp = pres_BP1_sp;
  home->U1.pres_BP1 = pres_BP1;
  EF1_0();
}

static void BF16_9(void) {
  CF8_1();
  CH2_ECD_Sp = OmegaArray( 2 * 0x4 - 1 );
  home->U25.CH2_ECD_Sp = CH2_ECD_Sp;
  EF8_1();
}

static void BF16_10(void) {
  CF8_2();
  CH3_Col = OmegaArray( 2 * 0x2 - 2 );
  pres_ECD3 = ADRanalog(0x21);
  pres_ECD2 = ADRanalog(0x17);
  home->U1.CH3_Col = CH3_Col;
  home->U9.pres_ECD3 = pres_ECD3;
  home->U3.pres_ECD2 = pres_ECD2;
  EF8_2();
}

static void BF16_11(void) {
  CF1_0();
  CH3_Col_Sp = OmegaArray( 2 * 0x2 - 1 );
  presH_123 = ADRanalog(0x4);
  presL_cal = ADRanalog(0x1);
  presL_dope = ADRanalog(0x3);
  pres_SL = ADRanalog(0x0);
  pres_extern = ADRanalog(0x25);
  pres_PUMP = ADRanalog(0x1B);
  home->U13.CH3_Col_Sp = CH3_Col_Sp;
  home->U11.presL_dope = presL_dope;
  home->U9.presL_cal = presL_cal;
  home->U9.presH_123 = presH_123;
  home->U11.pres_SL = pres_SL;
  home->U5.pres_PUMP = pres_PUMP;
  home->U9.pres_extern = pres_extern;
  EF1_0();
}

static void BF16_12(void) {
  CF1_0();
  CH3_ECD = OmegaArray( 2 * 0x1 - 2 );
  presL_N2 = ADRanalog(0x2);
  temp_gasB_C = ADRanalog(0x1A);
  temp_pump = ADRanalog(0x18);
  temp_amb = ADRanalog(0x10);
  temp_SL1 = ADRanalog(0xF);
  temp_gasB_N = ADRanalog(0xE);
  home->U0.CH3_ECD = CH3_ECD;
  home->U3.temp_SL1 = temp_SL1;
  home->U5.temp_pump = temp_pump;
  home->U3.temp_gasB_N = temp_gasB_N;
  home->U9.temp_gasB_C = temp_gasB_C;
  home->U3.temp_amb = temp_amb;
  home->U11.presL_N2 = presL_N2;
  EF1_0();
}

static void BF16_13(void) {
  CF1_0();
  CH3_ECD_Sp = OmegaArray( 2 * 0x1 - 1 );
  volt_28 = ADRanalog(0x7);
  volt_15 = ADRanalog(0x6);
  volt_1234 = ADRanalog(0x0);
  temp_SL3 = ADRanalog(0x23);
  temp_SL2 = ADRanalog(0x19);
  home->U11.CH3_ECD_Sp = CH3_ECD_Sp;
  home->U13.volt_28 = volt_28;
  home->U11.volt_15 = volt_15;
  home->U7.volt_1234 = volt_1234;
  home->U23.vaisX = vaisX;
  home->U11.temp_SL3 = temp_SL3;
  home->U3.temp_SL2 = temp_SL2;
  EF1_0();
  vaisX++;
  {if (!(V5)) {
    { VSET_5_(1); }
  }
  
  	if ( vaisX >= 120 ) { 
  		vaisX = 0; VSET_5_(2);
  	}
  }
}

static void BF16_14(void) {
  CF1_0();
  H2OValve = ADRdig(0x23);
  H2OPump = ADRdig(0x24);
  O3Pump = ADRdig(0x25);
  N2_IN = ADRdig(0x5);
  FailDummy = ADRdig(0x3);
  ManSwitch = ADRdig(0x1);
  InitShutdown = ADRdig(0x0);
  CH3_Post_Sp = OmegaArray( 2 * 0x3 - 1 );
  CH3_Post = OmegaArray( 2 * 0x3 - 2 );
  volt_5 = ADRanalog(0x5);
  CurrFile = CurrFile_;
  CurrInj = CurrInj_;
  home->U33.O3Pump = O3Pump;
  home->U0.N2_IN = N2_IN;
  home->U15.ManSwitch = ManSwitch;
  home->U13.InitShutdown = InitShutdown;
  home->U15.H2OValve = H2OValve;
  home->U13.H2OPump = H2OPump;
  home->U11.FailDummy = FailDummy;
  home->U0.CurrInj = CurrInj;
  home->U0.CurrFile = CurrFile;
  home->U13.CH3_Post_Sp = CH3_Post_Sp;
  home->U13.CH3_Post = CH3_Post;
  home->U13.volt_5 = volt_5;
  EF1_0();
  { ITXFileNum = CurrInj * 1000 + CurrFile;
  }
}

static void CF16_15(void) {
  CF1_0();
  SLoopOUT = ADRdig(0x11);
  SLoopIN = ADRdig(0x10);
  ssv = ADRdig(0xE);
  PumpSwitch = ADRdig(0xC);
  GCstate = *GCstatePtr;
  home->U0.RunState = RunState;
  home->U0.GCstate = GCstate;
  home->U15.ssv = ssv;
  home->U13.SLoopOUT = SLoopOUT;
  home->U11.SLoopIN = SLoopIN;
  home->U13.PumpSwitch = PumpSwitch;
  home->U15.o3xyy = o3xyy;
  home->U15.o3xss = o3xss;
  home->U17.o3xmm = o3xmm;
  home->U17.o3xmin = o3xmin;
  home->U17.o3xhh = o3xhh;
  home->U17.o3xdd = o3xdd;
}

static void EF16_15(void) {
  EF1_0();
  {
    	if ( GCstate == 0 ) VSET_0_(1);
  	else if ( GCstate == 1 ) VSET_0_(2);
  	else if ( GCstate == 2 ) VSET_0_(3);
  	else if ( GCstate == 3 ) VSET_0_(4);
  }
  {
  	if ( RunState == 0 ) VSET_1_(1);
  	else if ( RunState == 1 ) VSET_1_(2);
  }
  {if (!(V0)) {
    { CHROMtime++; InjectingInc = 0; }
  }
    if ((GCstate == 1) || (GCstate == 3)) { 
  	if (InjectingInc == 0 ) {
  		CHROMtime = 1; 
  		InjectingInc = 1;
  	}
  	else CHROMtime += 1;
    }
  }
  if ((GCstate == 1) || (GCstate == 3)) {
    if ( CurrFile_ == 0 )
  	read_gcfile( &CurrInj_, &CurrFile_ );
    CurrInj_++;
    if ( N_Inj_in_File_ == N_INJS_PER_FILE-1 ) {
      N_Inj_in_File_ = 0;
  	CurrFile_++;
    } else N_Inj_in_File_++;
    write_gcfile( CurrInj_, CurrFile_ );
  }
}

static void BF128_15(void) {
  CF16_15();
  {
      o3 =		ozone.o3;
      o3temp =	ozone.t;
      o3pres =	ozone.p;
      o3lmpv =	ozone.lamp_v;
      o3lmpsd =	ozone.lamp_sd;
      o3yy =		ozone.date.year;
      o3mm =		ozone.date.mon;
      o3dd =		ozone.date.day;
      o3hh =		ozone.time.hh;
      o3min =		ozone.time.min;
      o3ss =		ozone.time.sec;
  }
  home->U31.o3lmpsd = o3lmpsd;
  EF16_15();
}

static void BF128_31(void) {
  CF16_15();
  home->U29.o3lmpv = o3lmpv;
  EF16_15();
}

static void BF128_47(void) {
  CF16_15();
  home->U27.o3pres = o3pres;
  EF16_15();
}

static void BF128_63(void) {
  CF16_15();
  home->U19.o3temp = o3temp;
  EF16_15();
}

static void BF128_79(void) {
  CF16_15();
  home->U17.o3 = o3;
  EF16_15();
  {
  	o3best = (o3 * o3pres)/(o3pres*.9996 + 7.9);
  }
}

static void BF128_95(void) {
  CF16_15();
  home->U41.o3hh = o3hh;
  home->U33.o3dd = o3dd;
  EF16_15();
}

static void BF128_111(void) {
  CF16_15();
  home->U37.o3mm = o3mm;
  home->U35.o3min = o3min;
  EF16_15();
}

static void BF128_127(void) {
  CF16_15();
  home->U35.o3yy = o3yy;
  home->U37.o3ss = o3ss;
  EF16_15();
}

static void (*efuncs[128])() = {
  BF128_0,
  BF16_1,
  BF16_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  BF8_0,
  BF16_9,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  BF128_15,
  BF16_0,
  BF16_1,
  BF16_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  BF8_0,
  BF16_9,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  BF128_31,
  BF16_0,
  BF16_1,
  BF16_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  BF8_0,
  BF16_9,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  BF128_47,
  BF16_0,
  BF16_1,
  BF16_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  BF8_0,
  BF16_9,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  BF128_63,
  BF16_0,
  BF16_1,
  BF16_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  BF8_0,
  BF16_9,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  BF128_79,
  BF16_0,
  BF16_1,
  BF16_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  BF8_0,
  BF16_9,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  BF128_95,
  BF16_0,
  BF16_1,
  BF16_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  BF8_0,
  BF16_9,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  BF128_111,
  BF16_0,
  BF16_1,
  BF16_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  BF8_0,
  BF16_9,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  BF128_127
};

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

/* Some temporary defs until everything is in the right place */
#ifndef TS_MFC_LIMIT
  #define TS_MFC_LIMIT 32767
#endif

/* This is for real: */
#ifndef DG_OTHER_CASES
  #define DG_OTHER_CASES
#endif

/* for debugging */
int check_ts = 1;

#if (NROWMAJF < 16)
  #define DP_NROWS 16
#else
  #define DP_NROWS NROWMAJF
#endif
#define NTS 3
#define incmod(x,y) if (x==((y)-1)) x = 0; else x++

static unsigned char dpdata[DP_NROWS][NBROW];
static tstamp_type tstamps[NTS], *tsps[DP_NROWS], *curts;
static unsigned short next_ts_index;
static unsigned short trans_row, col_row;
static short rowlets;
static short ts_checks;
#ifdef NEED_TIME_FUNCS
  static unsigned short CurMFC;
#endif
#define TSCHK_RTIME 1
#define TSCHK_IMPLICIT 2
#define TSCHK_CHECK 4
#define TSCHK_REQUIRED 8
static unsigned short next_minor_frame, majf_row;
#if (NROWMINF != 1)
  static unsigned short minf_row;
#endif
#ifndef DG_CUSTOM_INIT
  #define DG_CUSTOM_INIT
#endif
#ifndef TMINITFUNC
  #define TMINITFUNC
#endif
#ifndef ONINT_INIT
  #define ONINT_INIT
#endif
#ifndef ONINT_TERM
  #define ONINT_TERM
#endif
#ifndef DG_CUSTOM_TERM
  #define DG_CUSTOM_TERM
#endif


void main(int argc, char **argv) {
  oui_init_options(argc, argv);
  { int nlrsp;
	
	nlrsp = set_response(NLRSP_QUIET);
	if (find_CC(0) != -1)
	  cc_init_options(argc, argv, DCT_TM, DCT_TM, 0, 0, FORWARD_QUIT);
	set_response(nlrsp);
  }
  DG_CUSTOM_INIT;
  TMINITFUNC;
  BEGIN_MSG;
  DG_operate();
  DG_CUSTOM_TERM;
  nl_error(MSG_EXIT_NORM, "Terminated");
}


static void ts_check(void) {
  rowlets -= TRN;
  if (rowlets < LOWLIM || rowlets > HIGHLIM)
	ts_checks = TSCHK_RTIME | TSCHK_CHECK;
}

static void Collect_row(void) {
  time_t rtime, dt;
  unsigned int dmfc;
  tstamp_type *newts;
  
  #ifdef _SUBBUS_H
	tick_sic();
  #endif
  #if (NROWMINF != 1)
	if (minf_row == 0) {
  #endif
	  if ((ts_checks & TSCHK_REQUIRED) == 0 && (
	  #ifdef ROLLOVER
		  next_minor_frame == ROLLOVER ||
	  #endif
		  next_minor_frame - curts->mfc_num > TS_MFC_LIMIT))
		ts_checks |= TSCHK_IMPLICIT | TSCHK_REQUIRED;
	  if (ts_checks) {
		newts = &tstamps[next_ts_index];
		if (newts == curts)
		  nl_error(MSG_EXIT_ABNORM, "TimeStamp overflow");
		if (ts_checks & TSCHK_RTIME)
		  rtime = time(NULL);
		if (ts_checks & (TSCHK_IMPLICIT|TSCHK_CHECK)) {
		  /* mfc rate is MFSECNUM/MFSECDEN mfcs/second, so
		     mfcs/MFSECNUM = secs/MFSECDEN = dmfc
		  */
		  #if (MFSECDEN == 1)
			#define MFSECDENMUL
		  #else
			#define MFSECDENMUL * MFSECDEN
		  #endif
		  dmfc = next_minor_frame - curts->mfc_num;
		  #if (MFSECNUM != 1)
			dmfc /= MFSECNUM;
		  #endif
		  newts->secs = curts->secs + dmfc MFSECDENMUL;
		  #if (MFSECNUM != 1)
			newts->mfc_num = curts->mfc_num + dmfc*MFSECNUM;
		  #else
			newts->mfc_num = next_minor_frame;
		  #endif
		  if (ts_checks & TSCHK_CHECK) {
			/* compare rtime to newts->secs */
			#if (MFSECNUM != 1)
			  dmfc = next_minor_frame - newts->mfc_num;
			  dt = dmfc MFSECDENMUL / MFSECNUM;
			  dt = rtime - dt - newts->secs;
			#else
			  dt = rtime - newts->secs;
			#endif
			if (dt > SECDRIFT || dt < -SECDRIFT)
			  ts_checks |= TSCHK_REQUIRED;
		  }
		}
		if (ts_checks & TSCHK_REQUIRED) {
		  if (ts_checks & TSCHK_RTIME) {
			/* New time stamp:
			  If higher resolution time is available {
				f = fraction of a second extra
				rmfc = rate of mfc Hz
				f*rmfc = number of minor frames since even second.
				record floor(seconds) and mfc - f*rmfc
			  }
			*/
			newts->secs = rtime;
			newts->mfc_num = next_minor_frame;
		  }
		  #ifdef ROLLOVER
			if (next_minor_frame == ROLLOVER) {
			  next_minor_frame = 0;
			  newts->mfc_num -= ROLLOVER;
			}
		  #endif
		  incmod(next_ts_index, NTS);
		  tsps[col_row] = curts = newts;
		} else tsps[col_row] = NULL;
		ts_checks = 0;
	  } else tsps[col_row] = NULL;
	  MFCtr = next_minor_frame;
	  #ifdef NEED_TIME_FUNCS
		CurMFC = MFCtr;
	  #endif
	  next_minor_frame++;
  #if (NROWMINF != 1)
	  minf_row = 1;
    } else
	  #if (NROWMINF > 2)
		if (minf_row == NROWMINF-1)
	  #endif
  #endif
	{ /* Synch Calculations */
      #ifdef INVSYNCH
		if (majf_row == NROWMAJF-1)
		  Synch = ~SYNCHVAL;
		else
	  #else
		  Synch = SYNCHVAL;
	  #endif
  #if (NROWMINF != 1)
	  minf_row = 0;
  #endif
	}
  #if (NROWMINF > 2)
	  else ++minf_row;
  #endif
  
  /* appropriate collection function */
  home = (void *) dpdata[col_row];
  efuncs[majf_row]();
  incmod(majf_row, NROWMAJF);
  rowlets += TRD;
  
  incmod(col_row, DP_NROWS);
  if (col_row == trans_row)
	nl_error(MSG_EXIT_ABNORM, "Collection overflow");
}

/* time_prox holds information pertinent to the two timing proxies.
   If proxy == 0, the proxy has not been initialized.
   If proxy != 0, timer_type indicates what type of timer is used.
   TPTYPE_SYS means u.timer is a system timer.
   TPTYPE_TBD means u.tmrno is a timer board timer.
   TPTYPE_EXT means an external timing source is used.
*/
struct time_prox {
  pid_t proxy;
  int timer_type;
  union {
	timer_t timer;
	int tmrno;
  } u;
};
#define TPTYPE_SYS 0
#define TPTYPE_TBD 1
#define TPTYPE_EXT 2
static struct time_prox col_timer = {0,0}, ts_timer = {0,0};

#define NSEC (1000000000)

static void start_timing(int rn, int rd, struct time_prox *tp,
						 unsigned char msgtxt) {
  struct itimercb tcb;
  struct itimerspec tval, otval;

  assert(tp->proxy == 0);
  if (rn <= 4*rd) {
	set_response(0);
	tp->u.tmrno = Tmr_proxy(3, rn*(TMR_0_FREQ/rd), msgtxt);
	set_response(3);
	if (tp->u.tmrno == -1) nl_error(0, "Using System Timer");
	else {
	  tp->proxy = -1;
	  tp->timer_type = TPTYPE_TBD;
	  nl_error(0, "Using Timer Board Timer");
	  return;
	}
  }
  tp->proxy = nl_make_proxy(&msgtxt, 1);
  tcb.itcb_event.evt_value = tp->proxy;
  tp->u.timer = mktimer(TIMEOFDAY, _TNOTIFY_PROXY, &tcb);
  if (tp->u.timer == -1)
	nl_error(MSG_EXIT_ABNORM, "Error making timer: %d", tp->u.timer);
  tval.it_value.tv_sec = rn/rd;
  tval.it_value.tv_nsec = (rn%rd) * (NSEC/rd);
  tval.it_interval = tval.it_value;
  if (reltimer(tp->u.timer, &tval, &otval) == -1)
	nl_error(MSG_EXIT_ABNORM, "Error in reltimer: %d\n", errno);
  tp->timer_type = TPTYPE_SYS;
}

/* Only detaches proxy if timing is internal */
static void stop_timing(struct time_prox *tp) {
  if (tp->proxy != 0) {
	switch (tp->timer_type) {
	  case TPTYPE_TBD:
		Tmr_reset(tp->u.tmrno);
		tp->proxy = 0;
		break;
	  case TPTYPE_SYS:
		rmtimer(tp->u.timer);
		tp->u.timer = 0;
		if (tp->proxy != 0) {
		  qnx_proxy_detach(tp->proxy);
		  tp->proxy = 0;
		}
		break;
	  default:
		break;
	}
  }
}

#define MKDCTV(x,y) ((x<<8)|y)
#define DCTV(x,y) MKDCTV(DCT_##x,DCV_##y)

int DG_DASCmd(unsigned char type, unsigned char val) {
  switch (MKDCTV(type, val)) {
	case DCTV(TM,TM_START):
	  if (check_ts)
		start_timing(10, 1, &ts_timer, COL_TSPROXY);
	  if (col_timer.proxy == 0)
		start_timing(tmi(nsecsper), tmi(nrowsper), &col_timer, COL_REG_SIG);
	  ts_checks = TSCHK_RTIME | TSCHK_REQUIRED;
	  next_ts_index = 0;
	  curts = NULL;
	  trans_row = col_row = 0;
	  rowlets = 0;
	  next_minor_frame = majf_row = 0;
	  #if (NROWMINF != 1)
		minf_row = 0;
	  #endif
	  ONINT_INIT
	  break;
	case DCTV(TM,TM_END):
	case DCTV(QUIT,QUIT):
	  #ifdef _SUBBUS_H
		disarm_sic();
	  #endif
	  ONINT_TERM
	  stop_timing(&col_timer);
	  stop_timing(&ts_timer);
	  break;
	default:
	  break;
  }
  return(0);
}


#include <sys/seginfo.h>

/* I've added some verbosity here, but I'd like to add more:
   The messages should include the pointer ID, which we don't know here.
   I'd have to change tmc together with this file...
*/
static void COL_get_pointer(pid_t sent_tid, void far **pptr, void far *ptr) {
  unsigned segt;
  
  if (*pptr == &nullregion) {
	segt = qnx_segment_get(sent_tid, FP_SEG(ptr), 0);
	if (segt != -1) {
	  *pptr = MK_FP(segt, FP_OFF(ptr));
	  reply_byte(sent_tid, DAS_OK);
	  nl_error(0, "Pointer set from pid %d", sent_tid);
	  return;
	} else nl_error(MSG_WARN, "Pointer failed from pid %d", sent_tid);
  } else nl_error(MSG_WARN, "Pointer from pid %d previously set", sent_tid);
  reply_byte(sent_tid, DAS_UNKN);
}

static void COL_free_pointer(pid_t sent_tid, void far **pptr) {
  if (*pptr != &nullregion) {
	qnx_segment_free( FP_SEG(*pptr));
	*pptr = &nullregion;
	reply_byte(sent_tid, DAS_OK);
  } else reply_byte(sent_tid, DAS_UNKN);
}

static void COL_recv_proxy(pid_t sent_tid, pid_t *prx, pid_t proxy) {
  if (*prx == 0) {
	*prx = proxy;
	reply_byte(sent_tid, DAS_OK);
  } else reply_byte(sent_tid, DAS_UNKN);
}

static void COL_end_proxy(pid_t sent_tid, pid_t *prx, struct colmsg *c) {
  c->u.proxy = *prx;
  c->type = *prx == 0 ? DAS_UNKN : DAS_OK;
  *prx = 0;
  Reply(sent_tid, c, sizeof(struct colmsg));
}

#include <stddef.h>

static void read_col_send( void *dest, size_t length,
					struct colmsg *cmsg, pid_t sent_tid ) {
  size_t trulen = min( length, cmsg->u.data.size );
  if ( trulen <= MAX_COLMSG_SIZE-5 ) {
	memcpy( dest, cmsg->u.data.data, trulen );
  } else {
	Readmsg( sent_tid,
	  offsetof( struct colmsg, u.data.data ), dest, trulen );
  }
}

int DG_other(unsigned char *msg_ptr, int sent_tid) {
  struct colmsg *cmsg;
  
  switch (*msg_ptr) {
	case COL_REG_SIG:
	  if (dbr_info.tm_started) Collect_row();
	  break;
	case COL_TSPROXY:
	  if (dbr_info.tm_started) ts_check();
	  break;
	case COL_REGULATE:
	  {
		struct dgreg_rep dgregrep;
		unsigned char msgtxt = COL_REG_SIG;

		if (col_timer.proxy != 0) {
		  dgregrep.reply_code = DAS_BUSY;
		  dgregrep.proxy = col_timer.proxy;
		} else {
		  col_timer.proxy = nl_make_proxy(&msgtxt, 1);
		  col_timer.timer_type = TPTYPE_EXT;
		  dgregrep.proxy = col_timer.proxy;
		  dgregrep.reply_code = DAS_OK;
		}
		Reply(sent_tid, &dgregrep, sizeof(dgregrep));
	  }
	  return(0);
	case COL_SET_POINTER:
	  cmsg = (struct colmsg *)msg_ptr;
	  switch (cmsg->id) {
		case 4: COL_get_pointer(sent_tid, &GCstatePtr, cmsg->u.pointer); break;
		default: return(reply_byte(sent_tid, DAS_UNKN));
	  }
	  return(0);
	case COL_RESET_POINTER:
	  cmsg = (struct colmsg *)msg_ptr;
	  switch (cmsg->id) {
		case 4: COL_free_pointer(sent_tid, &GCstatePtr); break;
		default: return(reply_byte(sent_tid, DAS_UNKN));
	  }
	  return(0);
	case COL_SET_PROXY:
	  cmsg = (struct colmsg *)msg_ptr;
	  switch (cmsg->id) {
		case 13: COL_recv_proxy(sent_tid, &vaisala_proxy, cmsg->u.proxy); break;
		case 12: COL_recv_proxy(sent_tid, &maycomm_proxy, cmsg->u.proxy); break;
		case 11: COL_recv_proxy(sent_tid, &o3x_proxy, cmsg->u.proxy); break;
		case 10: COL_recv_proxy(sent_tid, &o3_proxy, cmsg->u.proxy); break;
		case 4: COL_recv_proxy(sent_tid, &valco_proxy, cmsg->u.proxy); break;
		case 3: COL_recv_proxy(sent_tid, &rs485_proxy, cmsg->u.proxy); break;
		case 8: COL_recv_proxy(sent_tid, &ECDresp_proxy, cmsg->u.proxy); break;
		case 9: COL_recv_proxy(sent_tid, &adr_proxy, cmsg->u.proxy); break;
		default: return(reply_byte(sent_tid,DAS_UNKN));
	  }
	  return(0);
	case COL_RESET_PROXY:
	  cmsg = (struct colmsg *)msg_ptr;
	  switch (cmsg->id) {
		case 13: COL_end_proxy(sent_tid, &vaisala_proxy, cmsg); break;
		case 12: COL_end_proxy(sent_tid, &maycomm_proxy, cmsg); break;
		case 11: COL_end_proxy(sent_tid, &o3x_proxy, cmsg); break;
		case 10: COL_end_proxy(sent_tid, &o3_proxy, cmsg); break;
		case 4: COL_end_proxy(sent_tid, &valco_proxy, cmsg); break;
		case 3: COL_end_proxy(sent_tid, &rs485_proxy, cmsg); break;
		case 8: COL_end_proxy(sent_tid, &ECDresp_proxy, cmsg); break;
		case 9: COL_end_proxy(sent_tid, &adr_proxy, cmsg); break;
		default: return(reply_byte(sent_tid,DAS_UNKN));
	  }
	  return(0);
	case COL_SEND:
	  cmsg = (struct colmsg *)msg_ptr;
	  switch (cmsg->id) {
		case COL_SEND_INIT:
		  if (stricmp(cmsg->u.name, "vai") == 0) {
			cmsg->u.data.id = 8;
			cmsg->u.data.size = sizeof(vai);
		  } else if (stricmp(cmsg->u.name, "tdl") == 0) {
			cmsg->u.data.id = 7;
			cmsg->u.data.size = sizeof(tdl);
		  } else if (stricmp(cmsg->u.name, "ozonex") == 0) {
			cmsg->u.data.id = 6;
			cmsg->u.data.size = sizeof(ozonex);
		  } else if (stricmp(cmsg->u.name, "ozone") == 0) {
			cmsg->u.data.id = 5;
			cmsg->u.data.size = sizeof(ozone);
		  } else if (stricmp(cmsg->u.name, "valvePos") == 0) {
			cmsg->u.data.id = 4;
			cmsg->u.data.size = sizeof(valvePos);
		  } else if (stricmp(cmsg->u.name, "Omega485") == 0) {
			cmsg->u.data.id = 3;
			cmsg->u.data.size = sizeof(Omega485);
		  } else if (stricmp(cmsg->u.name, "ECDresp") == 0) {
			cmsg->u.data.id = 2;
			cmsg->u.data.size = sizeof(ECDresp);
		  } else if (stricmp(cmsg->u.name, "adr2000") == 0) {
			cmsg->u.data.id = 1;
			cmsg->u.data.size = sizeof(adr2000);
		  } else return reply_byte(sent_tid,DAS_UNKN);
		  cmsg->type = DAS_OK;
		  Reply(sent_tid, cmsg, offsetof(struct colmsg, u.data.data));
		  return 0;
		case COL_SEND_SEND:
		  switch (cmsg->u.data.id) {
			case 8:
			  read_col_send(&vai, sizeof(vai), cmsg, sent_tid );
			  break;
			case 7:
			  read_col_send(&tdl, sizeof(tdl), cmsg, sent_tid );
			  break;
			case 6:
			  read_col_send(&ozonex, sizeof(ozonex), cmsg, sent_tid );
			  break;
			case 5:
			  read_col_send(&ozone, sizeof(ozone), cmsg, sent_tid );
			  break;
			case 4:
			  read_col_send(&valvePos, sizeof(valvePos), cmsg, sent_tid );
			  break;
			case 3:
			  read_col_send(&Omega485, sizeof(Omega485), cmsg, sent_tid );
			  break;
			case 2:
			  read_col_send(&ECDresp, sizeof(ECDresp), cmsg, sent_tid );
			  break;
			case 1:
			  read_col_send(&adr2000, sizeof(adr2000), cmsg, sent_tid );
			  break;
			default: return reply_byte(sent_tid, DAS_UNKN);
		  }
		  break;
		case COL_SEND_RESET: break;
		default: return reply_byte(sent_tid,DAS_UNKN);
	  }
	  return reply_byte(sent_tid, DAS_OK);
	DG_OTHER_CASES /* defined via preprocessor elsewhere */
	default:
	  return(reply_byte(sent_tid, DAS_UNKN));
  }
  /* We only get here on the two proxy calls: proxies don't need reply */
  return(0);
}

/* Need a 'current time stamp' different from the one in dbr_info,
   since that one pertains to stuff already being transmitted.
   Need to optimize for wrap-around when DG_s_data is augmented
   to support two blocks of data.
*/
int DG_get_data(unsigned int n_rows) {
  int rowlim, i;
  
  if (trans_row != col_row) {
	if (tsps[trans_row] != NULL) {
	  DG_s_tstamp(tsps[trans_row]);
	  tsps[trans_row] = NULL;
	} else {
	  rowlim = trans_row + n_rows;
	  if (DP_NROWS < rowlim) rowlim = DP_NROWS;
	  if (col_row > trans_row && col_row < rowlim) rowlim = col_row;
	  for (i = trans_row; i < rowlim && tsps[i] == NULL; i++);
	  assert(i != trans_row);
	  DG_s_data(i-trans_row, dpdata[trans_row], 0, NULL);
	  trans_row = i;
	  if (trans_row == DP_NROWS) trans_row = 0;
	}
  }
  return(0);
}

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
