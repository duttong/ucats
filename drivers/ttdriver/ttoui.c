/* OUI output from the following packages:
   msghdr
   msghdr_init
   msg
   ttdriver
   nl_error_init
*/
char *opt_string = "h:e:o:c:lvsyq";
#include "oui.h"
#include "msg.h"
#include <stdlib.h>
#include "ttdriver.h"
#include "nortlib.h"
  void ttdrv_init( int argc, char **argv ) {
	int optltr;
	optind = 0;
	opterr = 0;
	while ((optltr = getopt(argc, argv, opt_string)) != -1) {
	  if (optltr == 'q') {
		tt_shutdown();
		exit( 0 );
	  }
	}
  }
  int (*nl_error)(int level, char *s, ...) = msg;

void oui_init_options(int argc, char **argv) {
  char *msg_hdr;
  msg_hdr = "TTDrv";
  msg_init_options(msg_hdr, argc, argv);
  ttdrv_init( argc, argv );
}

#ifdef __USAGE
%C	[options]
	-c <node>[,<attached name>] send msgs to another task; default: memo
	-e <error filename>
	-h <msg header>
	-l add a level of debug messages
	-o <device>[,<row>,<col>,<width>,<pass attr>,<warn>,<fail>,<debug>]
	-q Ask resident ttdriver to terminate
	-s no message sounds
	-v disable verbose to stderr
	-y disable system error message concatenation to messages
#endif
