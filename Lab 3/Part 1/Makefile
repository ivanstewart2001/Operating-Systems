CC = gcc
CFLAGS = -D_SVID_SOURCE -D_GNU_SOURCE -Wall -std=c99 -Werror=cpp -pedantic

all: pipes_processes1

pipes_proc1: pipes_processes1.c
	$(CC) -o pipes_processes1 pipes_processes1.c $(CFLAGS)

clean:
	rm -f pipes_processes1
