#!/bin/bash
# Author: Frenzoid
# This script launches the infinite loop, which takes a picture every $1 seconds and proceeds to process it with the python script.

# $1: time to wait until next loop.
# $2: path/name to give to the outpit image.
# $3: gaussianDistortion degree.

while :; do

    fswebcam --no-banner -r 1920x720 --png -0 $2;
    python3 ./preproc.py $2 $3;
    if [ $? -ne 0 ]; then
       echo "ERROR PPROCESSING IMAGE, BREAKING!"
       break
    fi
    
    echo "IMAGE PROCESSED, WAITIG $1 SECONDS UNTIL NEXT ITERATION!";
    sleep $1;

done;
