/* OUI output from the following packages:
   kbdclt
   msghdr
   msghdr_init
   msg
   cmdctrl
   nl_error_init
   client
   nl_cons
*/
char *opt_string = "h:e:o:c:lvsyC:pA:a:g";
#include "oui.h"
#include "msg.h"
#include "globmsg.h"
#include "nortlib.h"
#include <stdlib.h>
#include "nl_cons.h"
  extern int kbdclt_quit( int argc, char **argv );
  static int cmdctrl_pid;
  void nlcg_receive(pid_t who) {
	if ( cmdctrl_pid != -1 && who == cmdctrl_pid ) {
	  reply_byte( who, DAS_OK );
	  exit( 0 );
	} else reply_byte( who, DAS_UNKN );
  }
  int (*nl_error)(int level, char *s, ...) = msg;

void oui_init_options(int argc, char **argv) {
  char *msg_hdr;
  msg_hdr = "Clt";
  msg_init_options(msg_hdr, argc, argv);
  cmdctrl_pid = kbdclt_quit( argc, argv );
  cic_options(argc, argv, msg_hdr);
  Con_init_options(argc, argv);
  atexit(nlcon_close);
}

#ifdef __USAGE
%C	[options]
	-A <console> Open console as screen 0 instead of STDOUT
	-a <console> Open console as screen 1, etc.
	-C <node> send commands to server on specified node
	-c <node>[,<attached name>] send msgs to another task; default: memo
	-e <error filename>
	-g Don't ask getcon to release consoles
	-h <msg header>
	-l add a level of debug messages
	-o <device>[,<row>,<col>,<width>,<pass attr>,<warn>,<fail>,<debug>]
	-p Playback mode: don't send commands to server
	-s no message sounds
	-v disable verbose to stderr
	-y disable system error message concatenation to messages
#endif
