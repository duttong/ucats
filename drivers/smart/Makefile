CC=cc
CFLAGS=-2 -w4
BINDIR=/home/uav/bin
SRCDIR=/home/uav/flight/src

all: smart install 

smart: smart.o
	$(CC) $(CFLAGS) $@.c -o $@

install: 
	cp -n smart $(BINDIR)
	cp -n smart.h $(SRCDIR)

clean:
	rm -f *.o smart
