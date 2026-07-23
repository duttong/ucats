CC=cc
CFLAGS=-2 -w4
BINDIR=/home/uav/bin
SRCDIR=/home/uav/flight/src

all: iseries install

iseries: iseries.o
	$(CC) $(CFLAGS) $@.c -o $@

install: 
	cp -n iseries $(BINDIR)

clean:
	rm -f *.o iseries

	
	
