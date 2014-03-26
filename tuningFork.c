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

int16_t HEADER[46] = {0x52, 0x49, 0x46, 0x46, 0xF6, 0xCC, 0x02, 0x00,
                      0x57, 0x41, 0x56, 0x45, 0x66, 0x6D, 0x74, 0x20,
                      0x12, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00,
                      0x44, 0xAC, 0x00, 0x00, 0x10, 0xB1, 0x02, 0x00,
                      0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x64, 0x61,
                      0x74, 0x61, 0x10, 0xB1, 0x02, 0x00};

/*const char* HEADER_ChunkID = "\x52\x49\x46\x46";
const char* HEADER_Chunksize = "\xF6\xCC\x02\x00";
const char* HEADER_Format = "\x57\x41\x56\x45";
const char* HEADER_Subchunk1ID = "\x66\x6D\x74\x20";
const char* HEADER_SubchunkSize = "\x12\x00\x00\x00";
const char* HEADER_AudioFormat = "\x01\x00";
const char* HEADER_Channels = "\x02\x00";
const char* HEADER_SampleRate = "\x44\xAC\x00\x00";
const char* HEADER_ByteRate = "\x10\xB1\x02\x00";
const char* HEADER_BlockAlign = "\x04\x00";
const char* HEADER_BitsPerSample = "\x10\x00";
const char* HEADER_Subchunk2ID = "\x64\x61\x74\x61";
const char* HEADER_Subchunk2Size = "\x10\xB1\x02\x00";*/


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
    FILE *OutFile;

    duration = 1; /* Hard-coded to 1 second */

    OutFile = fopen(fname, "w");
    if (OutFile != NULL)
    {
        int i; // iterator

        for(i = 0; i < 46; i++)
        {
            fputc(HEADER[i], OutFile);
        }
        /*fputs(HEADER_ChunkID, OutFile);
        fputs(HEADER_Chunksize, OutFile);
        fputs(HEADER_Format, OutFile);
        fputs(HEADER_Subchunk1ID, OutFile);
        fputs(HEADER_SubchunkSize, OutFile);
        fputs(HEADER_AudioFormat, OutFile);
        fputs(HEADER_Channels, OutFile);
        fputs(HEADER_SampleRate, OutFile);
        fputs(HEADER_ByteRate, OutFile);
        fputs(HEADER_BlockAlign, OutFile);
        fputs(HEADER_BitsPerSample, OutFile);
        fputs(HEADER_Subchunk2ID, OutFile);
        fputs(HEADER_Subchunk2Size, OutFile);*/

        /* 16-bit integer to designate amplitude of wave form */
        int16_t sample; 
        int max_volume = 0x7FFF;
        for (i = 0; i < (44100 * duration); i++)
        {
            sample = max_volume * sin(2 * PI * (double) i / freq);
            //printf("%d\n", sample);
            fputc(sample, OutFile); /* Left channel */
            fputc(sample, OutFile); /* Right channel */

        }
    }
    
    fclose(OutFile);
}
