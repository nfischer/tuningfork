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
#define PI (3.141592653589793)

void genFile(double freq, double time, char* fname);

int main()
{
	double freq, duration;
	char fname[50]; // arbitrary file name limit
	// fix arbitrary limit to be nonarbitrary

	// get user input
	printf("Input desired frequency (Hz): ");
	scanf_s("%lf", &freq);
	printf("Input desired duration (sec): ");
	scanf_s("%lf", &duration);
	printf("Enter desired file name: ");
	scanf_s("%s", fname);

	// DEBUG (check user input)
	printf("You entered %lf Hz freq\n", freq);
	printf("You entered %lf s duration\n", duration);
	printf("You entered <%s> as your file name\n", fname);

	// Generate the file
	genFile(freq, duration, fname);

	return 0;
}

//	I'll let you start on this function, Freitag

void genFile(double freq, double time, char* fname)
{
	int16_t sample = 44100;	//	Sample rate of audio (44.1 KHz)
	
	return; // DEBUG
}

//	Wave generator (references: https://ccrma.stanford.edu/courses/422/projects/WaveFormat/)

/* Notes:

    *	The default byte ordering assumed for WAVE data files is little-endian. Files written using the big-endian byte ordering scheme have the identifier RIFX instead of RIFF.
    *	The sample data must end on an even byte boundary. Whatever that means.
    *	8-bit samples are stored as unsigned bytes, ranging from 0 to 255. 16-bit samples are stored as 2's-complement signed integers, ranging from -32768 to 32767.
    *	There may be additional subchunks in a Wave data stream. If so, each will have a char[4] SubChunkID, and unsigned long SubChunkSize, and SubChunkSize amount of data.
    *	RIFF stands for Resource Interchange File Format. 
*/

void genWave(char* fname, unsigned long numSamples, short int* data,int sampleSize)
{
	//	RIFF (52 49 46 46)			(big endian)	(4 bytes)
	//	Chunksize (ie 2084)			(little endian)	(4 bytes)
	//	WAVE (57 41 56 45)			(big endian)	(4 bytes)

	//	fmt  (66 6d 74 20)			(big endian)	(4 bytes)
	//	Subchunk size (ie 16)		(little endian)	(4 bytes)
	//	Audio format (ie PCM = 1)	(little endian)	(2 bytes)
	//	Number of channels (ie 2)	(little endian)	(2 bytes)
	//	Sample rate (ie 22050)		(little endian)	(4 bytes)
	//	Byte rate (ie 88200)		(little endian)	(4 bytes)
	//	Block align (ie 4)			(little endian)	(2 bytes)
	//	Bits per sample (16)		(little endian)	(2 bytes)

	//	data (64 61 74 61)			(big endian)	(4 bytes)
	//	Subchunk size (ie 2048)		(little endian)	(4 bytes)
	//	Samples (actual audio data)	(little endian)	(2 bytes each)

	return;
}
