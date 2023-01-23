// Cuentanumeros.
// ELVI MIAHI SABAU SABAU - 51254875L
// Compilacion: gcc -pthread cuentanumeros.c  -o cuentanumeros

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_HILOS 10

// Struct de argumentos para la funcion de los hilos
typedef struct {
  int id_hilo;
  char *nombre_archivo;
} thread_args;

// Funcion que ejecutan los hilos.
void *cuenta_digito(void *arg) {
  thread_args *args = (thread_args *)arg;
  int id_hilo = args->id_hilo;
  char *nombre_archivo = args->nombre_archivo;

  // Abre el archivo.
  FILE *archivo = fopen(nombre_archivo, "r");
  if (archivo == NULL) {
    printf("Error al abrir el archivo.\n");
    pthread_exit(NULL);
  }

  // Cuenta las veces que aparece el numero.
  int veces = 0;
  int ch;
  while ((ch = fgetc(archivo)) != EOF) if (ch == id_hilo + '0') veces++;

  // Obten el tamanyo del archivo.
  fseek(archivo, 0, SEEK_END);
  long tamanyo = ftell(archivo);

  // Imprimo el resultado.
  printf("Numero de veces que %d aparece en el fichero: %d - %f%%\n", id_hilo, veces, 100.0 * veces / tamanyo );

  // Cierro el archivo.
  fclose(archivo);
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  // Compruebo si el archivo ha sido pasado por parametro.
  if (argc != 2) {
    printf("Uso: %s <nombre_archivo>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char *nombre_archivo = argv[1];

  // Creo el array de hilos y los argumentos.
  pthread_t hilos[NUM_HILOS];
  thread_args args[NUM_HILOS];

  // Arrancamos los hilos
  for (int i = 0; i < NUM_HILOS; i++) {
    args[i].id_hilo = i;
    args[i].nombre_archivo = nombre_archivo;

    int result = pthread_create(&hilos[i], NULL, cuenta_digito, (void *)&args[i]);

    if (result != 0) {
      printf("Error creando el hilo %d\n", i);
      exit(EXIT_FAILURE);
    }
  }

  // Espero a que todos los hilos acaben
  for (int i = 0; i < NUM_HILOS; i++) {
    int result = pthread_join(hilos[i], NULL);
    if (result != 0) {
      printf("Error, hilo %d acabado con errores\n", i);
      exit(EXIT_FAILURE);
    }
  }

  return 0;
}