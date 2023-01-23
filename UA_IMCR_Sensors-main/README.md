# IMCR-Sensores
This repository contains the code relative to the sensoring part of the IMCR project.

The main goal of the project is to create a system that auto detects available parking lots live on the streets, and notifies the nearby drivers about it.

This script `preproc.py` takes a picture of the available camera, pre-processes it, and sends it to the data-analisys system.

## How to run

The main script is `preproc.py`.

It takes 2 arguments:
- The path to the image to process (string).
- The degree of distortion (integer).

Examples:
- `python3 preproc.py [image_path] [distortion_degree]`
- `python3 preproc.py dataset/parking.png 5`

## Output
The expected output is an image processed with all the filters needed.

## Other files
The other bash scripts are for automatic deployment.
- `screen_script.sh`: Infinite loop that takes a picture and processes it.
- `start.sh`: Script that installs the required packages and starts the loop in background (you can log-out after this).

## Test files
Theres an image inside the `dataset` folder.
You can use that image to test if the processing you need is adequate.

## Installation
To run the script, the library python3-opencv must be installed on the system, in addition to the python3 binary.

