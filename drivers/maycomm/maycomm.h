#include "globmsg.h"

// struct for a single path in the Maycomm TDL instrument 
typedef struct {
	float h2o;			// h2o in ppmv
	int amp;			// 2f signal amplitude.
	int pow;			// laser power
	int pos;			// spectral line position
	short zero;			// zero level
} TDLpath;

typedef struct {
	long	rec;		// record number
	float	p;			// pressure in cell
	float	t;			// temp in cell
	TDLpath	l;			// long path struct
	TDLpath s;			// short path struct
} TDLstruct;

enum {
	msg_TDLquit = MAX_GLOBMSG,
	msg_TDLnomsg,
	msg_TDLcol
};

#define NUM_TDL_RECS	2
