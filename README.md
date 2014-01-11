tuningfork
==========

Generates a .wav file of specified duration, frequency, filename, and
other parameters.

Files
-----

### tuningFork.c

The main file is tuningFork.c, a C file designed to create a .wav file
of specified duration, frequency, and filename. This takes user input
for these parameters from a prompt, checks for valid input, and then
creates the file if all parameters are valid.

### tune

This is a bash script that interfaces with an executable named tf
produced from the compilation of tuningFork.c. This will echo default
inputs into the executable's prompts, allowing users to bypass the slow
input prompts. Users can specify nondefault values for parameters with
options.

### compileTuningFork

This is our easier solution to makefiles. A simple bash script does the
job just as well (there's only one .c file), and it nicely synchronizes
our executable name across our different machines. This is intended
for use during development of the project, not the normal usage of the
finished project.

Usage
-----

### Using the executable tf
Example prompts and input:
```
$ ./tf
Input desired frequency (Hz): 440
Input desired duration (sec): 10
Enter desired file name: a.wav
$
```
This executable prompts for user input on frequency, duration, and file
name. Simply enter these values when prompted. Frequency and duration can
take decimal values with the precision of a double. Filename is currently
limited to 50 characters maximum.

### using the tune bash script
Example:
```
$ ./tune -n "other.wav"
$
```
This script interfaces with the tf executable file. It will compile it if
it doesn't already exist. This script, without options, will create a file
named "a.wav" that has duration 10 seconds and frequency A=440Hz.

You can change the default name, frequency, and/or duration with the
following options:
```
    -f                specify frequency (default = 440Hz)
    -d                specify time duration (default = 10s)
    -n                specify file name (default = A440.wav)
    -h, --help        display this help menu
```
