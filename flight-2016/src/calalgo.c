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
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include "nortlib.h"
	#include "globmsg.h"
	#include "addresses.h"
    #include "valves.h"

#define N2fail  20		// psi		(below this value set ECDs cold)

// the array "Sequence" can be any length. Sequence contains the
// sequence of SSV positions for a calibration run.  Running caldoit
// and starting the cal mode will call these routines.

// select position 20 to sample from the internal cal solenoid
// for cal expts. with flight cal tank in cal position
//unsigned int Sequence[] = {20,1,3,5,11};
//unsigned int Sequence[] = {1,1,3,3,5,5,11,11};
// for tests:
unsigned int Sequence[] = {1,1,1,20};
unsigned int NUMCALSEQ = sizeof(Sequence)/sizeof(unsigned int);
unsigned int SeqIndex = 0;

unsigned int N2lowCount = 0;
unsigned int MAXN2LOWCNTS = 10;

  #include "nortlib.h"
  #include "tma.h"
  char ci_version[] = "$CGID: uavcmd.c: Tue Dec 27 16:59:08 2016 $";

  tma_state initialize_cmds_[] = {
       0, ">Telemetry Start\n",
      15, ">Mode GC Init\n",
      20, ">ssv goto position 1\n",
      20, ">sample air\n",
      -1, NULL
  };

  tma_state CalSSV_cmds_[] = {
      -1, NULL
  };

  tma_state Cal_pos_cmds_[] = {
       1, ">sample cal\n",
       3, "#12", /* Cal_pos_1_ */
       8, "#2", /* CalSSV */
       8, "#11", /* part_1_idle_ */
      -1, NULL
  };

  tma_state Air_pos_cmds_[] = {
       1, ">sample air\n",
       3, "#13", /* Air_pos_1_ */
       8, "#2", /* CalSSV */
       8, "#11", /* part_1_idle_ */
      -1, NULL
  };

  tma_state NextCal_cmds_[] = {
      72, "#14", /* NextCal_end_ */
      -1, NULL
  };

  tma_state CheckCarrier_cmds_[] = {
      10, "#16", /* CheckCarrier_end_ */
      -1, NULL
  };

  tma_state SetECDsCold_cmds_[] = {
       1, ">Omega change SP1 CH1 ECD 10\n",
       2, ">Omega change SP1 CH2 ECD 10\n",
      -1, NULL
  };

  tma_state ShutdownComputer_cmds_[] = {
       1, "#18", /* ShutdownComputer_end_ */
      -1, NULL
  };

  tma_state Shutdown_cmds_[] = {
       0, ">Shutdown\n",
      -1, NULL
  };

  const int tma_n_partitions = 4;

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
unsigned char V10 = 0x3;
unsigned char V11 = 0x1;
unsigned char V12 = 0x1;
ULONG CHROMtime;
o3float o3pres;
o3float o3x;
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
/* doub_cvt for PSIL -> PRESS */
double _CVT_0( PSIL x ) {
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
static void VSET_13_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 2: /* ShutdownComputer_end_ */
      V12 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* ShutdownComputer_end_ */
      V12 &= ~0x1;
      break;
  }
}
static void VSET_12_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 2: /* CheckCarrier_end_ */
      V11 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* CheckCarrier_end_ */
      V11 &= ~0x1;
      break;
  }
}
static void VSET_11_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
  }
  oldstate = newstate;
  switch (newstate) {
    case 4: /* NextCal_end_ */ {
        { if (Sequence[SeqIndex] == 20) VSET_7_(2);
        		  else VSET_7_(3);
        	   }
      }
      break;
    case 3: /* Air_pos_1_ */ {
        { switch_ssv( CALSSVADD, Sequence[SeqIndex] );
        		if ( ++SeqIndex >= NUMCALSEQ ) SeqIndex = 0;
        	}
      }
      break;
    case 2: /* Cal_pos_1_ */ {
        { switch_ssv( CALSSVADD, Sequence[SeqIndex] );
        		if ( ++SeqIndex >= NUMCALSEQ ) SeqIndex = 0;
        	}
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
  }
}
static void VSET_9_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* Shutdown */ {
        {
          tma_init_state( 3, Shutdown_cmds_, "Shutdown" ); VSET_13_(1);
        }
      }
      break;
    case 1: /* ShutdownComputer */ {
        {
          tma_init_state( 3, ShutdownComputer_cmds_, "ShutdownComputer" ); VSET_13_(1);
        }
      }
      break;
  }
}
static void VSET_8_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* SetECDsCold */ {
        {
          tma_init_state( 2, SetECDsCold_cmds_, "SetECDsCold" ); VSET_12_(1);
        }
      }
      break;
    case 1: /* CheckCarrier */ {
        {
          tma_init_state( 2, CheckCarrier_cmds_, "CheckCarrier" ); VSET_12_(1);
        }
      }
      break;
  }
}
static void VSET_7_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 1: /* CalSSV */
      V10 |= 0x2;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 4: /* NextCal */ {
        {
          tma_init_state( 1, NextCal_cmds_, "NextCal" ); VSET_11_(1);
        }
      }
      break;
    case 3: /* Air_pos */ {
        {
          tma_init_state( 1, Air_pos_cmds_, "Air_pos" ); VSET_11_(1);
        }
      }
      break;
    case 2: /* Cal_pos */ {
        {
          tma_init_state( 1, Cal_pos_cmds_, "Cal_pos" ); VSET_11_(1);
        }
      }
      break;
    case 1: /* CalSSV */ {
        V10 &= ~0x2;
        {
          tma_init_state( 1, CalSSV_cmds_, "CalSSV" ); VSET_11_(1);
        }if (!(V10)) {
          { VSET_7_(4);
          	}
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
    case 1: /* initialize */ {
        {
          tma_init_state( 0, initialize_cmds_, "initialize" ); VSET_10_(1);
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
    case 3: /* Injection */
      V1 |= 0x1;
      break;
    case 2: /* Injecting1 */ {
        V10 |= 0x1;
        V3 |= 0x1;
      }
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 3: /* Injection */
      V1 &= ~0x1;
      break;
    case 2: /* Injecting1 */ {
        V10 &= ~0x1;
        V3 &= ~0x1;
        if (!(V10)) {
          { VSET_7_(4);
          	}
        }
      }
      break;
  }
}
static void tminitfunc(void) {VSET_0_(1);VSET_1_(1);VSET_2_(1);VSET_3_(1);VSET_4_(1);VSET_5_(1);VSET_6_(1);VSET_7_(1);VSET_8_(1);VSET_9_(1);VSET_10_(1);VSET_11_(1);VSET_12_(1);VSET_13_(1);
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
}

static void BF8_0(void) {
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
    long int it;
    int subcase;
  
    it = itime();
    ci_settime( it );
    while ( subcase = tma_process( it ) ) {
  	switch (subcase) {
  	  case -1:
  	  case 0: break;
  	  case 1: VSET_6_(1); break;
  	  case 2: VSET_7_(1); break;
  	  case 3: VSET_7_(2); break;
  	  case 4: VSET_7_(3); break;
  	  case 5: VSET_7_(4); break;
  	  case 6: VSET_8_(1); break;
  	  case 7: VSET_8_(2); break;
  	  case 8: VSET_9_(1); break;
  	  case 9: VSET_9_(2); break;
  	  case 10: VSET_10_(1); break;
  	  case 11: VSET_11_(1); break;
  	  case 12: VSET_11_(2); break;
  	  case 13: VSET_11_(3); break;
  	  case 14: VSET_11_(4); break;
  	  case 15: VSET_12_(1); break;
  	  case 16: VSET_12_(2); break;
  	  case 17: VSET_13_(1); break;
  	  case 18: VSET_13_(2); break;
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

static void BF8_1(void) {
  memcpy(&tdlrec, home->U26.U28, 2);
  tdl_longH2O = home->U22.tdl_longH2O;
  V8 &= ~0x1;
  EF1_0();
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
}

static void BF16_2(void) {
  CHROMtime = home->U1.CHROMtime;
  V0 &= ~0x1;
  EF8_2();
}

static void BF16_3(void) {
  o3x = home->U22.o3x;
  o3xpres = home->U17.o3xpres;
  V6 &= ~0x1;
  EF1_0();
}

static void BF16_4(void) {
  EF1_0();
  home->U0.CUMSEC++;
}

static void BF16_6(void) {
  o3best = home->U17.o3best;
  V5 &= ~0x1;
  EF1_0();
  home->U15.O3count++;
  {if (!(V4)) {
    { VSET_3_(1); }
  }
  
  	if ( home->U15.O3count >= 60*60/10 ) { 
  		home->U15.O3count = 0; VSET_3_(2);
  	}
  }
  if (!(V6)) {
    {
    	home->U15.o3xbest = 0.927*((o3x-3.0) * o3xpres)/(o3xpres*1.00095 + 3.23) ;
    }
  }
}

static void BF16_11(void) {
  EF1_0();
  if (!(V11)) {
    { if ( (_CVT_0(home->U7.presL_N2) < N2fail) && (_CVT_0(home->U7.presL_N2) > 0) ) {
    			msg( -2, "** (%d) LOW N2 Pressure (presL_N2 = %f)", N2lowCount,_CVT_0(home->U7.presL_N2) );
    			if ( ++N2lowCount >= MAXN2LOWCNTS ) VSET_8_(2); 
    		  }
    		  else if (_CVT_0(home->U7.presL_N2) >= N2fail ) 
    			N2lowCount = 0; 
    		}
  }
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
}

static void BF16_13(void) {
  EF1_0();
  { ITXFileNum = home->U0.CurrInj * 1000 + home->U1.CurrFile;
  }
}

static void BF16_14(void) {
  EF1_0();
  if (!(V12)) {
    { if ( home->U11.InitShutdown == FALSE ) VSET_9_(2); }
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
}

static void BF128_15(void) {
  o3pres = home->U19.o3pres;
  V5 &= ~0x2;
  EF16_15();
}

static void BF128_31(void) {
  EF16_15();
  if (!(V5)) {
    {
    	o3best = (home->U15.o3 * o3pres)/(o3pres*.9996 + 7.9);
    }
  }
}

static void (*efuncs[128])() = {
  BF128_0,
  BF8_1,
  BF16_2,
  BF16_3,
  BF16_4,
  EF1_0,
  BF16_6,
  EF1_0,
  BF8_0,
  BF8_1,
  EF8_2,
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
  EF1_0,
  BF16_6,
  EF1_0,
  BF8_0,
  BF8_1,
  EF8_2,
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
  EF1_0,
  BF16_6,
  EF1_0,
  BF8_0,
  BF8_1,
  EF8_2,
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
  EF1_0,
  BF16_6,
  EF1_0,
  BF8_0,
  BF8_1,
  EF8_2,
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
  EF1_0,
  BF16_6,
  EF1_0,
  BF8_0,
  BF8_1,
  EF8_2,
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
  EF1_0,
  BF16_6,
  EF1_0,
  BF8_0,
  BF8_1,
  EF8_2,
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
  EF1_0,
  BF16_6,
  EF1_0,
  BF8_0,
  BF8_1,
  EF8_2,
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
  EF1_0,
  BF16_6,
  EF1_0,
  BF8_0,
  BF8_1,
  EF8_2,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
  EF16_15
};

static void IVF8_1(void) {
  V8 |= 0x1;
}
static void IVF16_2(void) {
  V0 |= 0x1;
}
static void IVF16_3(void) {
  V6 |= 0x1;
}
static void IVF16_6(void) {
  V5 |= 0x1;
}
static void IVF128_15(void) {
  V5 |= 0x2;
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
