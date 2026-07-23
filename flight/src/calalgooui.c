/* OUI output from the following packages:
   msghdr
   msghdr_init
   msg
   nl_cons
   tma
   dc
   nl_error_init
   client
*/
char *opt_string = "h:e:o:c:lvsyA:a:gr:mb:i:xC:p";
#include "oui.h"
#include "msg.h"
#include <stdlib.h>
#include "nl_cons.h"
#include "nortlib.h"
#include "tma.h"
#include "dbr.h"
  int (*nl_error)(int level, char *s, ...) = msg;

void oui_init_options(int argc, char **argv) {
  char *msg_hdr;
  msg_hdr = "TMA";
  msg_init_options(msg_hdr, argc, argv);
  Con_init_options(argc, argv);
  atexit(nlcon_close);
  tma_init_options( argc, argv );
  DC_init_options(argc, argv);
  cic_options(argc, argv, msg_hdr);
}

#ifdef __USAGE
%C	[options]
	-A <console> Open console as screen 0 instead of STDOUT
	-a <console> Open console as screen 1, etc.
	-b <node> become a star client of the buffer on given node
	-C <node> send commands to server on specified node
	-c <node>[,<attached name>] send msgs to another task; default: memo
	-e <error filename>
	-g Don't ask getcon to release consoles
	-h <msg header>
	-i <number of rows> rows to ask for
	-l add a level of debug messages
	-m Don't use NVRAM if present
	-o <device>[,<row>,<col>,<width>,<pass attr>,<warn>,<fail>,<debug>]
	-p Playback mode: don't send commands to server
	-r -1    Don't display next partition
	-r <row> Display next partition at this row of current console
	-s no message sounds
	-v disable verbose to stderr
	-x (with -b) make buffer-client non-blocking
	-y disable system error message concatenation to messages
#endif
