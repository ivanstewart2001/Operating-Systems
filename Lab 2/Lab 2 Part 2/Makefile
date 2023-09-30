CC = gcc
CFLAGS = -Wall

all: signal timer

signal: signal.c
	$(CC) $(CFLAGS) -o signal signal.c

timer: timer.c
	$(CC) $(CFLAGS) -o timer timer.c

clean:
	rm -f signal timer
