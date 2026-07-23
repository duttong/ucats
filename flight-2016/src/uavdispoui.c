/* OUI output from the following packages:
   msghdr
   msghdr_init
   msg
   nl_cons
   tmg
   dc
   nl_error_init
*/
char *opt_string = "h:e:o:c:lvsyA:a:gb:i:x";
#include "oui.h"
#include "msg.h"
#include <stdlib.h>
#include "nl_cons.h"
#include "rtgapi.h"
#include "dbr.h"
#include "nortlib.h"
  int (*nl_error)(int level, char *s, ...) = msg;

void oui_init_options(int argc, char **argv) {
  char *msg_hdr;
  msg_hdr = "Ext";
  msg_init_options(msg_hdr, argc, argv);
  Con_init_options(argc, argv);
  atexit(nlcon_close);
  rtgext_init();
  DC_init_options(argc, argv);
}

#ifdef __USAGE
%C	[options]
	-A <console> Open console as screen 0 instead of STDOUT
	-a <console> Open console as screen 1, etc.
	-b <node> become a star client of the buffer on given node
	-c <node>[,<attached name>] send msgs to another task; default: memo
	-e <error filename>
	-g Don't ask getcon to release consoles
	-h <msg header>
	-i <number of rows> rows to ask for
	-l add a level of debug messages
	-o <device>[,<row>,<col>,<width>,<pass attr>,<warn>,<fail>,<debug>]
	-s no message sounds
	-v disable verbose to stderr
	-x (with -b) make buffer-client non-blocking
	-y disable system error message concatenation to messages
#endif
