CC=cc
CFLAGS=-2 -w4 -O
BINDIR=/home/uav/bin
SRCDIR=/home/uav/flight/src

all: vaisala install

vaisala: vaisala.o
	$(CC) $(CFLAGS) $@.c -o $@

install: 
	cp -n vaisala $(BINDIR)
	cp -n vaisala.h $(SRCDIR)

clean:
	rm -f *.o vaisala

	
