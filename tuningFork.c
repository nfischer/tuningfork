/***********************************************************
*                                                          *
* Generates a .wav file with specified duration,           *
* frequency, and other parameters.                         *
*                                                          *
* This produces a 2 channel .wav file.                     *
*                                                          *
* The .wav extension should be appended to any specified   *
* file name that does not already have it.                 *
*                                                          *
* Authors: Brandon Freitag, Nate Fischer, and Ivan De Dios *
* Started November 2013                                    *
*                                                          *
***********************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Global constants
const double MIN_FREQ = 0;
const double MAX_FREQ = 22050;  // 22050 Hz
const double MIN_DURATION = 0;
const double MAX_DURATION = 60 * 100;  // 100 minutes
const int MAX_NAME_LEN = 255;
const int LOOKUP_TABLE_SIZE = 8192;
const int QUARTER_TABLE_SIZE = 2048;
const int MAX_VOLUME = 0x7FFF;
const double PI = 3.141592653589793;  // full precision supported

void genFile(double freq, double time, char* fname);
void checkInputFormat(double freq, double duration, char* fname);

int main() {
    double freq, duration;
    char fname[MAX_NAME_LEN];
    /*
        255 characters is the longest file name supported on Linux
        We _should_ however support longer names, since this also
        permits paths to be written, and a valid path may exceed
        255 characters.

        Entering a name longer than 255 characters causes the
        program to crash. This should clearly be fixed.
    */

    // get user input
    int hasInputErrors = 0;
    printf("Input desired frequency (Hz): ");
    if (scanf("%lf", &freq) != 1)
    {
      hasInputErrors = 1;
    }
    printf("Input desired duration (sec): ");
    if (scanf("%lf", &duration) != 1)
    {
      hasInputErrors = 1;
    }
    printf("Enter desired file name: ");
    // scanf("\n%[^\n]s", fname);
    if (hasInputErrors)
    {
      fprintf(stderr, "Error reading user input\n");
      exit(1);
    }

    // throw out everything up until newline
    char garbageChar;
    for (garbageChar = getchar(); garbageChar != '\n'; garbageChar = getchar()) continue;

    // read in name (with buffer protection)
    if (fgets(fname, MAX_NAME_LEN, stdin) == NULL)
    {
      fprintf(stderr, "Error reading user input\n");
      exit(1);
    }

    /* Check for valid input values
        MIN_FREQ = 0
        MAX_FREQ = 22050 Hz
        MIN_DURATION = 0
        MAX_DURATION = 60 * 100 s = 100 minutes
    */

    checkInputFormat(freq, duration, fname);

    // Generate the file
    genFile(freq, duration, fname);

    return 0;
}


void checkInputFormat(double freq, double duration, char* fname) {
    /* Check for valid input values
        MIN_FREQ = 0
        MAX_FREQ = 22050 Hz
        MIN_DURATION = 0
        MAX_DURATION = 60 * 100 s = 100 minutes
    */

    int shouldExit = 0;
    if (freq <= MIN_FREQ || freq > MAX_FREQ) {
        fprintf(stderr,"ERROR: You must input a frequency value in the range %d < frequency <= %d. Exiting with status (1)\n", (int)MIN_FREQ, (int)MAX_FREQ);
        shouldExit = 1;
    }

    if (duration <= MIN_DURATION || duration > MAX_DURATION) {
        fprintf(stderr,"ERROR: You must input a duration value in the range %d < duration <= %d. Exiting with status (1)\n", (int)MIN_DURATION, (int)MAX_DURATION);
        shouldExit = 1;
    }

    int nameLen = strlen(fname);

    // strip trailing newline
    fname[nameLen-1] = '\0';  // was previously newline
    nameLen--;

    // empty string name
    if (strcmp(fname, "") == 0) {  // empty string is invalid
        fprintf(stderr,"ERROR: You must input a nonempty file name. Exiting with status (1)\n");
        shouldExit = 1;
    }

    // Catches the zero byte in the file name

    // exit with proper status
    if (shouldExit == 1)  // should exit with status (1)
        exit(1);

    // Check for proper file name extension
    char nameV = fname[nameLen-1];
    char nameA = fname[nameLen-2];
    char nameW = fname[nameLen-3];
    char nameP = fname[nameLen-4];
    int shouldExtend;
    if (nameLen > 4) {  // long enough to be valid name
        if (nameP == '.' && nameW == 'w' && nameA == 'a' && nameV == 'v')  // last 4 characters are ".wav"
            shouldExtend = 0;  // File name meets requirements and does not need .wav appending
        else
            shouldExtend = 1;
    } else {  // short enough that it must need an extension
        shouldExtend = 1;
    }

    // Append the .wav extension
    if (shouldExtend == 1)
        strcat(fname, ".wav");

    return;
}

