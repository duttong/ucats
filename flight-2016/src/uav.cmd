%{
#include <i86.h>
#include "globmsg.h"
#include "nortlib.h"
#include "soldrv.h"
#include "addresses.h"
#include "valves.h"
#include "commands.h"

#define IOMODE_INIT 	 27

%}

&start
	: &commands Quit     	* { 

		switch_gsv( CH1gsvADD, 2 ); delay(100);
		switch_gsv( CH2gsvADD, 2 ); delay(100);

		// sample air
		ADRdigSet( 0, 5, 0 );

		// sample in and out sols to closed
		ADRdigSet( 0, 6, 1 ); 
		ADRdigSet( 0, 7, 0 );
		
		// Turn pump off
		ADRdigSet( 0, 2, 0 );

		shutdownservers();
		delay(100);

		cis_terminate();
	
		send_dascmd(DCT_QUIT, DCV_QUIT, 1);
		delay(2000);
	}

	: &commands Shutdown	* { 

		shutdownservers();
		delay(100);

		//cis_terminate();
	
		send_dascmd(DCT_QUIT, DCV_QUIT, 1);
		delay(3000);
		system("/usr/local/bin/shutdn");
	}
	: &commands &&Exit
	;
&&Exit
	: Exit * {

		//cis_terminate();
		send_dascmd(DCT_QUIT, DCV_QUIT, 1);
		delay(2000); 
	}
	;
&commands
	:
	: &commands &command
	;
&command
	: *
	: Log %s ( Enter String to Log to Memo ) * {}
	: Telemetry &tm_cmd
	: &&local
	;
&tm_cmd
	: Start * { send_dascmd(DCT_TM, DCV_TM_START, 1); }
	: Logging Suspend * { send_dascmd(DCT_TM, DCV_TM_SUSLOG, 1); }
	: Logging Resume * { send_dascmd(DCT_TM, DCV_TM_RESLOG, 1); }
	;
&&local
	: IOMODE %d (Backspace=1 Space=2 Always=4 Word=8 WordSkip=16) *
		{ iomode = $2; }
	;
&command

	: Mode &ModeSet
#	: Flight Start { ADRdigSet( 0, 3, 1 );  }
#	: Flight Quit { ADRdigSet( 0, 3, 0 ); }

#	: Power &On { ADRdigSet( 0, 1, $2 ); }
	: Pump &On { ADRdigSet( 0, 2, $2 ); }

#	: Ozone &On { ADRdigSet( 0, 3, $2 ); }

	: Nitrogen &Open { ADRdigSet( 0, 4, $2 ); }

	: sample air { ADRdigSet( 0, 5, 0 ); }
	: sample cal { ADRdigSet( 0, 5, 1 ); }

	: solenoid samp In &Open2 { ADRdigSet( 0, 6, $4 ); }
	: solenoid samp Out &Open { ADRdigSet( 0, 7, $4 ); }
	: solenoid samp both Open {	ADRdigSet( 0, 6, 0 ); ADRdigSet( 0, 7, 1 ); } 
	: solenoid samp both Close { ADRdigSet( 0, 6, 1 ); ADRdigSet( 0, 7, 0 ); } 

	: gsv &GSVADDRESS * { }
	: ssv goto position %d { switch_ssv( CALSSVADD, $4 ); } 

	: elec reset &elecnum * { elec_reset( $3 ); }
	: elec bias &elecnum &bias_change * { elec_bias( $3, $4 ); }
	: elec bias NULL * { }

	: flow main channel 1 &FlowSetpoint { SetFlow( 1, 0, $5 ); }
	: flow main channel 2 &FlowSetpoint { SetFlow( 2, 0, $5 ); }
	: flow backflush channel 1 &FlowSetpoint { SetFlow( 1, 1, $5 ); }
	: flow backflush channel 2 &FlowSetpoint { SetFlow( 2, 1, $5 ); }

	: press channel 1 setpoint &PressSetpoint { SetPress( 0, 0, $5 ); }
	: press channel 2 setpoint &PressSetpoint { SetPress( 0, 1, $5 ); }
	
	: Omega change SP1 &OMEGAaddress %f *  { setOmegaSP1( $4, $5 ); }
	: Omega change SP1 DoNothing * {  }
	: Omega reset &OMEGAaddress *  { OmegaReset( $3 ); }

	: adr2000 &ADRBOARD set DIG &ADRCHAN to &On * { ADRdigSet( $2, $5, $7 ); }
	: adr2000 &ADRBOARD set DtoA &ADRDACCHAN to &ADRvolts * { ADRdtoaSet( $2, $5, $7 ); }
	;

