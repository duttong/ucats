/* OUI output from the following packages:
   collect
   seteuid
   msghdr
   msghdr_init
   msg
   dg
   nl_error_init
*/
char *opt_string = "h:e:o:c:lvsyn:j:";
#include "oui.h"
#include <unistd.h>
#include "msg.h"
#include "dbr.h"
#include "nortlib.h"
  static char seteuidid[] = "$Id: seteuid.oui,v 1.2 1994/10/18 19:03:44 nort Exp nort $";
  int (*nl_error)(int level, char *s, ...) = msg;

void oui_init_options(int argc, char **argv) {
  char *msg_hdr;
  seteuidid[0] = seteuidid[0];
  seteuid(getuid());
  msg_hdr = "Col";
  msg_init_options(msg_hdr, argc, argv);
  DG_init_options(argc, argv);
}

#ifdef __USAGE
%C	[options]
	-c <node>[,<attached name>] send msgs to another task; default: memo
	-e <error filename>
	-h <msg header>
	-j <milliseconds> approximate regulator, delay between token data reads
	-l add a level of debug messages
	-n <number of clients> start ring after client initialisations
	-o <device>[,<row>,<col>,<width>,<pass attr>,<warn>,<fail>,<debug>]
	-s no message sounds
	-v disable verbose to stderr
	-y disable system error message concatenation to messages
#endif
