CC=gcc
CFLAGS=-Wall -g -pthread
OBJECTS = main.o client.o server.o
.PHONY : clean

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o all

main.o: main.c global.h client.h server.h
	$(CC) $(CFLAGS) -c main.c

client.o: client.c client.h global.h
	$(CC) $(CFLAGS) -c client.c

server.o: server.c server.h global.h
	$(CC) $(CFLAGS) -c server.c

clean:
	-rm *.o all