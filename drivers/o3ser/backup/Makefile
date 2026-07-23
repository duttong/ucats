CC=cc
CFLAGS=-2 -w4
BINDIR=/home/uav/bin
SRCDIR=/home/uav/flight/src

all: o3ser install

install: 
	cp -n o3ser $(BINDIR)
	cp -n o3ser.h $(SRCDIR)

sertest: 
	$(CC) $(CFLAGS) sertest.c -o sertest
	cp -n sertest $(BINDIR)

clean:
	rm *.o o3ser sertest

	
