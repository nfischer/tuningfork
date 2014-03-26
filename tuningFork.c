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
#define PI (3.141592653589793)

/* Global constants */
const double MIN_FREQ = 0;
const double MAX_FREQ = 22050; /* 22050 Hz */
const double MIN_DURATION = 0;
const double MAX_DURATION = 60 * 100; /* 100 minutes */


void genFile(double freq, double time, char* fname);

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

    int shouldExit = 0;
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

    int nameLen = strlen(fname);
    /* Catches the zero byte in the file name */


    int i; // iterator
    for(i=0; i < nameLen; i++)
    {
        if(fname[i] == '/')
        {
            fprintf(stderr,"ERROR: Invalid character(s) in file name. Exiting with status (1)\n");
            shouldExit = 1;
            break;
        }
    }
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
    else
        shouldExtend = 1;

    // Append the .wav extension
    if (shouldExtend == 1)
        strcat(fname, ".wav");

    // DEBUG (check user input)
    debugOutput(freq, duration, fname);

    // Generate the file
    genFile(freq, duration, fname);

    return 0;
}

//  I'll let you start on this function, Freitag

void genFile(double freq, double time, char* fname)
{
    //int16_t sample = 44100;   //  Sample rate of audio (44.1 KHz)

    return; // DEBUG
}


void genWave(char* fname, unsigned long numSamples, short int* data,int sampleSize)
{

    return;
}
