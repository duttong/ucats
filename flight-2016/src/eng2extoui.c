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

Spreadsheet eng2, 21 columns:
  eng2         [ 1] = temp_pump
  eng2         [ 2] = temp_SL2
  eng2         [ 3] = temp_amb
  eng2         [ 4] = pres_extern
  eng2         [ 5] = volt_1234
  eng2         [ 6] = presL_dope
  eng2         [ 7] = presL_cal
  eng2         [ 8] = presL_N2
  eng2         [ 9] = presH_123
  eng2         [10] = volt_5
  eng2         [11] = volt_15
  eng2         [12] = volt_28
  eng2         [13] = CH2_ECD
  eng2         [14] = CH2_Col
  eng2         [15] = CH2_Post
  eng2         [16] = CH1_ECD
  eng2         [17] = CH1_Col
  eng2         [18] = GCstate
  eng2         [19] = ssv
  eng2         [20] = valv_calSSV
#endif
