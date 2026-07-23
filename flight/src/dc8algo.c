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



 typedef float vaifloat;
#include "integrate.h"
#include "tmctime.h"
#include "nl_dsp.h"

/* make sure the defined INTPEAKS in integrate.c
   equals the number of peaks integrated */

intStruct CH4int;	/* channel 1 */
intStruct CFC11int;	/* channel 2 */
intStruct CFC12int;	/* channel 2 */
intStruct N2Oint;	/* channel 3 */
intStruct SF6int;	/* channel 3 */





int old_ssv1min;	
int old_ssv1fold;	
int old_ssv2min;	
int old_ssv2fold; typedef float MixRatio;

MixRatio MR_CH4;
MixRatio MR_CFC12;
MixRatio MR_N2O;
MixRatio MR_SF6;
MixRatio MR_CFC11;



int secondhalf;
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include "nortlib.h"
	#include "globmsg.h"

#define NUMAIRINJ 	2		// number of air injections between cal injections
#define NUMCALINJ 	1		// number of cal injections between air injections

unsigned int AirCount = 0;
unsigned int CalCount = 0;

unsigned int STATUS = 1;			// NASDAT status variable 
unsigned int STATUS_WARNING = 0;	// used with status variable

#include "nasdat.h"
char nasdatMSG[NASDAT_MAXDATA];

