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
#define			NUMSECSXAXIS	 140

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
int Omega485[10];

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
#include <sys/types.h>
#include "o3ser.h"
pid_t o3_proxy = 0;

O3struct ozone;



 typedef float o3float;
 typedef long o3lint;
 typedef short o3int;
#include <sys/types.h>
#include "vaisala.h"
pid_t vaisala_proxy = 0;

RHstruct vai;



 typedef float vaifloat;
#include <sys/types.h>
#include "maycomm.h"
pid_t maycomm_proxy = 0;

TDLstruct tdl;



 typedef float tdlfloat;
 typedef float tdlfloas;
 typedef short tdlint6; /* edf2ext.awk reading elec.edf */
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

  sps_ptr elec1e;
  void initialize(void) {
	{
	  char *s;
	  s = getenv("EXT_DELTA");
	  if (s != NULL) {
		ext_delta=atof(s);
		msg(MSG, "Using Time Delta of %lf", ext_delta);
	  }
	}
	elec1e = edf_ss_open( "elec1e", 6 );
	ss_set_column(elec1e, 0, "%14.11lt", "Time");
	ss_set_column(elec1e, 1, "%8.0f", "GCstate");
	ss_set_column(elec1e, 2, "%8.0f", "SLoopIN");
	ss_set_column(elec1e, 3, "%8.0f", "SLoopOUT");
	ss_set_column(elec1e, 4, "%12.1f", "temp_SL1");
	ss_set_column(elec1e, 5, "%12.1f", "pres_SL");
  }
  void terminate(void) {
	ss_close(elec1e);
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
unsigned char V5 = 0x1;
o3float o3;
o3float o3temp;
o3float o3pres;
tdlfloas tdlP;
tdlint6  tdlsAmp;
union {
  struct {
    UINT MFCtr;
    GC_Ctr GC_Ctr_CH1;
    GC_Ctr GC_Ctr_CH2;
    SCCM flow_M1;
    SCCMsp flow_M1_sp;
    UINT CurrFile;
    UINT CurrInj;
    OmegaT CH2_ECD;
    UCHAR GCstate;
    UINT Synch;
  } U0;
  struct {
    char U2[10];
    SCCMsp flow_BF1_sp;
    PSI pres_BP1;
    PSIsp pres_BP1_sp;
    OmegaT CH2_Col;
    char U3[1];
  } U1;
  struct {
    char U5[10];
    SCCMsp flow_M2_sp;
    MBAR pres_SL;
    CELS temp_gasB_N;
    OmegaT CH2_Post;
    char U6[1];
  } U4;
  struct {
    char U8[10];
    MBAR pres_PUMP;
    CELS temp_SL1;
    SCCM flow_M2;
    OmegaT CH1_ECD;
    char U9[1];
  } U7;
  struct {
    char U11[10];
    PSIsp pres_BP2_sp;
    CELS temp_gasB_C;
    SCCMsp flow_BF2_sp;
    OmegaT CH1_Col;
    char U12[1];
  } U10;
  struct {
    char U14[10];
    CELS temp_pump;
    SCCMsl flow_SL;
    CELS temp_SL2;
    OmegaTsp CH2_ECD_Sp;
    char U15[1];
  } U13;
  struct {
    char U17[10];
    CELS temp_amb;
    SCCM flow_BF2;
    MBAR pres_extern;
    OmegaTsp CH2_Col_Sp;
    char U18[1];
  } U16;
  struct {
    char U20[10];
    PSIL presL_cal;
    MBAR pres_ECD2;
    PSIL presL_N2;
    OmegaTsp CH2_Post_Sp;
    char U21[1];
  } U19;
  struct {
    char U23[10];
    VOLTS28 volt_28;
    VOLTS512 volt_1234;
    PSIH presH_123;
    OmegaTsp CH1_ECD_Sp;
    char U24[1];
  } U22;
  struct {
    char U26[10];
    Bit_Cl_Op N2_IN;
    Bit_On_Off O3PwSwitch;
    PSIL presL_dope;
    VOLTSPM volt_15;
    OmegaTsp CH1_Col_Sp;
    char U27[1];
  } U25;
  struct {
    char U29[10];
    valvT valv_calSSV;
    valvetext valv_CH2;
    VOLTS512 volt_5;
    Bit_Op_Cl SLoopIN;
    ULONG CHROMtime;
    char U30[1];
  } U28;
  struct {
    char U32[10];
    ULONG O3count;
    Bit_On_Off PowerSwitch;
    ULONG CUMSEC;
    SCCM flow_BF1;
    char U33[1];
  } U31;
  struct {
    char U35[10];
    ULONG vaisX;
    valvetext valv_CH1;
    Bit_On_Off PumpSwitch;
    ULONG maycX;
    Bit_HI_LO InitShutdown;
    char U36[1];
  } U34;
  struct {
    char U38[10];
    char U39[2];
    vaifloat vaiT;
    vaifloat vaiRH;
    Bit_Cl_Op SLoopOUT;
    Bit_Air_Cal ssv;
    char U40[1];
  } U37;
  struct {
    char U42[10];
    char U43[1];
    tdlfloat tdllH2O;
    tdlfloat tdlsH2O;
    tdlfloas tdlT;
    char U44[2];
  } U41;
  struct {
    char U46[10];
    tdlint6  tdllZer;
    tdlint6  tdllPos;
    tdlint6  tdllPow;
    tdlint6  tdllAmp;
    tdlint6  tdlsZer;
    tdlint6  tdlsPos;
    tdlint6  tdlsPow;
    char U47[1];
  } U45;
  struct {
    char U49[24];
    char U50[1];
  } U48;
  struct {
    char U52[24];
    char U53[1];
  } U51;
  struct {
    char U55[24];
    char U56[1];
  } U54;
  struct {
    char U58[24];
    char U59[1];
  } U57;
  struct {
    char U61[24];
    char U62[1];
  } U60;
  struct {
    char U64[24];
    char U65[1];
  } U63;
  struct {
    char U67[24];
    char U68[1];
  } U66;
  struct {
    char U70[24];
    char U71[1];
  } U69;
  struct {
    char U73[24];
    char U74[1];
  } U72;
  struct {
    char U76[24];
    char U77[1];
  } U75;
  struct {
    char U79[24];
    char U80[1];
  } U78;
} *home;
/* doub_cvt for CELS -> TEMP */
double _CVT_0( CELS x ) {
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
/* doub_cvt for MBAR -> PRESS */
double _CVT_1( MBAR x ) {
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
static void VSET_4_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 2: /* MaycommTog */
      V5 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* MaycommTog */
      V5 &= ~0x1;
      break;
  }
}
static void VSET_3_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 2: /* VaisalaTog */
      V4 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 2: /* VaisalaTog */
      V4 &= ~0x1;
      break;
  }
}
static void VSET_2_(unsigned short newstate) {
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
static void VSET_1_(unsigned short newstate) {
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
static void tminitfunc(void) {VSET_0_(1);VSET_1_(1);VSET_2_(1);VSET_3_(1);VSET_4_(1);
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

static void BF16_0(void) {
  memcpy(&tdlsAmp, home->U78.U80, 1);
  EF1_0();
  {
  	if (adr_proxy != 0)  Trigger ( adr_proxy );
  }
  {
  	if (ECDresp_proxy != 0) Trigger ( ECDresp_proxy );
  }
  {if (!(V1)) {
    { VSET_1_(1);
    	}
  }if (!(V2)) {
    V2 |= 0x1;
    { VSET_1_(2);
    		ecdCH1x = 0.0;
    		ecdCH2x = 0.0;
    	}
  }
  
  	if ( ecdCH2x > NUMSECSXAXIS ) { VSET_1_(2);
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
  	if (vaisala_proxy != 0)  Trigger ( vaisala_proxy );
  }
  {
  	if (maycomm_proxy != 0)  Trigger ( maycomm_proxy );
  }
}

static void BF160_0(void) {
  BF16_0();
  {
  	if (o3_proxy != 0)  Trigger ( o3_proxy );
  }
}

static void BF16_1(void) {
  memcpy(&tdlP, home->U41.U44, 2);
  memcpy(((char*)(&tdlsAmp))+1, home->U41.U43, 1);
  EF1_0();
}

static void BF16_2(void) {
  memcpy(((char*)(&tdlP))+2, home->U37.U39, 2);
  EF1_0();
  {
    	if ( home->U0.GCstate == 0 ) VSET_0_(1);
  	else if ( home->U0.GCstate == 1 ) VSET_0_(2);
  	else if ( home->U0.GCstate == 2 ) VSET_0_(3);
  	else if ( home->U0.GCstate == 3 ) VSET_0_(4);
  }
  {if (!(V0)) {
    { home->U28.CHROMtime++; InjectingInc = 0; }
  }
    if ((home->U0.GCstate == 1) || (home->U0.GCstate == 3)) { 
  	if (InjectingInc == 0 ) {
  		home->U28.CHROMtime = 1; 
  		InjectingInc = 1;
  	}
  	else home->U28.CHROMtime += 1;
    }
  }
  {
    ss_insert_value(elec1e, dtime()+ext_delta, 0);
    ss_set(elec1e, 1, home->U0.GCstate);
  }
}

static void EF16_3(void) {
  EF1_0();
  home->U31.CUMSEC++;
}

static void BF160_3(void) {
  memcpy(&o3pres, home->U34.U36, 1);
  EF16_3();
}

static void BF160_4(void) {
  memcpy(((char*)(&o3pres))+1, home->U31.U33, 1);
  EF1_0();
}

static void BF160_5(void) {
  memcpy(((char*)(&o3pres))+2, home->U28.U30, 1);
  EF1_0();
}

static void EF16_6(void) {
  EF1_0();
  home->U34.maycX++;
  {if (!(V5)) {
    { VSET_4_(1); }
  }
  
  	if ( home->U34.maycX >= 120 ) { 
  		home->U34.maycX = 0; VSET_4_(2);
  	}
  }
}

static void BF160_6(void) {
  memcpy(((char*)(&o3pres))+3, home->U25.U27, 1);
  EF16_6();
}

static void EF16_7(void) {
  EF1_0();
  home->U31.O3count++;
  {if (!(V3)) {
    { VSET_2_(1); }
  }
  
  	
  	if ( home->U31.O3count >= 60*60/10 ) { 
  		home->U31.O3count = 0; VSET_2_(2);
  	}
  }
}

static void BF160_7(void) {
  memcpy(&o3temp, home->U22.U24, 1);
  EF16_7();
}

static void BF160_8(void) {
  memcpy(((char*)(&o3temp))+1, home->U19.U21, 1);
  EF1_0();
}

static void EF16_9(void) {
  EF1_0();
  {
    ss_insert_value(elec1e, dtime()+ext_delta, 0);
    ss_set(elec1e, 5, _CVT_1(home->U4.pres_SL));
  }
}

static void BF160_9(void) {
  memcpy(((char*)(&o3temp))+2, home->U16.U18, 1);
  EF16_9();
}

static void BF160_10(void) {
  memcpy(((char*)(&o3temp))+3, home->U13.U15, 1);
  EF1_0();
}

static void BF160_11(void) {
  memcpy(&o3, home->U10.U12, 1);
  EF1_0();
}

static void EF16_12(void) {
  EF1_0();
  {
    ss_insert_value(elec1e, dtime()+ext_delta, 0);
    ss_set(elec1e, 4, _CVT_0(home->U7.temp_SL1));
  }
}

static void BF160_12(void) {
  memcpy(((char*)(&o3))+1, home->U7.U9, 1);
  EF16_12();
}

static void EF16_13(void) {
  EF1_0();
  home->U34.vaisX++;
  {if (!(V4)) {
    { VSET_3_(1); }
  }
  
  	if ( home->U34.vaisX >= 120 ) { 
  		home->U34.vaisX = 0; VSET_3_(2);
  	}
  }
}

static void BF160_13(void) {
  memcpy(((char*)(&o3))+2, home->U4.U6, 1);
  EF16_13();
}

static void EF16_14(void) {
  EF1_0();
  { ITXFileNum = home->U0.CurrInj * 1000 + home->U0.CurrFile;
  }
}

static void BF160_14(void) {
  memcpy(((char*)(&o3))+3, home->U1.U3, 1);
  EF16_14();
}

static void BF16_15(void) {
  EF1_0();
  {
    ss_insert_value(elec1e, dtime()+ext_delta, 0);
    ss_set(elec1e, 2, home->U28.SLoopIN);
  }
  {
    ss_insert_value(elec1e, dtime()+ext_delta, 0);
    ss_set(elec1e, 3, home->U37.SLoopOUT);
  }
}

static void (*efuncs[160])() = {
  BF160_0,
  BF16_1,
  BF16_2,
  BF160_3,
  BF160_4,
  BF160_5,
  BF160_6,
  BF160_7,
  BF160_8,
  BF160_9,
  BF160_10,
  BF160_11,
  BF160_12,
  BF160_13,
  BF160_14,
  BF16_15,
  BF16_0,
  BF16_1,
  BF16_2,
  EF16_3,
  EF1_0,
  EF1_0,
  EF16_6,
  EF16_7,
  EF1_0,
  EF16_9,
  EF1_0,
  EF1_0,
  EF16_12,
  EF16_13,
  EF16_14,
  BF16_15,
  BF16_0,
  BF16_1,
  BF16_2,
  EF16_3,
  EF1_0,
  EF1_0,
  EF16_6,
  EF16_7,
  EF1_0,
  EF16_9,
  EF1_0,
  EF1_0,
  EF16_12,
  EF16_13,
  EF16_14,
  BF16_15,
  BF16_0,
  BF16_1,
  BF16_2,
  EF16_3,
  EF1_0,
  EF1_0,
  EF16_6,
  EF16_7,
  EF1_0,
  EF16_9,
  EF1_0,
  EF1_0,
  EF16_12,
  EF16_13,
  EF16_14,
  BF16_15,
  BF16_0,
  BF16_1,
  BF16_2,
  EF16_3,
  EF1_0,
  EF1_0,
  EF16_6,
  EF16_7,
  EF1_0,
  EF16_9,
  EF1_0,
  EF1_0,
  EF16_12,
  EF16_13,
  EF16_14,
  BF16_15,
  BF16_0,
  BF16_1,
  BF16_2,
  EF16_3,
  EF1_0,
  EF1_0,
  EF16_6,
  EF16_7,
  EF1_0,
  EF16_9,
  EF1_0,
  EF1_0,
  EF16_12,
  EF16_13,
  EF16_14,
  BF16_15,
  BF16_0,
  BF16_1,
  BF16_2,
  EF16_3,
  EF1_0,
  EF1_0,
  EF16_6,
  EF16_7,
  EF1_0,
  EF16_9,
  EF1_0,
  EF1_0,
  EF16_12,
  EF16_13,
  EF16_14,
  BF16_15,
  BF16_0,
  BF16_1,
  BF16_2,
  EF16_3,
  EF1_0,
  EF1_0,
  EF16_6,
  EF16_7,
  EF1_0,
  EF16_9,
  EF1_0,
  EF1_0,
  EF16_12,
  EF16_13,
  EF16_14,
  BF16_15,
  BF16_0,
  BF16_1,
  BF16_2,
  EF16_3,
  EF1_0,
  EF1_0,
  EF16_6,
  EF16_7,
  EF1_0,
  EF16_9,
  EF1_0,
  EF1_0,
  EF16_12,
  EF16_13,
  EF16_14,
  BF16_15,
  BF16_0,
  BF16_1,
  BF16_2,
  EF16_3,
  EF1_0,
  EF1_0,
  EF16_6,
  EF16_7,
  EF1_0,
  EF16_9,
  EF1_0,
  EF1_0,
  EF16_12,
  EF16_13,
  EF16_14,
  BF16_15
};

#define TRN 160
#define TRD 1
#define LOWLIM (-1440)
#define HIGHLIM (1440)
#define NBROW 27
#define NROWMINF 1
#define NSECSPER 1
#define NROWSPER 16
#define ROLLOVER 65440
#define SYNCHVAL 0xABB4
#define NROWMAJF 160
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
  27, /* NBMINF */
  27, /* NBROW */
  160, /* NROWSMAJF */
  1, /* NSECSPER */
  16, /* NROWSPER */
  0, 1, /* MFC lsb col, msb col */
  0xABB4, /* Synch Value */
  0 /* not inverted */
};
