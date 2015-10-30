# makefile for tuningFork

CFLAGS  := -O2
LDFLAGS := -lm
SOURCES := tuningFork.c
OBJECTS :=$(SOURCES:.c=.o)
TESTBIN := diffWaveFiles
TEST440WAV := test_files/A440.wav
TEST880WAV := test_files/A880.wav
TEST261WAV := test_files/C261.wav
EXECUTABLE  := tf
TESTSOURCES := test.c
TESTOBJECTS :=$(TESTSOURCES:.c=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(TESTBIN): $(TESTOBJECTS)
	$(CC) $(CFLAGS) $(TESTOBJECTS) -o $@ $(LDFLAGS)

test1: $(EXECUTABLE) $(TESTBIN)
	./tune -d 10 -f 261.6 -n tmp.wav
	./$(TESTBIN) tmp.wav $(TEST261WAV) 261.6

test2: $(EXECUTABLE) $(TESTBIN)
	./tune -d 10 -f 440 -n tmp.wav
	./$(TESTBIN) tmp.wav $(TEST440WAV) 440

test3: $(EXECUTABLE) $(TESTBIN)
	./tune -d 10 -f 880 -n tmp.wav
	./$(TESTBIN) tmp.wav $(TEST880WAV) 880

test: test1 test2 test3
	rm -f tmp.wav; echo "\nAll tests passed"

clean:
	rm -f *.o *.wav $(EXECUTABLE) $(TESTBIN) *.stackdump
