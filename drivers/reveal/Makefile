CC= cc
CFLAGS= -g -2 -w4 -Oil
LDFLAGS= -g -lsocket
INST=uav
BINDIR=/home/$(INST)/bin
SRCDIR=/home/$(INST)/flight/src

all: clean reveal install

reveal:
	$(CC) $(CFLAGS) $(LDFLAGS) $@.c -o $@ 

install: 
	cp -n reveal $(BINDIR)
	cp -n reveal.h $(SRCDIR)

clean:
	rm -f *.o reveal 