void genFile(double freq, double duration, char* fname) {
    /*
        Writing to the file is bit-count specific, so size-specific types
        must be used for every value written to the file.
    */

    const int SAMPLE_RATE = 44100;

    //////////////////////////
    // Calculate subchunk2Size
    //////////////////////////

    // int should be 32 bits on most systems
    //                = NumSamples * NumChannels * BitsPerSample/8
    int subchunk2Size = (duration * SAMPLE_RATE) * 2 * 16 / 8;

    uint32_t scx = subchunk2Size;  // scx will be modified

    // shift by 8 bits
    uint8_t B4 = scx;
    scx = scx >> 8;
    uint8_t B3 = scx;
    scx = scx >> 8;
    uint8_t B2 = scx;
    scx = scx >> 8;
    uint8_t B1 = scx;

    //////////////////////
    // Calculate ChunkSize
    //////////////////////

    int chunkSize = 36 + subchunk2Size;

    uint32_t cx = chunkSize;  // cx will be modified

    // int8_t is 8 bits (one byte)
    // shift by 8 bits
    uint8_t C4 = cx;
    cx = cx >> 8;
    uint8_t C3 = cx;
    cx = cx >> 8;
    uint8_t C2 = cx;
    cx = cx >> 8;
    uint8_t C1 = cx;

    // int8_t is 8 bits, all these are 8 bits
    uint8_t HEADER[46] = {0x52, 0x49, 0x46, 0x46,   C4,   C3,   C2,   C1,
        /* offset:  8 */ 0x57, 0x41, 0x56, 0x45, 0x66, 0x6D, 0x74, 0x20,
                /* 16 */ 0x12, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00,
                /* 24 */ 0x44, 0xAC, 0x00, 0x00, 0x10, 0xB1, 0x02, 0x00,
                /* 32 */ 0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x64, 0x61,
                /* 40 */ 0x74, 0x61,   B4,   B3,   B2,   B1};

    /////////////////////////
    // Generate data subchunk
    /////////////////////////
    int numSamples = SAMPLE_RATE * duration;

    // Generate a lookup table for samples
    // We can evaluate any value over an entire period using just the first quadrant
    int16_t* lookupTable = malloc(sizeof(int16_t) * LOOKUP_TABLE_SIZE);
    int i;
    for (i = 0; i < QUARTER_TABLE_SIZE; i++) {
        lookupTable[i] = MAX_VOLUME * sin((PI / 2) * ((double)i / QUARTER_TABLE_SIZE));
        lookupTable[(QUARTER_TABLE_SIZE * 2) - i - 1] = lookupTable[i];
        lookupTable[i + QUARTER_TABLE_SIZE * 2] = ~lookupTable[i];
        lookupTable[(QUARTER_TABLE_SIZE * 4) - i - 1] = ~lookupTable[i];
    }

    const double phaseIncrement = (double)(freq / SAMPLE_RATE) * LOOKUP_TABLE_SIZE;
    double phase = 0.0;
    int phase_i = 0;
    int16_t* dataSubChunk = malloc(sizeof(int16_t) * numSamples * 2);

    for (i = 0; i < numSamples; i += 2) {
        phase_i = (int)phase;
        dataSubChunk[i] = lookupTable[phase_i];
        dataSubChunk[i + 1] = lookupTable[phase_i];
        phase += phaseIncrement;
        if (phase >= (double)LOOKUP_TABLE_SIZE)
            phase -= (double)LOOKUP_TABLE_SIZE;
    }

    FILE *OutFile;

    int shouldExit = 0;
    OutFile = fopen(fname, "w");
    if (OutFile != NULL) {
        // Write header to file
        fwrite(HEADER, 1, 46, OutFile);  // guaranteed to be 1 byte

        // Write audio data subchunk to file
        fwrite(dataSubChunk, 2, numSamples, OutFile);
    } else {
        fprintf(stderr, "Error opening your file. Terminating program.\n");
        shouldExit = 1;
    }

    fclose(OutFile);

    free(dataSubChunk);
    free(lookupTable);

    if (shouldExit != 0)
        exit(shouldExit);
}
