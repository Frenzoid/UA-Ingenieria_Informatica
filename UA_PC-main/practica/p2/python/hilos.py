import threading

THREADS = 5
MAX_COUNT = 50000
CONTADOR = 0

# Funcion del hilo.
def thread():

    global CONTADOR
    print("Hilo {}".format(threading.current_thread().name))
    
    for i in range(MAX_COUNT):
        CONTADOR += 1
        print(CONTADOR)


def main():
    threads = []
    
    # Create new threads
    for i in range(THREADS):

        t = threading.Thread(target = thread)
        threads.append(t)
        t.start()

    # Wait for all threads to complete
    for t in threads:
        t.join()
        
    print("Contador: {} == {}\n".format(CONTADOR, MAX_COUNT))
        
if __name__ == "__main__":
    main()
