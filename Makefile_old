CC=gcc
CFLAGS=-Wall -g -DNDEBUG
DEPS=ex22.h dbg.h
OBJ=ex22_main.o ex22.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ex22: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

all: ex22

clean:
	rm -f ex22
	rm -f ex22_main.o
	rm -f ex22.o
