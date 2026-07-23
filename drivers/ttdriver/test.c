
#include <stdio.h>

void main() {

	unsigned short offset,chan,channel;

	for(channel=0; channel<= 16; channel++) {
		chan=channel-(channel/16)*16;
		offset=(channel/16)*0x10;
		printf("channel = %d, chan = %d, offset = %d\n", channel, chan, offset);
	}

}