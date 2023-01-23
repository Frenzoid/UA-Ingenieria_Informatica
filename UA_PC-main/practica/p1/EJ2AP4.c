#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROCESOS 3

void imprimir(char c) {
  for(int i = 0; i < 5; i++)
      printf("%c ", c);

  printf("\n");
}

int main() {
  char id[NUM_PROCESOS] = {'A', 'B', 'C'};
  int p;
  int pid;
  int salida;

  for (int p = 0; p < NUM_PROCESOS; p++) {
    pid = fork();
    if (pid == -1) {
      perror("Error al crear un proceso: ");
      exit(-1);
    } else if (pid == 0) {
        imprimir(id[p]);
        exit(id[p]);
    }
  }

  // Codigo del padre
  for (int p = 0; p < NUM_PROCESOS; p++)
    pid = wait(&salida);

  return 0;
}
