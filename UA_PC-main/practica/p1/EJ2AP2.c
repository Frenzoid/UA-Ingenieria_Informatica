#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_HILOS 3

typedef struct {
    char c;
    int veces;
} EST_CHAR;

void imprimir(char c, int veces) {
    int i;

    for(i = 0; i < veces; i++)
        printf("%c", c);
    
    printf("\n");
}

void *codigo_del_hilo (void *id){

    switch(*(int *) id) {
        case 1: imprimir('A', 50);
        break;
        case 2: imprimir('B', 100);
        break;
        case 3: imprimir('C', 150);
        break;
    }
    
    pthread_exit (id);
}

int main(){
   pthread_t hilos[NUM_HILOS];
   int id[NUM_HILOS] = {1, 2, 3};
   int h;
   int error;
   int *salida;

   for(h = 0; h < NUM_HILOS; h++){
      error = pthread_create( &hilos[h], NULL, codigo_del_hilo, &id[h]);
      if (error){
        fprintf (stderr, "Error: %d: %s\n", error, strerror (error));
        exit(-1);
      }
   }


   for(h = 0; h < NUM_HILOS; h++){
      error = pthread_join(hilos[h], (void **)&salida);
      if (error) {
          fprintf (stderr, "Error: %d: %s\n", error, strerror (error));
      }
      else {
          printf ("Hilo %d terminado\n", *salida);
      }
   }
}