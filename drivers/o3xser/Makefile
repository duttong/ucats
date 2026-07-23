CC=cc
CFLAGS=-2 -w4
BINDIR=/home/uav/bin
SRCDIR=/home/uav/flight/src

all: o3xser install

o3xser: o3xser.o
	$(CC) $(CFLAGS) $@.c -o $@

install: 
	cp -n o3xser $(BINDIR)

clean:
	rm *.o o3xser

	
