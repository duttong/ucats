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

Spreadsheet o3out, 13 columns:
  o3out        [ 1] = o3yy
  o3out        [ 2] = o3mm
  o3out        [ 3] = o3dd
  o3out        [ 4] = o3hh
  o3out        [ 5] = o3min
  o3out        [ 6] = o3ss
  o3out        [ 7] = o3
  o3out        [ 8] = o3temp
  o3out        [ 9] = o3pres
  o3out        [10] = o3best
  o3out        [11] = o3lmpv
  o3out        [12] = o3lmpsd
#endif
