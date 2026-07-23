CC=cc
CFLAGS= -g -2 -w4 -Oil
LDFLAGS= -g -lsocket
INST=uav
BINDIR=/home/$(INST)/bin
SRCDIR=/home/$(INST)/flight/src

all: clean nasdat install 

nasdat:
	$(CC) $(CFLAGS) $(LDFLAGS) $@.c -o $@ 

t:
	$(CC) $(CFLAGS) $(LDFLAGS) $@.c -o $@ 

install: 
	cp -n nasdat $(BINDIR)
	cp -n nasdat.h $(SRCDIR)

clean:
	rm -f *.o nasdat 
