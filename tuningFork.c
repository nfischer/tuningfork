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

/* Global constants */
const double MIN_FREQ = 0;
const double MAX_FREQ = 22050; /* 22050 Hz */
const double MIN_DURATION = 0;
const double MAX_DURATION = 60 * 100; /* 100 minutes */
const int MAX_NAME_LEN = 255;

const double PI = 3.141592653589793; // this is the max precision supported

void genFile(double freq, double time, char* fname);
void checkInputFormat(double freq, double duration, char* fname);

int main() {
  double freq, duration;
  char fname[MAX_NAME_LEN];
  /*
    255 characters is the longest file name supported on Linux We *should*
    however support longer names, since this also permits paths to be written,
    and a valid path may exceed 255 characters.

    Entering a name longer than 255 characters causes the program to crash. This
    should clearly be fixed.
  */

  // get user input
  int hasInputErrors = 0;
  printf("Input desired frequency (Hz): ");
  if (scanf("%lf", &freq) != 1) {
    hasInputErrors = 1;
  }
  printf("Input desired duration (sec): ");
  if (scanf("%lf", &duration) != 1) {
    hasInputErrors = 1;
  }

  printf("Enter desired file name: ");
  if (hasInputErrors) {
    fprintf(stderr, "Error reading user input\n");
    exit(1);
  }

  // throw out everything up until newline, then begin reading the name
  char garbageChar;
  for (garbageChar = getchar(); garbageChar != '\n'; garbageChar = getchar() );

  // read in name (with buffer protection)
  if (fgets(fname, MAX_NAME_LEN, stdin) == NULL) {
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


void checkInputFormat(double freq, double duration, char* fname)
{
  /* Check for valid input values

    MIN_FREQ = 0
    MAX_FREQ = 22050 Hz
    MIN_DURATION = 0 
    MAX_DURATION = 60 * 100 s = 100 minutes
  */

  int shouldExit = 0;
  // frequency
  if (freq <= MIN_FREQ || freq > MAX_FREQ) {
    fprintf(stderr,
            "ERROR: You must input a frequency value in the range %d < frequency <= %d. Exiting with status (1)\n",
            (int)MIN_FREQ, (int)MAX_FREQ);
    shouldExit = 1;
  }

  // duration / length
  if (duration <= MIN_DURATION || duration > MAX_DURATION) {
    fprintf(stderr,"ERROR: You must input a duration value in the range %d < duration <= %d. Exiting with status (1)\n", (int)MIN_DURATION, (int)MAX_DURATION);
    shouldExit = 1;
  }

  int nameLen = strlen(fname);

  // strip trailing newline
  fname[nameLen-1] = '\0'; // was previously newline
  nameLen--;

  // empty string name
  if (strcmp(fname, "") == 0) { // empty string is invalid
    fprintf(stderr,"ERROR: You must input a nonempty file name. Exiting with status (1)\n");
    shouldExit = 1;
  }

  // Catches the zero byte in the file name

  // exit with proper status
  if (shouldExit == 1) // should exit with status (1)
    exit(1);

  // Check for proper file name extension

  char nameV = fname[nameLen-1];
  char nameA = fname[nameLen-2];
  char nameW = fname[nameLen-3];
  char nameP = fname[nameLen-4];
  int shouldExtend;
  if (nameLen > 4) { // long enough to be valid name
    if (nameP == '.' && nameW == 'w' && nameA == 'a' && nameV == 'v') // last 4 characters are ".wav"
      shouldExtend = 0; // File name meets requirements and does not need .wav appending
    else
      shouldExtend = 1;
  } else { // short enough that it must need an extension
    shouldExtend = 1;
  }

  // Append the .wav extension
  if (shouldExtend == 1)
    strcat(fname, ".wav");

  return;
}

void genFile(double freq, double duration, char* fname)
{
  /*
    Writing to the file is bit-count specific, so size-specific types
    must be used for every value written to the file.
  */

  const int SAMPLE_RATE = 44100;

  ///////////////////////////
  // Calculate subchunk2Size
  ///////////////////////////

  // int should be 32 bits on most systems
  //          = NumSamples * NumChannels * BitsPerSample/8
  int subchunk2Size = (duration * SAMPLE_RATE) * 2 * 16 / 8;

  uint32_t scx = subchunk2Size; // scx will be modified

  // shift by 8 bits
  uint8_t B4 = scx;
  scx = scx >> 8;
  uint8_t B3 = scx;
  scx = scx >> 8;
  uint8_t B2 = scx;
  scx = scx >> 8;
  uint8_t B1 = scx;

  ///////////////////////////
  // Calculate ChunkSize
  ///////////////////////////

  int chunkSize = 36 + subchunk2Size;

  uint32_t cx = chunkSize; // cx will be modified

  // int8_t is 8 bits (one byte)
  // shift by 8 bits
  uint8_t C4 = cx;
  cx = cx >> 8;
  uint8_t C3 = cx;
  cx = cx >> 8;
  uint8_t C2 = cx;
  cx = cx >> 8;
  uint8_t C1 = cx;

  // int8_t is 8 bits, and all these are 8 bits
  uint8_t HEADER[46] = {0x52, 0x49, 0x46, 0x46,   C4,   C3,   C2,   C1,
       /* offset:  8 */ 0x57, 0x41, 0x56, 0x45, 0x66, 0x6D, 0x74, 0x20,
               /* 16 */ 0x12, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00,
               /* 24 */ 0x44, 0xAC, 0x00, 0x00, 0x10, 0xB1, 0x02, 0x00,
               /* 32 */ 0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x64, 0x61,
               /* 40 */ 0x74, 0x61,   B4,   B3,   B2,   B1};


  //////////////////////
  // Calculate samples
  //////////////////////


  const int NUM_PERIODS = 400;
  int16_t sample; // designates value of wave func at that point
  int max_volume = 0x7FFF;
  double omega = 2*PI*freq; // cuts down on calculation time

  int i;

  double period = 1/freq; // in seconds
  int tableSize = NUM_PERIODS * SAMPLE_RATE * period; // in samples
  uint16_t* sampleTable = malloc(sizeof(uint16_t) * tableSize);

  int dataLoopLimit = SAMPLE_RATE * duration;
  uint16_t* dataArr = malloc(sizeof(uint16_t) * 2 * dataLoopLimit);

  // Generate a lookup table for samples
  double omegaT = 0; // omega * time
  double deltaOmegaT = (double)omega/SAMPLE_RATE;

  for (i = 0; i < tableSize; i++) {
    sample = max_volume * sin(omegaT);
    // equivalent to:
    // sample = max_volume * sin(omega * (double)i/SAMPLE_RATE);

    sampleTable[i] = sample;
    omegaT += deltaOmegaT; // gives next value to evaluate sin at
  }


  int periodIndex = 0; // the index within the current period relative to
                       // the start of the period

  // Populate sample array from lookup table
  for (i = 0; i < dataLoopLimit; i++) {
    sample = sampleTable[periodIndex];

    /* write two samples to array */
    int j = i*2;
    dataArr[j] = sample;
    dataArr[j+1] = sample;

    periodIndex++;
    if ( periodIndex >= tableSize) {
      // reset the index
      periodIndex = 0;
    }
  }

  int shouldExit = 0;
  FILE *OutFile = fopen(fname, "w");
  if (OutFile != NULL) {
    /* Write header to file */
    fwrite(HEADER, 1, 46, OutFile); // guaranteed to be 1 byte

    /* Write audio data to file */
    fwrite(dataArr, 2, 2*dataLoopLimit, OutFile);
  } else {
    fprintf(stderr, "Error opening your file. Terminating program.\n");
    shouldExit = 1;
  }

  fclose(OutFile);

  // free dynamically allocated memory
  free(dataArr);
  free(sampleTable);

  if (shouldExit != 0)
    exit(shouldExit);
}
