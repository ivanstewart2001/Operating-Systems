# list/Makefile
#
# Makefile for list implementation and test file.
#
# <Author>

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
TARGET = list
MEMCHECK = valgrind --leak-check=full

all: $(TARGET)

$(TARGET): main.o list.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o list.o

main.o: main.c list.h
	$(CC) $(CFLAGS) -c main.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

memcheck: $(TARGET)
	$(MEMCHECK) ./$(TARGET)

clean:
	rm -f *.o $(TARGET)
