tuningfork
==========

Generates a .wav file of specified duration, frequency, filename, and
other parameters.

Files
=====

tuningFork.c
------------
The main file is tuningFork.c, a C file designed to create a .wav file
of specified duration, frequency, and filename. This takes user input
for these parameters from a prompt, checks for valid input, and then
creates the file if all parameters are valid.

tune
----
This is a bash script that interfaces with an executable named tf
produced from the compilation of tuningFork.c. This will echo default
inputs into the executable's prompts, allowing users to bypass the slow
input prompts. Users can specify nondefault values for parameters with
options.



