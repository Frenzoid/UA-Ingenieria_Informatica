// P7 - Practicas de Programación Concurrente 
// Problema barbería
// Elvi Mihai Sabau Sabau - 51254875L
// Compilación: gcc -o barberia barberia.c -lpthread

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <semaphore.h>

const int BARBEROS = 3;
const int CLIENTES = 25;

sem_t max_capacidad;            // controla la capacidad de clientes que tiene la barbería. Inicializado a 20
sem_t sofa;                     // controla el uso del sofá de los clientes. Inicializado a 4
sem_t silla_barbero;            // controla las sillas que usan los barberos para cortar el pelo. Inicializado a 3
sem_t cliente_listo;            // este semáforo sirve para indicar que el cliente ya esta sentado en la silla.
sem_t terminado;                // indica que el corte de pelo ha terminado. Inicializado a 0.
sem_t dejar_silla_barbero;      // usado cuando el cliente abandona la silla después del corte de pelo. Inicializado a 0.
sem_t pago;                     // controla el pago de los clientes. Inicializado a 0.
sem_t recibo;                   // entrega al cliente de un recibo de pago, indica que se ha aceptado el pago. Inicializado a 0.
sem_t coord;                    // controla la ocupación de los barberos, tanto para cortar el pelo como para cobrar. Inicializado a 3.

// Basandome en el pseudocodigo proprcionado, he desarollado las siguienntes funciones.

void cortar_pelo(void *id) {
    // cortar pelo, esperamos 5 segundos.
    printf("Barbero %d cortando pelo\n", *(int *)id);
    sleep(5);
    printf("Barbero %d ha acabado de cortar el pelo\n", *(int *)id);

}

void cobrar() {
    printf("Cobrando\n");
    sleep(1);
}

void *barbero(void *id) {

    while (1) {
        sem_wait(&cliente_listo); 
        sem_wait(&coord);

        cortar_pelo(id);

        sem_post(&coord);
        sem_post(&terminado);
        sem_wait(&dejar_silla_barbero);
        sem_post(&silla_barbero);
    }
    pthread_exit(id);
}

void *cajero(void *id) {

    while (1) {
        sem_wait(&pago);
        sem_wait(&coord);

        cobrar();

        sem_post(&coord);
        sem_post(&recibo);
    }
    pthread_exit(id);
}

void *cliente(void * id) {

    int i = *(int *) id;

    sem_wait(&max_capacidad);

    printf("El cliente %d entra en la barberia\n", i);

    sem_wait(&sofa);
    printf("El cliente %d se sienta en el sofa a esperar\n", i);
    sem_wait(&silla_barbero);

    printf("El cliente Cliente %d se levanta del sofa\n", i);
    sem_post(&sofa);

    printf("El cliente %d se sienta en la silla del barbero\n", i);

    sem_post(&cliente_listo);
    sem_wait(&terminado);

    printf("El cliente %d se levanta de la silla del barbero\n", i);
    sem_post(&dejar_silla_barbero);

    printf("El cliente %d realiza el pago\n", i);
    sem_post(&pago);
    sem_wait(&recibo);

    printf("El cliente %d sale de la barbería\n", i);
    sem_post(&max_capacidad);

    pthread_exit(id);
}

int main() {

    pthread_t hilos_clientes[CLIENTES];
    pthread_t hilos_barberos[BARBEROS];
    pthread_t hilo_cajero;
    int id_clientes[CLIENTES];
    int id_barberos[BARBEROS];

    int error;
    int *salida;
    
    // Inicializacion de semaforos.
    sem_init(&max_capacidad, 0, 20);
    sem_init(&sofa, 0, 4);
    sem_init(&silla_barbero, 0, 3);
    sem_init(&cliente_listo, 0, 0);
    sem_init(&terminado, 0 , 0);
    sem_init(&dejar_silla_barbero, 0 , 0);
    sem_init(&pago, 0 , 0);
    sem_init(&recibo, 0 , 0);
    sem_init(&coord, 0 , 3);


    // Creamos los barberos.
    for (int hilo = 0; hilo < BARBEROS; hilo++) {
        id_barberos[hilo] = hilo;
        error = pthread_create(&hilos_barberos[hilo], NULL, barbero, &id_barberos[hilo]);
        if (error) {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
            exit(-1);
        }
    }

    // Creamos los clientes.
    for (int hilo = 0; hilo < CLIENTES; hilo++) {
        id_clientes[hilo] = hilo;
        error = pthread_create(&hilos_clientes[hilo], NULL, cliente, &id_clientes[hilo]);
        if (error) {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
            exit(-1);
        }
    }

    // Creamos el cajero.
    int id_cajero;
    pthread_create(&hilo_cajero, NULL, cajero, &id_cajero);

    // El cliente acaba.
    for (int hilo = 0; hilo < CLIENTES; hilo++) {
        error = pthread_join(hilos_clientes[hilo], (void **) &salida);
        if (error) fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
    }

    // Cerramos todos los semaforos.
    sem_destroy(&max_capacidad);
    sem_destroy(&sofa);
    sem_destroy(&silla_barbero);
    sem_destroy(&cliente_listo);
    sem_destroy(&terminado);
    sem_destroy(&dejar_silla_barbero);
    sem_destroy(&pago);
    sem_destroy(&recibo);
    sem_destroy(&coord);

    return 0;
}