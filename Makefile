CC=g++
CFLAGS= -g -Wall -Werror
LDFLAGS= -lncurses
PROGS= frupal

all: $(PROGS)

frupal: main.cpp object.cpp object.h world.cpp world.h
	$(CC) $(CFLAGS) main.cpp object.cpp world.cpp -o $@ $(LDFLAGS)

zip:
	zip frupal.zip *

clean:
	rm -f $(PROGS) *.o ~*
