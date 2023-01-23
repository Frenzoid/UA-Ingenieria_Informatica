// Elvi Mihai Sabau Sabau - 51254875L

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
  // Revisamos que haya el numero correcto de argumentos.
  if (argc <= 2)
  {
    perror("Se deben pasar 2 argumentos: ./hijos x y");
    exit(1);
  }

  // Usamos punteros ya que los valores se pueden compartir entre los hijos
  int *pidx, *pidy;
  int shmid_x, shmid_y;
  int x, y, pid, i, j;

  if (argc == 3)
  {
    x = atoi(argv[1]);
    y = atoi(argv[2]);

    // Reservamos memoria.
    //  IPC_PRIVATE: acceso compartido a su proceso y sus hijos.
    //  0666: rwx rwx rwx
    shmid_x = shmget(IPC_PRIVATE, sizeof(int) * (x + 1), IPC_CREAT | 0666); // x -> x+1 ya que también contamos al padre
    shmid_y = shmget(IPC_PRIVATE, sizeof(int) * y, IPC_CREAT | 0666);

    // Vinculamos el segmento de memoria compartida
    pidx = (int *)shmat(shmid_x, 0, 0);
    pidy = (int *)shmat(shmid_y, 0, 0);

    pidx[0] = getpid();

    for (i = 1; i <= x; i++)
    {
      pid = fork();

      if (pid != 0)
      {
        // Paramos al padre (llamado hijos)
        wait(NULL);

        if (i == 1)
        {
          sleep(10);
          // Imprimimos la linea del superpadre.
          printf("Soy el superpadre (%d): mis hijos finales son:  ", getpid());
          for (j = 1; j <= x; j++)
            printf("%d ", pidx[j]);

          for (j = 0; j < y; j++)
            printf("%d ", pidy[j]);

          printf("\n");
        }

        break;
      }
      else
      {
        // Los hijos
        pidx[i] = getpid();

        // Imprimimos la linea individual.
        printf("Soy el subhijo %d, mis padres son: ", pidx[i]);
        for (j = 0; j < i; j++)
          printf("%d ", pidx[j]);

        printf("\n");
      }
    }

    // Creamos los procesos...
    if (i == x + 1)
    {

      for (j = 1; j <= y; j++)
      {
        pid = fork();

        if (pid == 0)
        {
          pidy[j - 1] = getpid();
          break;
        }
      }

      // Hacemos que esperen.
      if (j == y + 1)
        for (j = 1; j <= y; j++)
        {
          wait(NULL);
        }
    }
  }

  exit(0);
}
