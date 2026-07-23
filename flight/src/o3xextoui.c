/* OUI output from the following packages:
   edfoui
   msghdr
   msghdr_init
   msg
   dc
   nl_error_init
*/
char *opt_string = "h:e:o:c:lvsyb:i:x";
#include "oui.h"
#include "msg.h"
#include "dbr.h"
#include "nortlib.h"
  int (*nl_error)(int level, char *s, ...) = msg;

void oui_init_options(int argc, char **argv) {
  char *msg_hdr;
  msg_hdr = "Ext";
  msg_init_options(msg_hdr, argc, argv);
  DC_init_options(argc, argv);
}

#ifdef __USAGE
%C	[options]
	-b <node> become a star client of the buffer on given node
	-c <node>[,<attached name>] send msgs to another task; default: memo
	-e <error filename>
	-h <msg header>
	-i <number of rows> rows to ask for
	-l add a level of debug messages
	-o <device>[,<row>,<col>,<width>,<pass attr>,<warn>,<fail>,<debug>]
	-s no message sounds
	-v disable verbose to stderr
	-x (with -b) make buffer-client non-blocking
	-y disable system error message concatenation to messages

Spreadsheet o3xout, 13 columns:
  o3xout       [ 1] = o3xyy
  o3xout       [ 2] = o3xmm
  o3xout       [ 3] = o3xdd
  o3xout       [ 4] = o3xhh
  o3xout       [ 5] = o3xmin
  o3xout       [ 6] = o3xss
  o3xout       [ 7] = o3x
  o3xout       [ 8] = o3xtemp
  o3xout       [ 9] = o3xpres
  o3xout       [10] = o3xbest
  o3xout       [11] = o3xflowa
  o3xout       [12] = o3xflowb
#endif
