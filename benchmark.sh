#!/bin/bash

# A shell script to bench mark the tuningfork executable

# check for appropriate files
if [ ! -f benchmark ]; then
  echo "Error: you must run this script from the tuningfork directory." >&2
  exit 1
elif [ ! -f tune ]; then
  echo "Error: The tune shell script could not be found" >&2
  exit 1
fi

# check for time utility
hasTimeUtility=$(which time 2>/dev/null)

if [ -z "${hasTimeUtility}" ]; then
  # There is no time utility on the system
  echo "You must have the utility 'time' to run this program" >&2
fi

# Begin benchmarks
echo "1 minute file"
(time -p ./tune -d 60 -n 60sec.wav) 2>&1
echo "10 minute file"
out=$(time -p ./tune -d 600 -n 600sec.wav 2>&1)
echo "$out"
lastTime=$(echo "$out" | grep 'real')
lastTime=$(echo "${lastTime}" | sed 's/^.* \([0-9]\+\).*$/\1/')

if [[ "$1" == "-f" ]] || [[ "${lastTime}" -le 3 ]]; then
  echo "100 minute file"
  (time -p ./tune -d 6000 -n 6000sec.wav) 2>&1
else
  echo "To run the 100 minute benchmark (1 GB), supply the -f flag"
fi