#include "globmsg.h"

typedef struct {
	unsigned short day;
	unsigned short mon;
	unsigned short year;
} O3date;

typedef struct {
	unsigned short hh;
	unsigned short min;
	unsigned short sec;
} O3time;

// log = log record
// o3 = ozone
// t = temperature
// p = pressure
typedef struct {
	// unsigned short log;
	float o3;
	float t;
	float p;
	float lamp_v;
	float lamp_sd;
	O3date date;
	O3time time;
} O3struct;

enum {
	msg_o3quit = MAX_GLOBMSG,
	msg_o3nomsg,
	msg_o3col
};
