#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROCESOS 2

// Funcion del hijo/s.
void imprimirId(int id) {
  printf("id: %d\n", id);
  exit(id);
}

int main() {
  // Procesos hijos.
  int id[NUM_PROCESOS] = {1, 2}; // 2 procesos
  int pid;
  int salida;

  // Crear 5 procesos hijos y el proceso padre se dedica a esperar a que acabe.
  for (int p = 0; p < NUM_PROCESOS; p++) {
    pid = fork();

    if (pid == -1) { 
      // Fallo al crear proceso, permisos, memoria, etc.
      perror("Error al crear un proceso: ");
      exit(-1);
    } else if (pid == 0) 
        imprimirId(id[p]);
  }

  // Codigo del padre
  // Por cada proceso hijo, el padre se espera, y cuando acaba, imprime el pid del hijo que ha terminado y su estado de salida.
  // Desplazamos 8 bits porque el id se almacena en los bits 8 al 15.
  for (int p = 0; p < NUM_PROCESOS; p++) {
    pid = wait(&salida);
    printf("Proceso(pid=%d) con id = %x terminado y status = %d \n", pid, salida >> 8, WEXITSTATUS(salida)); 
  }
  return 0;
}