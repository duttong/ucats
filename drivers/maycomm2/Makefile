CC=cc
CFLAGS=-2 -w4 -O
BINDIR=/home/uav/bin
SRCDIR=/home/uav/flight/src

all: maycomm install

maycomm: maycomm.o
	$(CC) $(CFLAGS) $@.c -o $@

install: 
	cp -n maycomm $(BINDIR)
	cp -n maycomm.h $(SRCDIR)

clean:
	rm -f *.o maycomm
