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

Spreadsheet eng1, 21 columns:
  eng1         [ 1] = flow_M1
  eng1         [ 2] = flow_M1_sp
  eng1         [ 3] = flow_BF1
  eng1         [ 4] = flow_BF1_sp
  eng1         [ 5] = pres_BP1
  eng1         [ 6] = pres_BP1_sp
  eng1         [ 7] = pres_SL
  eng1         [ 8] = temp_gasB_N
  eng1         [ 9] = temp_SL1
  eng1         [10] = temp_gasB_C
  eng1         [11] = flow_SL
  eng1         [12] = flow_M2
  eng1         [13] = flow_M2_sp
  eng1         [14] = flow_BF2
  eng1         [15] = flow_BF2_sp
  eng1         [16] = pres_PUMP
  eng1         [17] = pres_BP2_sp
  eng1         [18] = pres_ECD2
  eng1         [19] = ecdA_CH1
  eng1         [20] = ecdA_CH2
#endif
