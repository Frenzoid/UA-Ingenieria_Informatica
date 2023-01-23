// Elvi Mihai Sabau Sabau - 51254875L

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    char opcion;

    if (argc != 3)
    {
        perror("Error, se deben pasar 2 argumentos, ./hacha archivo tamaño \n");
        exit(1);
    }
    else
    {
        int DescEntrada, DescSalida;           // descriptores
        DescEntrada = open(argv[1], O_RDONLY); // Padre: abre el fichero read only.

        if (DescEntrada < 0)
        {
            perror("Error, No existe el fichero \n");
            exit(1);
        }
        else
        {
            struct stat propFichero; // struct para recoger las propiedades del fichero (tamaño y nombre)

            char nombreFichero[100];
            char bufferSal[100];
            int tubo[2]; // tubo[0] lectura, tubo[1] escritura.

            int numTrozos,
                numLeidos,
                estado;

            stat(argv[1], &propFichero);
            numTrozos = (int)propFichero.st_size / atoi(argv[2]);

            // vector donde voy leyendo del fichero trozos.
            char trozoLeido[atoi(argv[2])];

            // Comprueba si hay resto, si lo hay, crea un trozo extra.
            if ((int)propFichero.st_size % atoi(argv[2]) != 0)
                numTrozos++;

            // por cada trozo, el padre crea un pipe, forkea y espera, el hijo recibe el dato desde el pipe, crea el fichero y muere.
            for (int i = 0; i < numTrozos; i++)
            {
                pipe(tubo);
                if (fork() != 0)
                {
                    // leemos un trozo y lo escribimos en el tubo.
                    numLeidos = read(DescEntrada, trozoLeido, atoi(argv[2]));
                    write(tubo[1], trozoLeido, numLeidos);
                    wait(&estado);
                }
                else
                {
                    if (i < 10)
                        // la funcion sprintf vuelca el resultado de la impresion a un vector en vez de en pantalla.
                        sprintf(nombreFichero, "%s.h0%d", argv[1], i);
                    else
                        sprintf(nombreFichero, "%s.h%d", argv[1], i);

                    DescSalida = creat(nombreFichero, 0666);

                    numLeidos = read(tubo[0], trozoLeido, atoi(argv[2]));
                    write(DescSalida, trozoLeido, numLeidos);
                    close(DescSalida);

                    exit(0);
                }
            }
        }
    }

    exit(0);
}
