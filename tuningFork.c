/*********************************************************

Generates a .wav file with specified
duration, frequency, and other parameters

--- further description ---

Authors: Brandon Freitag, Nate Fischer, and Ivan De Dios
Started November 2013

*********************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define PI (3.141592653589793)

/* Global constants */
const double MIN_FREQ = 0;
const double MAX_FREQ = 22050; /* 22050 Hz */
const double MIN_DURATION = 0; 
const double MAX_DURATION = 60 * 100; /* 100 minutes */


void genFile(double freq, double time, char* fname);

int main()
{
	double freq, duration;
	char fname[50]; // arbitrary file name limit
	// fix arbitrary limit to be nonarbitrary

	// get user input
	printf("Input desired frequency (Hz): ");
	scanf("%lf", &freq);
	printf("Input desired duration (sec): ");
	scanf("%lf", &duration);
	printf("Enter desired file name: ");
	scanf("%s", fname);

	/* Check for valid input values

		MIN_FREQ = 0
		MAX_FREQ = 22050 Hz
		MIN_DURATION = 0 
		MAX_DURATION = 60 * 100 s = 100 minutes
	*/

	int shouldExit=0;
	if (freq <= MIN_FREQ || freq > MAX_FREQ)
	{
		fprintf(stderr,"ERROR: You must input a frequency value in the range %d < frequency <= %d. Exiting with status (1)\n", (int)MIN_FREQ, (int)MAX_FREQ);
		shouldExit = 1;
	}
	if (duration <= MIN_DURATION || duration > MAX_DURATION)
	{
		fprintf(stderr,"ERROR: You must input a duration value in the range %d < duration <= %d. Exiting with status (1)\n", (int)MIN_DURATION, (int)MAX_DURATION);
		shouldExit = 1;
	}
	if (strcmp(fname, "") == 0) /* empty string is invalid */
	{
		fprintf(stderr,"ERROR: You must input a nonempty file name. Exiting with status (1)\n");
		shouldExit = 1;
	}

	// exit with proper status
	if (shouldExit == 1) /* should exit with status (1) */
		exit(1);


	/* Check for proper file name extension */

	int nameLen = strlen(fname);
	// DEBUG
	printf("nameLen for %s is %d\n", fname, nameLen);
	int shouldExtend = 0;
	if (nameLen < 5) // too short to be valid name
		shouldExtend = 1;
	else if ( 0 ) // last 4 characters aren't ".wav"
		// DEBUG false in if statement
		shouldExtend = 1;

	// Append the .wav extension
	if (shouldExtend == 1)
		strcpy(fname, strcat(fname, ".wav") );

	// DEBUG (check user input)
	printf("You entered %lf Hz freq\n", freq);
	printf("You entered %lf s duration\n", duration);
	printf("You entered <%s> as your file name\n", fname);

	// Generate the file
	genFile(freq, duration, fname);

	return 0;
}

// I'll let you start on this function, Freitag

typedef struct {
		int16_t *sample; /* pointer to memory storing list of 16-bit signed samples */
}PCM; 

PCM *genSampleChunk(double duration)
{
	PCM *sampleList;

	if(!(sampleList = (PCM*)malloc(sizeof(PCM)))) /* if malloc can't allocate enough memory, return NULL */
	{
		return NULL;
	}

	if(!(sampleList->sample = (int16_t*)malloc(sizeof(int16_t) * 44100 * duration))) /* if malloc can't allocate enough memory, return NULL */
	{
		return NULL;
	}

	return sampleList;
}

PCM *genSampleList(double freq, double duration)
{
	PCM *sampleList; /* pointer to list of 16-bit samples */
	int i;			 /* counter for loop that generates consecutive 16-bit samples */

	sampleList = genSampleChunk(duration);

	for (i = 0; i < (44100 * duration); i++)
	{
		sampleList->sample[i] = sin(2 * PI * i / freq);
	}

	return sampleList;
}

void genFile(double freq, double duration, char* fname)
{
	int16_t sample = 44100;	//	Sample rate of audio (44.1 KHz)
	
	return; // DEBUG
}


void genWave(char* fname, unsigned long numSamples, short int* data,int sampleSize)
{

	return;
}
