#include "globmsg.h"

typedef struct {
	float rh;
	float t;
} RHstruct;

enum {
	msg_RHquit = MAX_GLOBMSG,
	msg_RHnomsg,
	msg_RHcol
};
