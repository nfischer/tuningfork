/***********************************************************
*                                                          *
* Generates a .wav file with specified                     *
* duration, frequency, and other parameters                *
*                                                          *
* --- further description ---                              *
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

const double PI = 3.141592653589793;


void genFile(double freq, double time, char* fname);
void checkInputFormat(double freq, double duration, char* fname);

void debugOutput(double freq, double duration, char* fname)
{
    fprintf(stderr, "You entered %lf Hz freq\n", freq);
    fprintf(stderr, "You entered %lf s duration\n", duration);
    fprintf(stderr, "You entered <%s> as your file name\n", fname);
    return;
}


int main()
{
    double freq, duration;
    char fname[255]; // longest name supported on linux

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

    checkInputFormat(freq, duration, fname);

    // DEBUG (check user input)
    debugOutput(freq, duration, fname);

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
    if (freq <= MIN_FREQ || freq > MAX_FREQ)
    {
        fprintf(stderr,"ERROR: You must input a frequency value in the range %d < frequency <= %d. Exiting with status (1)\n", (int)MIN_FREQ, (int)MAX_FREQ);
        shouldExit = 1;
    }

    // duration / length
    if (duration <= MIN_DURATION || duration > MAX_DURATION)
    {
        fprintf(stderr,"ERROR: You must input a duration value in the range %d < duration <= %d. Exiting with status (1)\n", (int)MIN_DURATION, (int)MAX_DURATION);
        shouldExit = 1;
    }

    // empty string name
    if (strcmp(fname, "") == 0) /* empty string is invalid */
    {
        fprintf(stderr,"ERROR: You must input a nonempty file name. Exiting with status (1)\n");
        shouldExit = 1;
    }

    int nameLen = strlen(fname);
    /* Catches the zero byte in the file name */

    // exit with proper status
    if (shouldExit == 1) /* should exit with status (1) */
        exit(1);

    /* Check for proper file name extension */

    char nameV = fname[nameLen-1];
    char nameA = fname[nameLen-2];
    char nameW = fname[nameLen-3];
    char nameP = fname[nameLen-4];
    int shouldExtend;
    if (nameLen > 4) // long enough to be valid name
    {
        if (nameP == '.' && nameW == 'w' && nameA == 'a' && nameV == 'v') // last 4 characters are ".wav"
            shouldExtend = 0; // File name meets requirements and does not need .wav appending
        else
            shouldExtend = 1;
    }
    else // short enough that it must need an extension
        shouldExtend = 1;

    // Append the .wav extension
    if (shouldExtend == 1)
        strcat(fname, ".wav");

    return;
}

void genFile(double freq, double duration, char* fname)
{
    const int SAMPLE_RATE = 44100;
    //duration = 1; /* Hard-coded to 1 second */

    /**************************
    * Calculate subchunk2Size *
    **************************/

    // int should be 32 bits on most systems
    //                = NumSamples * NumChannels * BitsPerSample/8
    int subchunk2Size = (duration * SAMPLE_RATE) * 2 * 16 / 8;

    int scx = subchunk2Size; // scx will be modified

    // char is 8 bits (one byte)
    // 256 is 2 ^ 8
    char B4 = scx % 256;
    scx = scx / 256;
    char B3 = scx % 256;
    scx = scx / 256;
    char B2 = scx % 256;
    scx = scx / 256;
    char B1 = scx % 256;

    /**************************
    * Calculate ChunkSize     *
    **************************/

    int chunkSize = 36 + subchunk2Size;

    int cx = chunkSize; // cx will be modified

    // char is 8 bits (one byte)
    // 256 is 2 ^ 8
    char C4 = cx % 256;
    cx = cx / 256;
    char C3 = cx % 256;
    cx = cx / 256;
    char C2 = cx % 256;
    cx = cx / 256;
    char C1 = cx % 256;

    // char is 8 bits, and all these are 8 bits
    char HEADER[46] = {0x52, 0x49, 0x46, 0x46,   C4,   C3,   C2,   C1,
                       0x57, 0x41, 0x56, 0x45, 0x66, 0x6D, 0x74, 0x20,
                       0x12, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00,
                       0x44, 0xAC, 0x00, 0x00, 0x10, 0xB1, 0x02, 0x00,
                       0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x64, 0x61,
                       0x74, 0x61,   B4,   B3,   B2,   B1};

    FILE *OutFile;


    OutFile = fopen(fname, "w");
    if (OutFile != NULL)
    {
        int i; // iterator

        for(i = 0; i < 46; i++)
        {
            fputc(HEADER[i], OutFile);
        }

        /* 16-bit integer to designate amplitude of wave form */
        int16_t sample[1]; 
        int max_volume = 0x7FFF;
        for (i = 0; i < (SAMPLE_RATE * duration); i++)
        {
            sample[0] = max_volume * sin(2 * PI * ((double) i/SAMPLE_RATE) * freq);
            fwrite(sample, 2, 1, OutFile); /* Left channel */
            fwrite(sample, 2, 1, OutFile); /* Right channel */
        }
    }
    
    fclose(OutFile);
}