#include "kuband.h"
char kuMSG[KUDATA_MAXDATA];

  #include "nortlib.h"
  #include "tma.h"
  char ci_version[] = "$CGID: uavcmd.c: Sat Feb  4 16:22:54 2023 $";

  tma_state initialize_cmds_[] = {
       0, ">Telemetry Start\n",
       0, ">Pump GC Off\n",
       2, ">Nitrogen Open\n",
       3, ">Flow main channel 1 40\n",
      15, ">Mode GC Init\n",
      20, ">sample air\n",
      21, "#2", /* GCReady */
      -1, NULL
  };

  tma_state GCReady_cmds_[] = {
       5, ">\n",
       5, "#4", /* SSVtableInit */
       5, "#13", /* GCReady_end_ */
      -1, NULL
  };

  tma_state Idle_cmds_[] = {
      -1, NULL
  };

  tma_state SSVtableInit_cmds_[] = {
      -1, NULL
  };

  tma_state SSVtable_cmds_[] = {
      -1, NULL
  };

  tma_state AIRnext_cmds_[] = {
       2, ">Sample Air\n",
       2, "#15", /* AIRnext_1_ */
       3, "#5", /* SSVtable */
       3, "#14", /* part_1_idle_ */
      -1, NULL
  };

  tma_state CALnext_cmds_[] = {
       2, ">Sample Cal\n",
       2, "#16", /* CALnext_1_ */
       3, "#5", /* SSVtable */
       3, "#14", /* part_1_idle_ */
      -1, NULL
  };

  tma_state NASDAT_eng_cmds_[] = {
      -1, NULL
  };

  tma_state KUDATA_eng_cmds_[] = {
      -1, NULL
  };

  tma_state ShutdownComputer_cmds_[] = {
       1, "#20", /* ShutdownComputer_end_ */
      -1, NULL
  };

  tma_state Shutdown_cmds_[] = {
       0, ">Shutdown\n",
      -1, NULL
  };

  const int tma_n_partitions = 5;

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
unsigned char V10 = 0x1;
unsigned char V11 = 0x1;
unsigned char V12 = 0x3;
unsigned char V13 = 0x3;
unsigned char V14 = 0x1;
unsigned char V15 = 0x1;
unsigned char V16 = 0x1;
unsigned char V17 = 0x1;
unsigned char V18 = 0x7F;
unsigned int V19 = 0xFFFF;
unsigned char V20 = 0x1;
ULONG CHROMtime;
SCCMpnu flow_M1;
SCCMpnu flow_BF1;
PSIBpnu pres_BP1;
MBARpnu pres_ECD1;
CELS temp_gasB_N;
CELS temp_SL1;
CELS temp_amb;
SCCMsl flow_SL;
SCCMpnu flow_M2;
SCCMpnu flow_BF2;
PSIBpnu pres_BP2;
MBARpnu pres_ECD2;
CELS temp_pump;
CELS temp_SL2;
CELS temp_gasB_C;
MBAR pres_PUMP;
SCCMpnu flow_M3;
SCCMpnu flow_BF3;
MBARpnu pres_ECD3;
CELS temp_SL3;
MBAR pres_extern;
MBARpnuSL pres_SL;
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
tdlfloas tdl_t;
tdlint6  tdl_amp;
tdlint6  tdl_pow;
tdlint6  tdl_pos;
tdlint6  tdl_zer;
tdlfloat tdl_best;
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
/* doub_cvt for PSIH -> PRESS */
double _CVT_0( PSIH x ) {
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
/* doub_cvt for PSIL -> PRESS */
double _CVT_1( PSIL x ) {
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
/* doub_cvt for PSIBpnu -> PRESS */
double _CVT_2( PSIBpnu x ) {
  double ov;

  if (x <= -1e-005) {
    ov = -999.9;
  } else {
    if (x <= 0) {
      ov = 99990000 * x;
    } else {
      ov = 40 * x;
    }
  }
  return(ov);
}
/* doub_cvt for SCCMsl -> FLOW */
double _CVT_3( SCCMsl x ) {
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
/* doub_cvt for SCCMpnu -> FLOW */
double _CVT_4( SCCMpnu x ) {
  double ov;

  if (x <= -0.01) {
    ov = -999.9;
  } else {
    if (x <= 0) {
      ov = 99990 * x;
    } else {
      ov = 80 * x;
    }
  }
  return(ov);
}
/* doub_cvt for CELS -> TEMP */
double _CVT_5( CELS x ) {
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
/* doub_cvt for MBARpnuSL -> PRESS */
double _CVT_6( MBARpnuSL x ) {
  double ov;

  if (x <= 0) {
    if (x <= -2e-005) {
      ov = -999.9;
    } else {
      ov = 49945000 * x-1;
    }
  } else {
    if (x <= 0.02) {
      ov = 36250 * x-1;
    } else {
      if (x <= 4.5) {
        ov = 123.21429 * x+721.53571;
      } else {
        ov = 122 * x+727;
      }
    }
  }
  return(ov);
}
/* doub_cvt for MBARpnu -> PRESS */
double _CVT_7( MBARpnu x ) {
  double ov;

  if (x <= 0) {
    if (x <= -2e-005) {
      ov = -999.9;
    } else {
      ov = 49945000 * x-1;
    }
  } else {
    if (x <= 0.2) {
      ov = 3990 * x-1;
    } else {
      ov = 203.78378 * x+756.24324;
    }
  }
  return(ov);
}
/* doub_cvt for MBAR -> PRESS */
double _CVT_8( MBAR x ) {
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
/* doub_cvt for VOLTS28 -> VOL5 */
double _CVT_9( VOLTS28 x ) {
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
/* doub_cvt for VOLTSPM -> VOL5 */
double _CVT_10( VOLTSPM x ) {
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
/* doub_cvt for VOLTS512 -> VOL5 */
double _CVT_11( VOLTS512 x ) {
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
static void VSET_15_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 2: /* ShutdownComputer_end_ */
      V20 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* ShutdownComputer_end_ */
      V20 &= ~0x1;
      break;
  }
}
static void VSET_14_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
  }
  oldstate = newstate;
  switch (newstate) {
  }
}
static void VSET_13_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
  }
  oldstate = newstate;
  switch (newstate) {
  }
}
static void VSET_12_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
  }
  oldstate = newstate;
  switch (newstate) {
    case 3: /* CALnext_1_ */ {
        { if ( ++CalCount == NUMCALINJ ) CalCount = 500; } { STATUS = 1 + 2 + 4 + STATUS_WARNING; }
      }
      break;
    case 2: /* AIRnext_1_ */ {
        { if ( ++AirCount == NUMAIRINJ ) {
        			AirCount = 0;
        			CalCount = 0;
        		 }
        	   } { STATUS = 1 + 2 + STATUS_WARNING; }
      }
      break;
  }
}
static void VSET_11_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* GCReady_end_ */ {
        { msg( 0, "Ready for injections" ); }
      }
      break;
  }
}
static void VSET_10_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* Shutdown */ {
        {
          tma_init_state( 4, Shutdown_cmds_, "Shutdown" ); VSET_15_(1);
        }
      }
      break;
    case 1: /* ShutdownComputer */ {
        {
          tma_init_state( 4, ShutdownComputer_cmds_, "ShutdownComputer" ); VSET_15_(1);
        }
      }
      break;
  }
}
static void VSET_9_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 1: /* KUDATA_eng */
      V19 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 1: /* KUDATA_eng */ {
        V19 &= ~0x1;
        {
          tma_init_state( 3, KUDATA_eng_cmds_, "KUDATA_eng" ); VSET_14_(1);
        }
      }
      break;
  }
}
static void VSET_8_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 1: /* NASDAT_eng */
      V18 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 1: /* NASDAT_eng */ {
        V18 &= ~0x1;
        {
          tma_init_state( 2, NASDAT_eng_cmds_, "NASDAT_eng" ); VSET_13_(1);
        }
      }
      break;
  }
}
static void VSET_7_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 3: /* SSVtable */
      V14 |= 0x1;
      break;
    case 2: /* SSVtableInit */
      V13 |= 0x2;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 5: /* CALnext */ {
        {
          tma_init_state( 1, CALnext_cmds_, "CALnext" ); VSET_12_(1);
        }
      }
      break;
    case 4: /* AIRnext */ {
        {
          tma_init_state( 1, AIRnext_cmds_, "AIRnext" ); VSET_12_(1);
        }
      }
      break;
    case 3: /* SSVtable */ {
        V14 &= ~0x1;
        {
          tma_init_state( 1, SSVtable_cmds_, "SSVtable" ); VSET_12_(1);
        }
      }
      break;
    case 2: /* SSVtableInit */ {
        V13 &= ~0x2;
        {
          tma_init_state( 1, SSVtableInit_cmds_, "SSVtableInit" ); VSET_12_(1);
        }if (!(V13)) {
          { VSET_7_(3);
          	}
        }
      }
      break;
    case 1: /* Idle */ {
        {
          tma_init_state( 1, Idle_cmds_, "Idle" ); VSET_12_(1);
        }
      }
      break;
  }
}
static void VSET_6_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* GCReady */ {
        {
          tma_init_state( 0, GCReady_cmds_, "GCReady" ); VSET_11_(1);
        }
      }
      break;
    case 1: /* initialize */ {
        {
          tma_init_state( 0, initialize_cmds_, "initialize" ); VSET_11_(1);
        }
      }
      break;
  }
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
    case 4: /* Injecting2 */ {
        V16 |= 0x1;
        V13 |= 0x1;
        V11 |= 0x1;
      }
      break;
    case 3: /* Injection */
      V1 |= 0x1;
      break;
    case 2: /* Injecting1 */ {
        V15 |= 0x1;
        V10 |= 0x1;
        V3 |= 0x1;
      }
      break;
    case 1: /* NotInjecting */
      V17 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 4: /* Injecting2 */ {
        V16 &= ~0x1;
        V13 &= ~0x1;
        V11 &= ~0x1;
        { secondhalf = 1; }if (!(V13)) {
          { VSET_7_(3);
          	}
        }
      }
      break;
    case 3: /* Injection */
      V1 &= ~0x1;
      break;
    case 2: /* Injecting1 */ {
        V15 &= ~0x1;
        V10 &= ~0x1;
        V3 &= ~0x1;
        { secondhalf = 0; }
      }
      break;
    case 1: /* NotInjecting */ {
        V17 &= ~0x1;
        {
        
        	N2Oint.mol = "n2o";		
        	N2Oint.pnum = 0;		
        	N2Oint.strt = 46;		
        	N2Oint.stop = 73;		
        	N2Oint.calval = 332.52;	
        	N2Oint.calssv = 1;		
        	N2Oint.delay = 0;		
        	N2Oint.rt_a = 1.0;		
        	N2Oint.rt_b = 0.0;		
        
        	CFC12int.mol = "cfc12";	
        	CFC12int.pnum = 1;		
        	CFC12int.strt = 45;		
        	CFC12int.stop = 55;		
        	CFC12int.calval = 482.6;	
        	CFC12int.calssv = 1;	
        	CFC12int.delay = 0; 	
        	CFC12int.rt_a = 1.0;	
        	CFC12int.rt_b = 0.0;	
        
        	SF6int.mol = "sf6";		
        	SF6int.pnum = 2;		
        	SF6int.strt = 32;		
        	SF6int.stop = 46;		
        	SF6int.calval = 11.22;	
        	SF6int.calssv = 1;		
        	SF6int.delay = 0;		
        	SF6int.rt_a = 1.0;		
        	SF6int.rt_b = 0.0;		
        
        	CH4int.mol = "ch4";		
        	CH4int.pnum = 3;		
        	CH4int.strt = 4;		
        	CH4int.stop = 22;		
        	CH4int.calval = 1945.7;	
        	CH4int.calssv = 1;		
        	CH4int.delay = 75;		
        	CH4int.rt_a = 1.0;		
        	CH4int.rt_b = 0.0;		
        
        	CFC11int.mol = "cfc11";	
        	CFC11int.pnum = 4;		
        	CFC11int.strt = 3;		
        	CFC11int.stop = 17;		
        	CFC11int.calval = 217.0;	
        	CFC11int.calssv = 1;	
        	CFC11int.delay = 75; 	
        	CFC11int.rt_a = 1.0;	
        	CFC11int.rt_b = 0.0;	
        
        } { secondhalf = 0; }
      }
      break;
  }
}
static void tminitfunc(void) {VSET_0_(1);VSET_1_(1);VSET_2_(1);VSET_3_(1);VSET_4_(1);VSET_5_(1);VSET_6_(1);VSET_7_(1);VSET_8_(1);VSET_9_(1);VSET_10_(1);VSET_11_(1);VSET_12_(1);VSET_13_(1);VSET_14_(1);VSET_15_(1);
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
  {if (!(V12)) {
    {
    	
    		if (( home->U0.GC_Ctr_CH1 != ECDOFFLINE ) && ( secondhalf == 0 )) {
    			integrate( 0, home->U0.GC_Ctr_CH1, CH4int, CHROMtime, old_ssv2min );
    		}
    
    		if ( home->U0.GC_Ctr_CH2 != ECDOFFLINE ) {
    			integrate( 0, home->U0.GC_Ctr_CH2, CFC12int, CHROMtime, old_ssv1min );
    		}
    
    		if ( home->U0.GC_Ctr_CH3 != ECDOFFLINE ) {
    			integrate( 0, home->U0.GC_Ctr_CH3, N2Oint, CHROMtime, old_ssv1min );
    		}
    
    		if ( home->U0.GC_Ctr_CH3 != ECDOFFLINE ) {
    			integrate( 0, home->U0.GC_Ctr_CH3, SF6int, CHROMtime, old_ssv1min );
    		}
    
    		if ( home->U0.GC_Ctr_CH2 != ECDOFFLINE ) {
    			integrate( 0, home->U0.GC_Ctr_CH2, CFC11int, CHROMtime, old_ssv1fold );
    		}
    
    	}
  }
  
  }
}