&ModeSET 
	: GC &GCModeName * { send_dascmd( DCT_SOLDRV_A, $2, -1 ); }
	;

&GCModeName <unsigned short>
	: Safe  { $0 = 0; }
	: Init  { $0 = 1; }
	: Run   { $0 = 2; }
	: Lab 70s { $0 = 3; }
	: Lab 140s { $0 = 4; }
	: Lab 280s { $0 = 6; }
	: Cal   { $0 = 7; }
	: Shutdown { $0 = 9; }
	;

&elecnum <unsigned short>
	: 1 { $0 = (CH1elecADD); }
	: 2 { $0 = (CH2elecADD); }
	;

&ADRBOARD <unsigned short>
	: board 0 { $0 = 0; }
	: board 1 { $0 = 1; }
	: board 2 { $0 = 2; }
	;

&ADRCHAN <unsigned short>
	: 0 { $0 = 0; }
	: 1 { $0 = 1; }
	: 2 { $0 = 2; }
	: 3 { $0 = 3; }
	: 4 { $0 = 4; }
	: 5 { $0 = 5; }
	: 6 { $0 = 6; }
	: 7 { $0 = 7; }
	;

&ADRDACCHAN <unsigned short>
	: 0 { $0 = 0; }
	: 1 { $0 = 1; }
	;

&ADRvolts <float>
	: %f (0.0 to 5.0 volts) { 
		if ($1 < 0) 
			$0 = 0.0;
		else if ($1 > 5.0) 
			$0 = 5.0;
		else
			$0 = $1;
	}
	;

&OMEGAaddress <unsigned short>
	: CH2 ECD  { $0 = 1; }
	: CH2 Col  { $0 = 2; }
	: CH2 Post { $0 = 3; }
	: CH1 ECD  { $0 = 4; }
	: CH1 Col  { $0 = 5; }
	: H2O Pelt  { $0 = 6; }
	;

&bias_change <unsigned short>
	: %d (Enter bias Value 0-255)
	  { if ($1 < 0) $0 = 0;
		else if ($1 > 255) $0 = 255;
		else $0 = $1;
	  }
	;

&Open <unsigned short>
	: Open { $0 = 1; }
	: Close { $0 = 0; }
	;

&Open2 <unsigned short>
	: Open { $0 = 0; }
	: Close { $0 = 1; }
	;

&On <unsigned short>
	: On  { $0 = 1; }
	: Off { $0 = 0; }
	;

&FlowSetpoint <float>
	: %f (0 to 200 cc/min) { 
		if ($1 < 0) 
			$0 = 0.0;
		else if ($1 > 200) 
			$0 = 200;
		else
			$0 = $1;
	}
	;

&PressSetpoint <float>
	: %f (0 to 2000 mbar) { 
		if ($1 < 0) 
			$0 = 0.0;
		else if ($1 > 2000) 
			$0 = 2000;
		else
			$0 = $1;
	}
	;

&GSVADDRESS <unsigned short>
	: channel 1 &GSVVALVEPOS { switch_gsv( CH1gsvADD, $3 ); }
	: channel 2 &GSVVALVEPOS { switch_gsv( CH2gsvADD, $3 ); }
	;
&GSVVALVEPOS <unsigned short>
	: Inject { $0 = 1; }
	: Load { $0 = 2; }
	;
&GSVVALVEPOS_Inv <unsigned short>
	: Inject { $0 = 2; }
	: Load { $0 = 1; }
	;
