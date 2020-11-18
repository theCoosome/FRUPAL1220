CC=g++
CFLAGS= -g -Wall -Werror
LDFLAGS= -lncurses
PROGS= frupal fog_test

all: $(PROGS)

frupal: main.cpp object.cpp object.h world.cpp world.h
	$(CC) $(CFLAGS) main.cpp object.cpp world.cpp -o $@ $(LDFLAGS)

fog_test: fog_test.cpp fog.cpp fog.h
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

zip:
	zip frupal.zip *

clean:
	rm -f $(PROGS) *.o ~*