static void EF8_0(void) {
  tdl_H2OCD = home->U39.tdl_H2OCD;
  tdl_p = home->U19.tdl_p;
  tdl_t = home->U19.tdl_t;
  tdl_amp = home->U19.tdl_amp;
  tdl_pow = home->U21.tdl_pow;
  tdl_pos = home->U21.tdl_pos;
  tdl_zer = home->U21.tdl_zer; {
    V19 &= ~0x2000;
    V8 &= ~0x2;
  }
  EF1_0();
  {
      if (maycomm_proxy != 0)  Trigger (maycomm_proxy);
  }
}

static void BF16_0(void) {
  V12 &= ~0x2;
  EF8_0();
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
  	}V19 &= ~0x4;
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
  	}V19 &= ~0x2;
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
  	}V19 &= ~0x8;
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
  	MR_N2O = MRres( 0 );V18 &= ~0x2;
  }
  { 
  	MR_CFC12 = MRres( 1 );V18 &= ~0x8;
  }
  { 
  	MR_SF6 = MRres( 2 );V18 &= ~0x4;
  }
  { 
  	MR_CH4 = MRres( 3 );
  }
  { 
  	MR_CFC11 = MRres( 4 );
  }
  if (!(V14)) {
    {if (!(V15)) {
      { 
      			if ( CalCount < NUMCALINJ ) VSET_7_(5);
      			else VSET_7_(4);
      		}
    }if (!(V16)) {
      { 
      			if ( CalCount < NUMCALINJ ) VSET_7_(5);
      			else VSET_7_(4);
      		}
    }if (!(V17)) {
      {
      			AirCount = 0;
      			CalCount = 0; VSET_7_(2);
      		}
    }
    
    	}
  }
  {
    long int it;
    int subcase;
  
    it = itime();
    ci_settime( it );
    while ( subcase = tma_process( it ) ) {
  	switch (subcase) {
  	  case -1:
  	  case 0: break;
  	  case 1: VSET_6_(1); break;
  	  case 2: VSET_6_(2); break;
  	  case 3: VSET_7_(1); break;
  	  case 4: VSET_7_(2); break;
  	  case 5: VSET_7_(3); break;
  	  case 6: VSET_7_(4); break;
  	  case 7: VSET_7_(5); break;
  	  case 8: VSET_8_(1); break;
  	  case 9: VSET_9_(1); break;
  	  case 10: VSET_10_(1); break;
  	  case 11: VSET_10_(2); break;
  	  case 12: VSET_11_(1); break;
  	  case 13: VSET_11_(2); break;
  	  case 14: VSET_12_(1); break;
  	  case 15: VSET_12_(2); break;
  	  case 16: VSET_12_(3); break;
  	  case 17: VSET_13_(1); break;
  	  case 18: VSET_14_(1); break;
  	  case 19: VSET_15_(1); break;
  	  case 20: VSET_15_(2); break;
  	  default:
  		nl_error( 1, "Unexpected return value from tma_process" );
  		break;
  	}
    }
  }
}

