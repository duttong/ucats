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

Spreadsheet h2oout, 18 columns:
  h2oout       [ 1] = tdlrec
  h2oout       [ 2] = tdl_time
  h2oout       [ 3] = tdl_shortH2O
  h2oout       [ 4] = tdl_H2OB
  h2oout       [ 5] = tdl_longH2O
  h2oout       [ 6] = tdl_H2OCD
  h2oout       [ 7] = tdl_p
  h2oout       [ 8] = tdl_t
  h2oout       [ 9] = tdl_elecT
  h2oout       [10] = tdl_amp
  h2oout       [11] = tdl_pow
  h2oout       [12] = tdl_pos
  h2oout       [13] = tdl_zer
  h2oout       [14] = tdl_posB
  h2oout       [15] = vaiT
  h2oout       [16] = vaiRH
  h2oout       [17] = tdl_best
#endif
