/* PROCESOS */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROCESOS 5

int I = 0;

// Funcion del hijo/s.
void codigo_del_proceso(int id) {
  int i;

  // Imprimir 50 veces el valor de i y I y el id del proceso hijo.
  for (i = 0; i < 50; i++)
    printf("Proceso(id=%d): i = %d, I = %d\n", id, i, I++);

  exit(id);
}

int main() {
  int p;
  // Procesos hijos.
  int id[NUM_PROCESOS] = {1, 2, 3, 4, 5};
  int pid;
  int salida;

  // Crear 5 procesos hijos y el proceso padre se dedica a esperar a que acabe.
  for (p = 0; p < NUM_PROCESOS; p++) {
    pid = fork();

    if (pid == -1) { 
      // Fallo al crear proceso, permisos, memoria, etc.
      perror("Error al crear un proceso: ");
      exit(-1);
    } else if (pid == 0) 
      codigo_del_proceso(id[p]);
  }

  // Codigo del padre
  // Por cada proceso hijo, el padre se espera, y cuando acaba, imprime el pid del hijo que ha terminado.
  // Desplazamos 8 bits porque el id se almacena en los bits 8 al 15.
  for (p = 0; p < NUM_PROCESOS; p++) {
    pid = wait(&salida);
    printf("Proceso(pid=%d) con id = %x terminado y status = %d \n", pid, salida >> 8, WEXITSTATUS(salida)); 
  }
  return 0;
}