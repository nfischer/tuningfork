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
	genFile(freq, time, fname);

	return 0;
}



// I'll let you start on this function, Freitag

void genFile(double freq, double time, char* fname)
{

	return; // DEBUG
}
