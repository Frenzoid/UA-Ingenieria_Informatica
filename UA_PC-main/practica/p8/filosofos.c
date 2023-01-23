// P7 - Practicas de Programación Concurrente 
// Problema de la comida de los filósofos con monitores
// Elvi Mihai Sabau Sabau - 51254875L
// Compilación: gcc -o filosofos filosofos.c comida.c -lpthread

#include "comida.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define TIEMPO_PENSAR 3
#define TIEMPO_COMER 5

#define VECES_COME 5

mesa_t *mesa;

void pensar(int id) {
    printf("El filosofo %d esta pensando\n", id);
    sleep(TIEMPO_PENSAR);
    printf("El filosofo %d ha dejado de pensar\n", id);
}

void comer(int id) {
    printf("El filosofo %d esta comiendo\n", id);
    sleep(TIEMPO_COMER);
    printf("El filosofo %d ya ha comido\n", id);
}

void *filosofo(void * id) {

    int i = *(int *) id;

    for (int hilo = 0; hilo < VECES_COME; hilo++) {
        pensar(i);
        coger_palillo(mesa, i);
        comer(i);
        dejar_palillo(mesa, i);
    }

    pthread_exit(id);
}

int main(){
    pthread_t thFil[NUM_FILOSOFOS];
    int filosofos[NUM_FILOSOFOS];

    int error;
    int *salida;

    // Creamos la mesa ( monitor ), y la inicializamos.
    mesa_t mesa_monitor = INIT_MESA;
    mesa = &mesa_monitor;

    // Creamos los filosofos.
    for (int hilo = 0; hilo < NUM_FILOSOFOS; hilo++) {
        filosofos[hilo] = hilo;
        error = pthread_create(&thFil[hilo], NULL, filosofo, &filosofos[hilo]);
        if (error) {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
            exit(-1);
        }
    }

    // Esperamos a que terminen los filosofos.
    for (int hilo = 0; hilo < NUM_FILOSOFOS; hilo++) {
        error = pthread_join(thFil[hilo], (void **)&salida);
        if (error) fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
    }

    return 0;
}