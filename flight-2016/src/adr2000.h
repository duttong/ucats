#include "globmsg.h"

#define ADR2000_PROXY_NUM   9

#define ADR2000_NAME		"adr2000"

#define ADchans				8	// number of A to D channels per board
#define DAchans				2	// number of D to A channels per board
#define DIGchans			8	// number of digital channels
#define NUMboards			3	// number of ADR2000 boards used

typedef struct {
	float 	analog[ADchans];
	float	dtoa[DAchans];
	int		dig[DIGchans];
} ADRstruct;

enum {
	msg_adrQuit = MAX_GLOBMSG,
	msg_adrNoMsg,
	msg_adrRetAll,
	msg_adrSetDig,
	msg_adrSetDtoA
};
