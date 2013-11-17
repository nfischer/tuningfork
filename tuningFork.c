/********************************************
Generates a .wav file with specified
duration, frequency, and other parameters

--- further description ---

Authors: Brandon Freitag and Nate Fischer
November 2013

********************************************/
#include <stdio.h>


void genFile(double freq, double time, char* fname);

int main()
{
	double freq, duration;
	char fname[50]; // arbitrary file name limit
	printf("Input desired frequency (Hz): ");
	scanf("%lf", &freq);
	printf("Input desired duration (sec): ");
	scanf("%lf", &duration);
	printf("Enter desired file name: ");
	scanf("%s", &fname);

	return 0;
}




void genFile(double freq, double time, char* fname)
{

	return; // DEBUG
}
