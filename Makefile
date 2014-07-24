# makefile for tuningFork

CFLAGS  := 
LDFLAGS := -lm
SOURCES := tuningFork.c
OBJECTS :=$(SOURCES:.cpp=.o)
EXECUTABLE := tf

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

clean:
	rm -f *.o *.wav $(EXECUTABLE) *.stackdump
