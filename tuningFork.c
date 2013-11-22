/********************************************
Generates a .wav file with specified
duration, frequency, and other parameters

--- further description ---

Authors: Brandon Freitag and Nate Fischer
November 2013

********************************************/
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define PI 3.141592653

int main()
{
	double freq, duration;
	char fname[50]; // arbitrary file name limit

	// get user input
	printf("Input desired frequency (Hz): ");
	scanf("%lf", &freq);
	printf("Input desired duration (sec): ");
	scanf("%lf", &duration);
	printf("Enter desired file name: ");
	scanf("%s", fname);

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
}