static void BF128_0(void) {
  BF16_0();
  {
  	if (o3_proxy != 0)	Trigger ( o3_proxy );
  }
}

static void EF8_1(void) {
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

static void BF16_1(void) {
  CH1_Col = home->U5.CH1_Col;
  V19 &= ~0x4000;
  EF8_1();
}

static void EF8_2(void) {
  tdl_best = home->U23.tdl_best;
  V18 &= ~0x40;
  EF1_0();
  if (!(V8)) {
    {
    	home->U23.tdl_shortcorr = -824 + 1.160*tdl_shortH2O;
    	home->U21.tdl_longcorr = -9.62 + .776*tdl_longH2O*(1 + .0003*tdl_p) + .00099*tdl_longH2O*tdl_longH2O/(1 + .00176*tdl_p);
    	home->U23.tdl_CDcorr = ZeroOffset + (.778*tdl_H2OCD + .00132*tdl_H2OCD*tdl_H2OCD)/(1 + .000268*tdl_p);
        tdl_best = home->U21.tdl_longcorr;
    
        if (home->U21.tdl_longcorr < USECD) tdl_best = home->U23.tdl_CDcorr;
        if (home->U21.tdl_longcorr > USEShort) tdl_best = home->U23.tdl_shortcorr;
    }
  }
}

static void BF16_3(void) {
  o3x = home->U15.o3x;
  o3xtemp = home->U13.o3xtemp;
  o3xpres = home->U15.o3xpres;
  o3xflowa = home->U15.o3xflowa;
  o3xflowb = home->U15.o3xflowb;
  CH1_ECD = home->U3.CH1_ECD; {
    V19 &= ~0x1000;
    V6 &= ~0x1;
  }
  EF1_0();
}

static void BF16_4(void) {
  flow_BF2 = home->U1.flow_BF2;
  flow_BF1 = home->U3.flow_BF1;
  CHROMtime = home->U0.CHROMtime; {
    V19 &= ~0x20;
    V12 &= ~0x1;
    V0 &= ~0x1;
  }
  EF1_0();
  home->U0.CUMSEC++;
}

static void BF16_5(void) {
  CH2_Col = home->U7.CH2_Col;
  flow_M2 = home->U0.flow_M2;
  flow_M1 = home->U1.flow_M1;
  flow_BF3 = home->U7.flow_BF3;
  V19 &= ~0x10;
  EF1_0();
}

static void BF16_6(void) {
  o3xbest = home->U21.o3xbest;
  o3best = home->U17.o3best;
  flow_SL = home->U5.flow_SL;
  flow_M3 = home->U5.flow_M3; {
    V19 &= ~0x200;
    V18 &= ~0x20;
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

static void BF16_7(void) {
  CH2_ECD = home->U9.CH2_ECD;
  pres_ECD1 = home->U1.pres_ECD1;
  pres_BP2 = home->U7.pres_BP2;
  pres_BP1 = home->U1.pres_BP1;
  V19 &= ~0x40;
  EF1_0();
}

static void BF16_10(void) {
  CH3_Col = home->U1.CH3_Col;
  pres_ECD3 = home->U9.pres_ECD3;
  pres_ECD2 = home->U3.pres_ECD2;
  V19 &= ~0x8000;
  EF8_2();
}

static void BF16_11(void) {
  presL_dope = home->U11.presL_dope;
  presL_cal = home->U9.presL_cal;
  presH_123 = home->U9.presH_123;
  pres_SL = home->U11.pres_SL;
  pres_PUMP = home->U5.pres_PUMP;
  pres_extern = home->U9.pres_extern; {
    V19 &= ~0x80;
    V18 &= ~0x10;
  }
  EF1_0();
}

static void BF16_12(void) {
  CH3_ECD = home->U0.CH3_ECD;
  temp_SL1 = home->U3.temp_SL1;
  temp_pump = home->U5.temp_pump;
  temp_gasB_N = home->U3.temp_gasB_N;
  temp_gasB_C = home->U9.temp_gasB_C;
  temp_amb = home->U3.temp_amb;
  presL_N2 = home->U11.presL_N2;
  V19 &= ~0x100;
  EF1_0();
  if (!(V18)) {
    {	sprintf( nasdatMSG, "xUCATS:%02d", STATUS );
    		nasdat_format_f( nasdatMSG, "%06.1f",_CVT_0(presH_123) );
    		nasdat_format_f( nasdatMSG, "%06.1f",_CVT_1(presL_N2) );
    		nasdat_format_f( nasdatMSG, "%06.1f",_CVT_5(temp_amb) );
    		nasdat_format_a( nasdatMSG, "%06.1f", o3xbest );
    		nasdat_format_f( nasdatMSG, "%06.1f", MR_N2O );
    		nasdat_format_f( nasdatMSG, "%06.2f", MR_SF6 );
    		nasdat_format_f( nasdatMSG, "%06.1f", MR_CCl4 );
    		nasdat_format_f( nasdatMSG, "%06.1f", MR_CFC12 );
    		nasdat_format_f( nasdatMSG, "%06.1f", tdl_best );
    		sprintf( nasdatMSG, "%s\n", nasdatMSG );
    		
    		send2nasdat( &nasdatMSG );
    	}
  }
}

static void BF16_13(void) {
  volt_28 = home->U13.volt_28;
  volt_15 = home->U11.volt_15;
  temp_SL3 = home->U11.temp_SL3;
  temp_SL2 = home->U3.temp_SL2;
  V19 &= ~0x400;
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
  CH3_Post = home->U13.CH3_Post;
  volt_5 = home->U13.volt_5;
  V19 &= ~0x800;
  EF1_0();
  { ITXFileNum = home->U0.CurrInj * 1000 + home->U0.CurrFile;
  }
  if (!(V20)) {
    { if ( home->U13.InitShutdown == FALSE ) VSET_10_(2); }
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
        old_ssv2fold = old_ssv2min;
    	old_ssv2min = home->U15.ssv;
        old_ssv1fold = old_ssv1min;
    	old_ssv1min = home->U15.ssv;
    }
  }
  if (!(V11)) {
    {
        old_ssv1fold = old_ssv1min;
    	old_ssv1min = home->U15.ssv;
    }
  }
  if (!(V19)) {
    {	
    		
    		sprintf(kuMSG, "\0");	    
    		KUformat_f(kuMSG, "flow_M1=%6.1f",_CVT_4(flow_M1), 		0);
    		KUformat_f(kuMSG, "flow_BF1=%6.1f",_CVT_4(flow_BF1), 		0);
    		KUformat_f(kuMSG, "pres_ECD1=%6.1f",_CVT_7(pres_ECD1), 	0);
    		KUformat_f(kuMSG, "pres_BP1=%6.1f",_CVT_2(pres_BP1), 		0);
    		KUformat_f(kuMSG, "pres_SL=%6.1f",_CVT_6(pres_SL), 		0);
    		KUformat_f(kuMSG, "temp_gasB_N=%6.1f",_CVT_5(temp_gasB_N),	0);
    		KUformat_f(kuMSG, "temp_SL1=%6.1f",_CVT_5(temp_SL1),		0);
    		KUformat_f(kuMSG, "temp_gasB_C=%6.1f",_CVT_5(temp_gasB_C), 	0);
    		KUformat_f(kuMSG, "flow_SL=%6.1f",_CVT_3(flow_SL), 		0);
    		KUformat_f(kuMSG, "flow_M2=%6.1f",_CVT_4(flow_M2), 		0);
    		KUformat_f(kuMSG, "flow_BF2=%6.1f",_CVT_4(flow_BF2),		0);
    		KUformat_f(kuMSG, "pres_PUMP=%6.1f",_CVT_8(pres_PUMP), 	0);
    		KUformat_f(kuMSG, "pres_BP2=%6.1f",_CVT_2(pres_BP2), 		0);
    		KUformat_f(kuMSG, "pres_ECD2=%6.1f",_CVT_7(pres_ECD2), 	0);
    		KUformat_f(kuMSG, "flow_M3=%6.1f",_CVT_4(flow_M3), 		0);
    		KUformat_f(kuMSG, "flow_BF3=%6.1f",_CVT_4(flow_BF3),		0);
    		KUformat_f(kuMSG, "pres_ECD3=%6.1f",_CVT_7(pres_ECD3), 	0);
    		KUformat_d(kuMSG, "ecdA_CH1=%ld", 		ecdA_CH1, 				0);
    		KUformat_d(kuMSG, "ecdA_CH2=%ld", 		ecdA_CH2, 				0);
    		KUformat_d(kuMSG, "ecdA_CH3=%ld", 		ecdA_CH3, 				0);
    		KUformat_f(kuMSG, "temp_pump=%6.1f",_CVT_5(temp_pump),	  -30);
    		KUformat_f(kuMSG, "temp_SL2=%6.1f",_CVT_5(temp_SL2), 		0);
    		KUformat_f(kuMSG, "temp_SL3=%6.1f",_CVT_5(temp_SL3), 		0);
    		KUformat_f(kuMSG, "temp_amb=%6.1f",_CVT_5(temp_amb), 		0);
    		KUformat_f(kuMSG, "pres_extern=%6.1f",_CVT_8(pres_extern), 	0);
    		KUformat_f(kuMSG, "presL_dope=%6.1f",_CVT_1(presL_dope), 	0);
    		KUformat_f(kuMSG, "presL_cal=%6.1f",_CVT_1(presL_cal), 	0);
    		KUformat_f(kuMSG, "presL_N2=%6.1f",_CVT_1(presL_N2), 		0);
    		KUformat_f(kuMSG, "presH_123=%6.1f",_CVT_0(presH_123), 	0);
    		KUformat_f(kuMSG, "volt_5=%7.3f",_CVT_11(volt_5), 		0);
    		KUformat_f(kuMSG, "volt_15=%6.2f",_CVT_10(volt_15), 	  -20);
    		KUformat_f(kuMSG, "volt_28=%6.2f",_CVT_9(volt_28), 		0);
    		KUformat_f(kuMSG, "CH3_ECD=%6.1f", 		CH3_ECD/10., 			0);
    		KUformat_f(kuMSG, "CH3_Col=%6.1f", 		CH3_Col/10., 			0);
    		KUformat_f(kuMSG, "CH3_Post=%6.1f", 	CH3_Post/10., 			0);
    		KUformat_f(kuMSG, "CH1_ECD=%6.1f", 		CH1_ECD/10., 			0);
    		KUformat_f(kuMSG, "CH1_Col=%6.1f", 		CH1_Col/10., 			0);
    		KUformat_f(kuMSG, "CH2_ECD=%6.1f", 		CH2_ECD/10., 			0);
    		KUformat_f(kuMSG, "CH2_Col=%6.1f", 		CH2_Col/10., 			0);
    		KUformat_d(kuMSG, "GCstate=%02d", 		home->U0.GCstate, 				0);
    		KUformat_d(kuMSG, "ssv=%d", 			home->U15.ssv, 					0);
    		KUformat_f(kuMSG, "tdl_p=%6.1f", 		tdl_p, 					0);
    		KUformat_f(kuMSG, "tdl_t=%6.1f", 		tdl_t, 					0);
    		KUformat_f(kuMSG, "tdl_shortH2O=%6.1f", tdl_shortH2O, 			0);
    		KUformat_f(kuMSG, "tdl_longH2O=%6.1f", 	tdl_longH2O, 			0);
    		KUformat_f(kuMSG, "tdl_H2OCD=%6.1f", 	tdl_H2OCD,  			0);
    		KUformat_f(kuMSG, "tdl_amp=%6.1f", 		tdl_amp, 				0);
    		KUformat_f(kuMSG, "tdl_pow=%6.1f", 		tdl_pow, 				0);
    		KUformat_f(kuMSG, "tdl_pos=%6.1f", 		tdl_pos, 				0);
    		KUformat_f(kuMSG, "tdl_zer=%6.1f", 		tdl_zer, 				0);
    		KUformat_f(kuMSG, "tdl_best=%6.1f", 	tdl_best, 				0);
    		KUformat_f(kuMSG, "o3x=%6.1f", 			o3x, 				 -500);
    		KUformat_f(kuMSG, "o3xtemp=%6.1f", 		o3xtemp, 				0);
    		KUformat_f(kuMSG, "o3xpres=%6.1f", 		o3xpres,				0);
    		KUformat_f(kuMSG, "o3xbest=%6.1f", 		o3xbest, 			 -500);
    		KUformat_d(kuMSG, "o3xflowa=%d", 		o3xflowa,			   -1);
    		KUformat_d(kuMSG, "o3xflowb=%d", 		o3xflowb,			   -1);	
    		
    		send2kuband("eng", &kuMSG);
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
  BF16_1,
  EF8_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  EF8_0,
  EF8_1,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  EF16_15,
  BF16_0,
  BF16_1,
  EF8_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  EF8_0,
  EF8_1,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  EF16_15,
  BF16_0,
  BF16_1,
  EF8_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  EF8_0,
  EF8_1,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  BF128_47,
  BF16_0,
  BF16_1,
  EF8_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  EF8_0,
  EF8_1,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  EF16_15,
  BF16_0,
  BF16_1,
  EF8_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  EF8_0,
  EF8_1,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  BF128_79,
  BF16_0,
  BF16_1,
  EF8_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  EF8_0,
  EF8_1,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  EF16_15,
  BF16_0,
  BF16_1,
  EF8_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  EF8_0,
  EF8_1,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  EF16_15,
  BF16_0,
  BF16_1,
  EF8_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  EF8_0,
  EF8_1,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  EF16_15
};

static void IVF8_0(void) { {
    V19 |= 0x2000;
    V8 |= 0x2;
  }
}
static void IVF16_0(void) {IVF8_0();
  V12 |= 0x2;
}
static void IVF8_1(void) {
  V8 |= 0x1;
}
static void IVF16_1(void) {IVF8_1();
  V19 |= 0x4000;
}
static void IVF8_2(void) {
  V18 |= 0x40;
}
static void IVF16_3(void) { {
    V19 |= 0x1000;
    V6 |= 0x1;
  }
}
static void IVF16_4(void) { {
    V19 |= 0x20;
    V12 |= 0x1;
    V0 |= 0x1;
  }
}
static void IVF16_5(void) {
  V19 |= 0x10;
}
static void IVF16_6(void) { {
    V19 |= 0x200;
    V18 |= 0x20;
    V5 |= 0x1;
  }
}
static void IVF16_7(void) {
  V19 |= 0x40;
}
static void IVF16_10(void) {IVF8_2();
  V19 |= 0x8000;
}
static void IVF16_11(void) { {
    V19 |= 0x80;
    V18 |= 0x10;
  }
}
static void IVF16_12(void) {
  V19 |= 0x100;
}
static void IVF16_13(void) {
  V19 |= 0x400;
}
static void IVF16_14(void) {
  V19 |= 0x800;
}
static void IVF128_47(void) {
  V5 |= 0x2;
}
#define IVFUNCS
static void (*ivfuncs[128])() = {
  IVF16_0,
  IVF16_1,
  IVF8_2,
  IVF16_3,
  IVF16_4,
  IVF16_5,
  IVF16_6,
  IVF16_7,
  IVF8_0,
  IVF8_1,
  IVF16_10,
  IVF16_11,
  IVF16_12,
  IVF16_13,
  IVF16_14,
  nullfunc,
  IVF16_0,
  IVF16_1,
  IVF8_2,
  IVF16_3,
  IVF16_4,
  IVF16_5,
  IVF16_6,
  IVF16_7,
  IVF8_0,
  IVF8_1,
  IVF16_10,
  IVF16_11,
  IVF16_12,
  IVF16_13,
  IVF16_14,
  nullfunc,
  IVF16_0,
  IVF16_1,
  IVF8_2,
  IVF16_3,
  IVF16_4,
  IVF16_5,
  IVF16_6,
  IVF16_7,
  IVF8_0,
  IVF8_1,
  IVF16_10,
  IVF16_11,
  IVF16_12,
  IVF16_13,
  IVF16_14,
  IVF128_47,
  IVF16_0,
  IVF16_1,
  IVF8_2,
  IVF16_3,
  IVF16_4,
  IVF16_5,
  IVF16_6,
  IVF16_7,
  IVF8_0,
  IVF8_1,
  IVF16_10,
  IVF16_11,
  IVF16_12,
  IVF16_13,
  IVF16_14,
  nullfunc,
  IVF16_0,
  IVF16_1,
  IVF8_2,
  IVF16_3,
  IVF16_4,
  IVF16_5,
  IVF16_6,
  IVF16_7,
  IVF8_0,
  IVF8_1,
  IVF16_10,
  IVF16_11,
  IVF16_12,
  IVF16_13,
  IVF16_14,
  nullfunc,
  IVF16_0,
  IVF16_1,
  IVF8_2,
  IVF16_3,
  IVF16_4,
  IVF16_5,
  IVF16_6,
  IVF16_7,
  IVF8_0,
  IVF8_1,
  IVF16_10,
  IVF16_11,
  IVF16_12,
  IVF16_13,
  IVF16_14,
  nullfunc,
  IVF16_0,
  IVF16_1,
  IVF8_2,
  IVF16_3,
  IVF16_4,
  IVF16_5,
  IVF16_6,
  IVF16_7,
  IVF8_0,
  IVF8_1,
  IVF16_10,
  IVF16_11,
  IVF16_12,
  IVF16_13,
  IVF16_14,
  nullfunc,
  IVF16_0,
  IVF16_1,
  IVF8_2,
  IVF16_3,
  IVF16_4,
  IVF16_5,
  IVF16_6,
  IVF16_7,
  IVF8_0,
  IVF8_1,
  IVF16_10,
  IVF16_11,
  IVF16_12,
  IVF16_13,
  IVF16_14,
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
