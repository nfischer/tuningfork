# makefile for tuningFork

CC=gcc
CFLAGS=-Wall -O2
LDFLAGS=-lm

all: tf

tf: tuningFork.o
	$(CC) $(CFLAGS) tuningFork.o -o tf $(LDFLAGS)

tuningFork.o:
	$(CC) $(CFLAGS) -c tuningFork.c $(LDFLAGS)


clean:
	rm -f *.o tf *.stackdump *.wav
