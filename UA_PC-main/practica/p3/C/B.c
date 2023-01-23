/**
   $hilos
   Compilación: gcc -o int2 Intento2.c -lpthread
**/

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int I = 0;
bool critico[] = {false, false};

void *codigo_del_hilo(void *id)
{
    int i = *(int *)id;
    int k;

    int hilo1 = (i == 1) ? 0 : 1; // id de hilo
    int hilo2 = (i == 1) ? 1 : 0; // id de hilo

    for (k = 0; k < 100; k++) {
        // protocolo de entrada
        while (critico[hilo2]);
        critico[hilo1] = true;

        // Sección crítica
        I = (I + 1) % 10;
        printf("En hilo %d, I=%d\n", i, I);
        // protocolo salida

        critico[hilo1] = false;
        // Resto
    }

    pthread_exit(id);
}

int main()
{
    int h;
    pthread_t hilos[2];
    int id[2] = {1, 2};
    int error;
    int *salida;
    for (h = 0; h < 2; h++)
    {
        error = pthread_create(&hilos[h], NULL, codigo_del_hilo, &id[h]);
        if (error)
        {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
            exit(-1);
        }
    }
    for (h = 0; h < 2; h++)
    {
        error = pthread_join(hilos[h], (void **)&salida);
        if (error)
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
        else
            printf("Hilo %d terminado\n", *salida);
    }
}