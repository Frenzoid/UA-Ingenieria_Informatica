
// gcc -o dekker Dekker.c -lpthread
// taskset -c 0 dekker

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <stdbool.h>

int I = 0;
int turno = 0;
bool critico[] = {false,false};

void *codigo_del_hilo(void *id)
{
    int k;
    int i = *(int *)id;
    int id1 = (i == 1) ? 0 : 1; // id de hilo
    int id2 = (i == 1) ? 1 : 0; // id de hilo
    for (k = 0; k < 100; k++)
    {
        critico[id1] = true;
        // protocolo de entrada
        while (critico[id2]) {
            if (turno == id2) {
                critico[id1] = false;
                while (turno != id1);
                critico[id1] = true;
            }
        }
        I = (I + 1) % 10;
        printf("En hilo %d, I=%d\n", i, I);

        // Salida
        critico[id1] = false;
        turno = id2;
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