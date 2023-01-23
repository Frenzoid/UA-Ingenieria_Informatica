// P5 - Practicas de Programación Concurrente 
// Lectores/Escritores con prioridad de lectura
// Elvi Mihai Sabau Sabau - 51254875L
// Compilación : gcc -o p5 p5.c -lpthread

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>

sem_t mx, writer;
int  LECTORES = 10, ESCRITORES = 5, readers = 0, recurso = -1;

void reader_lock() {
    sem_wait(&mx);
    readers++;
    
    if (readers == 1) sem_wait(&writer);
    sem_post(&mx);
}

void reader_unlock() {
    sem_wait(&mx);
    readers--;

    if (readers == 0) sem_post(&writer);
    sem_post(&mx);
}


void *lector(void *id) {

    for(int i = 0; i < LECTORES; i++) {
        reader_lock();
        printf("El lector %d ha leido un valor de %d\n", *(int*) id, recurso);
        reader_unlock();
        // Añadimos un retardo para simular lecturas de distinto tiempo.
        usleep(rand()%5);
    }

    pthread_exit(id);
}

void *escritor(void *id) {

    for(int i = 0; i < ESCRITORES; i++) {
        sem_wait(&writer);
        printf("El escritor %d ha actualizado el recurso\n", *(int*) id);
        recurso = *(int*) id;
        sem_post(&writer);
        // Añadimos un retardo para simular escrituras de distinto tiempo.
        usleep(rand()%5); 
    }
    pthread_exit(id);
}

void crear_hilos(pthread_t hilos[], int id[], int num, void *(*func) (void*)) {

    for (int i = 0; i < num; i++) {
        id[i] = i;
        int error = pthread_create(&hilos[i], NULL, func, &id[i]);
        if (error) {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
            exit(-1);
        }
    }
}

void terminar_hilos(pthread_t hilos[], int num) {
    
    int *salida;

    for (int i = 0; i < num; i++) {
        int error = pthread_join(hilos[i], (void **) &salida);
        if (error) fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
    }
}

int main() {
    pthread_t tidlector[LECTORES], tidescritor[ESCRITORES];
    int id_lec[LECTORES], id_esc[ESCRITORES];
    
    sem_init(&mx, 0, 1);
    sem_init(&writer, 0, 1);

    crear_hilos(tidescritor, id_esc, ESCRITORES, escritor);
    crear_hilos(tidlector, id_lec, LECTORES, lector);

    terminar_hilos(tidlector, LECTORES);
    terminar_hilos(tidescritor, ESCRITORES);

    sem_destroy(&mx);
    sem_destroy(&writer);

    return 0;
}