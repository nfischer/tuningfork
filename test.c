/***********************************************************
*                                                          *
* Takes in 2 .wav files and gives a numerical evaluation   *
* of their difference                                      *
*                                                          *
* Authors: Brandon Freitag, Nate Fischer, and Ivan De Dios *
* Started November 2015                                    *
*                                                          *
***********************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int compareFileSizes(char* fname1, char* fname2, int* buf)
{
  struct stat buf1;
  struct stat buf2;

  stat(fname1, &buf1);
  stat(fname2, &buf2);

  *buf = (int)buf1.st_size;
  return buf1.st_size - buf2.st_size;
}

const int BUFSIZE_LIMIT = 2 << 28; // 256M items, so 512MB of RAM
const double THRESHOLD = 1.0; // arbitrary threshold
const int SAMPLE_RATE = 44100;

int main(int argc, char *argv[])
{
  if (argc < 4)
  {
    if (argc < 3)
      fprintf(stderr,"Must supply two filenames and the frequency\n");
    else
      fprintf(stderr,"Must supply the frequency as well\n");
    exit(-1);
  }

  // Verify that files exist
  char* fname1 = argv[1];
  char* fname2 = argv[2];
  FILE *inFile1 = fopen(fname1, "r");
  FILE *inFile2 = fopen(fname2, "r");
  double freq = atoi(argv[3]);
  if (freq <= 0)
  {
    fprintf(stderr,"Must supply a valid frequency\n");
    exit(-1);
  }
  if (inFile1 == NULL || inFile2 == NULL)
  {
    if (inFile1 != NULL)
      fclose(inFile1);
    if (inFile2 != NULL)
      fclose(inFile2);
    fprintf(stderr, "Error opening your files. Terminating program.\n");
    exit(-2);
  }

  // Make sure file sizes match
  int fileSize;
  if (compareFileSizes(fname1, fname2, &fileSize))
  {
    fprintf(stderr, "Your files differ in size\n");
    exit(-3);
  }

  // Read in both files to buffers
  int bufsize = (fileSize/2) < BUFSIZE_LIMIT ? (fileSize/2) : BUFSIZE_LIMIT;
  int16_t *buf1 = malloc(bufsize * sizeof(int16_t));
  int16_t *buf2 = malloc(bufsize * sizeof(int16_t));
  fread(buf1, 2, bufsize, inFile1);
  fread(buf2, 2, bufsize, inFile2);
  fclose(inFile1);
  fclose(inFile2);

  // See how closely file contents match
  int k;
  long int runningTotal = 0;
  for (k=0; k < bufsize; k++)
  {
    int difference = buf1[k] - buf2[k];
    if (difference < 0)
      difference *= -1; // absolute value
    runningTotal += difference;
  }
  long int average = runningTotal / bufsize;

  free(buf1);
  free(buf2);

  double numPeriods = (fileSize/2) / SAMPLE_RATE * freq;
  if (average/numPeriods < THRESHOLD)
    return 0;
  else
  {
    printf("The difference is: %lf\n", average/numPeriods);
    return average;
  }
}
