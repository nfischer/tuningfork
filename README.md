# TuningFork

[![Travis](https://img.shields.io/travis/nfischer/tuningfork.svg?style=flat-square)](https://travis-ci.org/nfischer/tuningfork)

Generates a single-tone .wav file of specified duration, frequency, and
file name.

## Install

```bash
$ git clone https://github.com/nfischer/tuningfork.git
$ cd tuningfork/
$ make # this creates the binary
```

From there, you'll have to copy the binary manually to your `PATH`, or just use
a full path to the project location.

## Details

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

## Usage

### Using the `tf` binary

Example prompts and input:

```
$ ./tf
Input desired frequency (Hz): 440
Input desired duration (sec): 10
Enter desired file name: a.wav
$
```

### Using the `tune` bash script

Example:

```
$ ./tune -n "other.wav" # no output to terminal
```

This script interfaces with the tf executable file. This script, without
options, will create a file named "A440.wav" that has duration 10 seconds
and frequency A=440Hz.

You can change the default name, frequency, and/or duration with the
following options:

| Option         | Description           | Default    |
| -------------- | --------------------- | ---------- |
| `-f`           | Specify frequency     | 440Hz      |
| `-d`           | Specify time duration | 10 sec     |
| `-n`           | Specify file name     | "A440.wav" |
| `-h`, `--help` | Display the help menu |            |
