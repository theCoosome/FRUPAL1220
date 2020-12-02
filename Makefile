CC=g++
CFLAGS= -g -Wall# -Werror
LDFLAGS= -lncurses
PROGS= frupal fog_test

all: $(PROGS)

frupal: main.cpp object.cpp object.h split.cpp split.h world.cpp world.h
	$(CC) $(CFLAGS) main.cpp object.cpp object.h split.cpp split.h world.cpp world.h -o $@ $(LDFLAGS)

fog_test: fog_test.cpp object.cpp object.h world.cpp world.h
	$(CC) $(CFLAGS) -DTEST fog_test.cpp object.cpp world.cpp -o $@ $(LDFLAGS)

test: fog_test
	./fog_test

zip:
	zip frupal.zip *

clean:
	rm -f $(PROGS) *.o ~*
