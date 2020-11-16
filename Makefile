CC=g++
CFLAGS= -g -Wall -Werror
LDFLAGS= -lncurses
PROGS= frupal

all: $(PROGS)

%: main.cpp object.cpp object.h world.cpp world.h
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

zip:
	zip frupal.zip *

clean:
	rm -f $(PROGS) *.o ~*
