import socket
import sys

def Main():
    
    if len(sys.argv) < 3:
        print("Missing parameters.")
        exit()

    host = sys.argv[1]
    port = int(sys.argv[2])
    
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))

    while True:

        command = input('Insert command: ')

        if command == "exit":
            s.send(command.encode('utf-8'))
            response = s.recv(1024).decode('utf-8')

            if "EXIT" == response:
                break

        s.send(command.encode('utf-8'))
        response = s.recv(1024).decode('utf-8')
        print(response)

    s.close()


Main()