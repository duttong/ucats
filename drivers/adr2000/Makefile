CC=cc
CFLAGS=-2 -w4
BINDIR=/home/uav/bin
SRCDIR=/home/uav/flight/src

all: adr2000 install

adr2000: adr2000.o
	$(CC) $(CFLAGS) $@.c -o $@

install: 
	cp -n adr2000 $(BINDIR)
	cp -n adr2000.h $(SRCDIR)

clean:
	rm -f *.o adr2000
	
