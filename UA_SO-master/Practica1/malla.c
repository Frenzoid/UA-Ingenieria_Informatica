// Elvi Mihai Sabau Sabau - 51254875L

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Revisamos que haya el numero correcto de argumentos.
    if (argc == 3)
    {
        // x: filas, y: columbas,
        int x, y;

        x = atoi(argv[1]);
        y = atoi(argv[2]);

        for (int j = 0; j < y; j++)
        {
            // Creamos los hijos del proceso padre, la primera fila.
            int pid_primera_fila = fork();

            if (pid_primera_fila < 0)
            {
                perror("Fallo al crear hijo del padre raiz");
                exit(1);
            }
            else if (pid_primera_fila == 0)
            {
                // La primera fila de hijos ya se creo, asi que x deberá ser x - 1.
                for (int i = 0; i < x - 1; i++)
                {
                    int pid_filas_inferiores = fork();

                    if (pid_filas_inferiores < 0)
                    {
                        perror("Fallo al crear subhijo");
                        exit(1);
                    }
                    else if (pid_filas_inferiores > 0)
                        break;
                }

                break;
            }
        }

        // Usamos un sleep para poder ejecutar el comando pstree -c al ejecutar el programa malla.
        sleep(15);
        exit(0);
    }

    perror("Se deben pasar 2 argumentos, num de filas, num de cols, ejemplo: ./malla x y");
    exit(1);
}