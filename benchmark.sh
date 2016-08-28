#!/bin/bash

# A shell script to bench mark the tuningfork executable

set -e

# check for time utility
if ! which time &>/dev/null; then
  echo "You must have the utility 'time' to run this program" >&2
  exit 1
fi

# change to the working directory
cd "$(dirname "$0")"

# build files
make

# Begin benchmarks
echo "1 minute file"
time -p ./tf -f 440 -d 60   -n 60sec.wav   2>&1
echo "10 minute file"
time -p ./tf -f 440 -d 600  -n 600sec.wav  2>&1
echo "100 minute file"
time -p ./tf -f 440 -d 6000 -n 6000sec.wav 2>&1
