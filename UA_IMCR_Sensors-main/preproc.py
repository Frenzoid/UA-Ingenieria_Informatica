import numpy
import cv2
import requests
import sys
import os.path
import socket


class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


class exit_codes:
    EX_OK = 0
    EX_USAGE = 64
    EX_NOINPUT = 66
    EX_TIMEOUT = 124
    EX_GENERIC = 1


class server_addresses:
    DEFAULT = "http://wewewew.com/apirest"


def checkArguments(arguments):
    if len(arguments) != 3:
        print(bcolors.FAIL,
              "Image missing and / or degree of distortion argument missing. \n",
              bcolors.HEADER,
              "Example:",
              bcolors.OKBLUE,
              "python3", arguments[0], "[image_path] [distortion_degree]",
              bcolors.ENDC)
        sys.exit(exit_codes.EX_USAGE)


def checkFile(file):

    if not os.path.isfile(file):
        print(bcolors.FAIL,
              "Image missing:\n",
              bcolors.WARNING,
              file,
              bcolors.ENDC)

        sys.exit(exit_codes.EX_NOINPUT)


def checkDistortion(distortion):

    distortion = int(distortion) if distortion.isnumeric() else None

    if distortion is None or distortion < 1 or (distortion % 2) == 0:
        print(bcolors.FAIL,
              "Distortion degree is incorrect: \n",
              bcolors.HEADER,
              "The distortion degree must be greater than 0 and an odd number.",
              bcolors.ENDC)
        sys.exit(exit_codes.EX_USAGE)


def gaussianBlurProcess(image, distortion):
    return cv2.GaussianBlur(
        image, (distortion, distortion), cv2.BORDER_DEFAULT)


def sendBinaryData(path_data, camNumber):

    timeoutTime = 30

    file = {
        'media': open(path_data, 'rb'),
    }

    values = {
        'camname': socket.gethostname()
    }

    try:
        response = requests.post(server_addresses.DEFAULT,
                                 files=file, data=values, timeout=timeoutTime)
        response.raise_for_status()
    except requests.exceptions.HTTPError as errh:
        print("Http Error:", errh)
    except requests.exceptions.ConnectionError as errc:
        print("Error Connecting:", errc)
    except requests.exceptions.Timeout as errt:
        print("Timeout Error:", errt)
    except requests.exceptions.RequestException as err:
        print("Oops: Something Else", err)


def main():
    # Checks the arguments, and inputs.
    checkArguments(sys.argv)
    checkFile(sys.argv[1])
    checkDistortion(sys.argv[2])

    # Save the arguments on variables for easier handling.
    imagePath = sys.argv[1]
    distortion = int(sys.argv[2])

    # Load the image.
    binaryImage = cv2.imread(imagePath)

    # Process the image.
    processedBinaryImage = gaussianBlurProcess(binaryImage, distortion)

    # Save the processed image on the same path, overwritting the original image.
    cv2.imwrite(imagePath, processedBinaryImage)

    # Sends the processed image to the data-analisys system. ( URL pending ).
    # sendBinaryData(imagePath)

    # Good bye, have a great day!
    sys.exit(exit_codes.EX_OK)


main()
