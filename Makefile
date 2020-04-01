CC=gcc
CFLAGS=-Wall -g -pthread
OBJECTS = main.o
.PHONY : clean

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o all

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c

clean:
	-rm *.o all