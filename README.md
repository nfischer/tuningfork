tuningfork
==========

[![Build Status](https://travis-ci.org/nfischer/tuningfork.svg?branch=master)]
(https://travis-ci.org/nfischer/tuningfork)

Generates a single-tone .wav file of specified duration, frequency, and
file name.

Build
-----

To build our project, please use a make command. The compile script is
deprecated.

```
$ make
```

Details
-------

### tuningFork.c

The main file is tuningFork.c, a C file designed to create a .wav file of
specified duration, frequency, and filename. This takes user input for
these parameters from a prompt, checks for valid input, and then creates
the file if all parameters are valid.

The .wav file is stored in memory until the file is written in order to
improve file I/O, so don't generate large files on systems where RAM is a
limitation.

Recently, a lookup table was added to minimize sin computations. This
bumped up performance a great deal. Now, on some systems, it can generate a
6000 second (100 minute) .wav file in under 15 seconds (under 3 on some
solid state drives). You can benchmark our program yourself!

Usage
-----

### Using the executable *tf*

Example prompts and input:

```
$ ./tf
Input desired frequency (Hz): 440
Input desired duration (sec): 10
Enter desired file name: a.wav
$
```

All the above is fairly self explanatory

### Using the *tune* bash script

Example:

```
$ ./tune -n "other.wav" # no output to terminal
```

This script interfaces with the tf executable file. This script, without
options, will create a file named "A440.wav" that has duration 10 seconds
and frequency A=440Hz.

You can change the default name, frequency, and/or duration with the
following options:

```
-f                specify frequency (default = 440Hz)
-d                specify time duration (default = 10s)
-n                specify file name (default = A440.wav)
-h, --help        display this help menu
```
