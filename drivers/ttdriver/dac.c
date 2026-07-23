/* DAC Functions: dac.c */
#include <conio.h>
#include <i86.h>
#include "ttdriver.h"
#include "ttintern.h"

static unsigned short saved_outputs[ TT_N_DAC_CHANS ];

/* D/A output:
  CFG  <- 0  All ports for output, even Ch!
  CTRL <- 4
  ADDR <- channel address
  DATA <- LSB
  CTRL <- 5   latches LSB
  DATA <- MSN
  CTRL <- 6   latches MSN
  CTRL <- 7
  ADDR <- output address
  CTRL <- 3
  CTRL <- 7
  ADDR <- dummy address
*/

unsigned int outpDelay( int port, int value ) {
	int outpv;
	long inc;
	outpv =	outp( port, value );

	for(inc=0;inc<1000;inc++) {}

	return outpv;
}

unsigned short tti_dac_out( unsigned short channel, unsigned short value ) {
unsigned short offset,chan;
  chan=channel-(channel/16)*16;
  offset=(channel/16)*0x10;
  if ( channel >= TT_N_DAC_CHANS ) return 0xFFFF;
  outpDelay( TT_CFG_PORT, 0x80 ); /* All ports for output, even Ch! */
  outpDelay( TT_CTRL_PORT, 4 );
  outpDelay( TT_ADDR_PORT, chan + TT_DAC_BASE+offset );
  outpDelay( TT_DATA_PORT, value & 0xFF );         /* LSB */
  outpDelay( TT_CTRL_PORT, 5 );
  outpDelay( TT_DATA_PORT, ( value >> 8 ) & 0xF ); /* MSN */
  outpDelay( TT_CTRL_PORT, 6 );
  outpDelay( TT_CTRL_PORT, 7 );
  outpDelay( TT_ADDR_PORT, TT_DAC_OUTPUTS +offset);
  outpDelay( TT_CTRL_PORT, 3 );
  outpDelay( TT_CTRL_PORT, 7 );
  outpDelay( TT_ADDR_PORT, TT_DUMMY_ADDR );
  saved_outputs[ channel ] = value & 0xFFF;
  return 0;
}

/* This returns the last value output. It's only software, but
   it might be convenient!
*/
unsigned short tti_dac_in( unsigned short channel ) {
  if ( channel >= TT_N_DAC_CHANS ) return 0xFFFF;
  return saved_outputs[ channel ];
}

/* If safe != 0, sets hardware to use the SAFE potentiometer.
   If safe == 0, hardware enables the value of the DAC.
   
   CFG  <- 0x10  Ain, Cout, Bout
   CTRL <- 7
   ADDR <- Output Address
       safe:          unsafe:
   CTRL <- 0x1F    CTRL <- 0x0F
   CTRL <- 0x17
       both:
   CTRL <- 7
   ADDR <- dummy address
*/
unsigned short tti_dac_enbl( unsigned short safe ) {

  outpDelay( TT_CFG_PORT, 0x90 ); /* Ain, Cout, Bout */
  outpDelay( TT_CTRL_PORT, 7 );
  outpDelay( TT_ADDR_PORT, TT_DAC_OUTPUTS );
  if ( safe != 0 ) {
	outpDelay( TT_CTRL_PORT, 0x1F );
	outpDelay( TT_CTRL_PORT, 0x17 );
  } else outpDelay( TT_CTRL_PORT, 0x0F );
  outpDelay( TT_CTRL_PORT, 7 );
  outpDelay( TT_ADDR_PORT, TT_DUMMY_ADDR );

  outpDelay( TT_CFG_PORT, 0x90 ); /* Ain, Cout, Bout */
  outpDelay( TT_CTRL_PORT, 7 );
  outpDelay( TT_ADDR_PORT, TT_DAC_OUTPUTS+0x10 );
  if ( safe != 0 ) {
	outpDelay( TT_CTRL_PORT, 0x1F );
	outpDelay( TT_CTRL_PORT, 0x17 );
  } else outpDelay( TT_CTRL_PORT, 0x0F );
  outpDelay( TT_CTRL_PORT, 7 );
  outpDelay( TT_ADDR_PORT, TT_DUMMY_ADDR );
 

  outpDelay( TT_CFG_PORT, 0x90 ); /* Ain, Cout, Bout */
  outpDelay( TT_CTRL_PORT, 7 );
  outpDelay( TT_ADDR_PORT, TT_DAC_OUTPUTS +0x20);
  if ( safe != 0 ) {
	outpDelay( TT_CTRL_PORT, 0x1F );
	outpDelay( TT_CTRL_PORT, 0x17 );
  } else outpDelay( TT_CTRL_PORT, 0x0F );
  outpDelay( TT_CTRL_PORT, 7 );
  outpDelay( TT_ADDR_PORT, TT_DUMMY_ADDR );
 

  outpDelay( TT_CFG_PORT, 0x90 ); /* Ain, Cout, Bout */
  outpDelay( TT_CTRL_PORT, 7 );
  outpDelay( TT_ADDR_PORT, TT_DAC_OUTPUTS +0x30);
  if ( safe != 0 ) {
	outpDelay( TT_CTRL_PORT, 0x1F );
	outpDelay( TT_CTRL_PORT, 0x17 );
  } else outpDelay( TT_CTRL_PORT, 0x0F );
  outpDelay( TT_CTRL_PORT, 7 );
  outpDelay( TT_ADDR_PORT, TT_DUMMY_ADDR );
 
 


 return 0;
}

