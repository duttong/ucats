CC= cc
CFLAGS= -2 -w4 -Oil
INST= uav
BINDIR=/home/$(INST)/bin
SRCDIR=/home/$(INST)/flight/src

all: clean kuband install

kuband:
	$(CC) $(CFLAGS) $@.c -o $@ 

install: 
	cp -n kuband $(BINDIR)
	cp -n kuband.h $(SRCDIR)

clean:
	rm -f *.o kuband 

