# makefile for tuningFork

CC=gcc
CFLAGS=-Wall -O3
LDFLAGS=-lm

all: tf

tf: tuningFork.o
	$(CC) $(CFLAGS) tuningFork.o -o tf $(LDFLAGS)

#fast:
#	$(CC) $(CFLAGS) -O3 tuningFork.c -o tf $(LDFLAGS)

tuningFork.o:
	$(CC) $(CFLAGS) -c tuningFork.c $(LDFLAGS)


clean:
	rm -f *.o tf *.stackdump *.wav
