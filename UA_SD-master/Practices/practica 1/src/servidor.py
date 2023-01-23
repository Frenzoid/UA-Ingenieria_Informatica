import socket
import os
import sys
from _thread import start_new_thread


def clientProcess(c):
    while True:

        command = c.recv(1024).decode('utf-8')

        if command == "exit":
            print("Closing Connection.")
            c.send("EXIT".encode('utf-8'))
            c.close()
            break

        try:
            response = run(command)
            print("SAY: \n", response)
            c.send(response.encode('utf-8'))
        except ValueError:
            print(ValueError)
            c.send("An issue happend while executing your command.".encode('utf-8'))


def Main():

    if len(sys.argv) < 3:
        print("Missing parmeters!")
        exit()

    host = sys.argv[1]
    port = int(sys.argv[2])
    
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    s.bind((host, port))
    print("Socket binded to port: ", port)

    s.listen(5)
    print("Socket in listening mode!")

    while True:
        c, addr = s.accept()
        print('New connection incomming from:', addr[0], ':', addr[1])
        start_new_thread(clientProcess, (c,))


def run(command):
    return os.popen(command).read() or "Command: '" + command + "' executed. Yet, no output was returned."


Main()