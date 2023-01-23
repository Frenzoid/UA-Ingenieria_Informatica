// Sabau Sabau, Elvi Mihai

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

const int MAXNPROC = 8;
const int MAXN = 100000000;

int main(int argc, char **argv)
{
    int processor_rank, total_processors;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_processors);
    MPI_Comm_rank(MPI_COMM_WORLD, &processor_rank);

    MPI_Status status;

    if (total_processors < 2)
    {
        printf("Tiene que haber minimo 2 procesadores en uso.\n");

        // No cierra correctamente por el mismo motivo que en el ejercicio del anillo. Lo unico que se cierra es el
        //  proceso padre.
        MPI_Finalize();
        return 0;
    }

    // Comprueba si el proceso actual super el numero limite de la longitud de vectores.
    if (processor_rank >= MAXN)
    {
        MPI_Finalize();
        return 0;
    }

    // Comprueba si el numero total de procesos supera el limite total de procesos.
    if (total_processors > MAXNPROC)
    {
        if (processor_rank == 0)
            printf("!El numero de procesos no puede ser mayor que %d. Se ha limitado a %d procesos.\n", MAXNPROC, MAXNPROC);

        else if (processor_rank >= MAXNPROC)
        {
            // Misma situación que arriba.
            MPI_Finalize();
            return 0;
        }

        total_processors = MAXNPROC;
    }

    int vector_size;
    if (processor_rank == 0)
    {
        printf("Introduce el tamaño de vector deseado\n(debe ser mayor que el numero de procesos):\n");
        if (!scanf("%d", &vector_size))
        {
            // Misma situación que arriba.
            printf("Debes introducir un numero.\n");
            MPI_Finalize();
            return 0;
        }

        // Comprueba si el tamaño del vector es mayor que el num de procesos.
        if (processor_rank >= vector_size)
        {
            // Misma situación que arriba.
            MPI_Finalize();
            return 0;
        }

        // Comprueba si la longitud del vector supera el limite de longitud del vector.
        if (vector_size > MAXN)
        {
            printf("!El tamaño del vector supera el limite. Se ha limitado a %d slots.\n", MAXN);
            vector_size = MAXN;
        }
    }

    // Envia la variable vector_size a todos los hijos.
    MPI_Bcast(&vector_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    double *x, *y;

    // Balanceamos la carga
    // Slot x proceso
    int j = vector_size / total_processors;

    // Slots sobrantes
    int ln = (vector_size - (j * (total_processors - 1)));

    if (processor_rank == 0)
    {
        // Codigo del proceso maestro.
        // Declaramos los arrays.
        x = (double *)malloc(sizeof(double) * vector_size);
        y = (double *)malloc(sizeof(double) * vector_size);

        // Rellenamos los vectores con la formula especificada.
        for (int k = 0; k < vector_size; k++)
        {
            x[k] = 1.0 / (k + 1);
            y[k] = 1.0 + k;
        }

        // Enviamos los slots divididos justamente a cada proceso.
        for (int i = 0; i < (total_processors - 1); i++)
        {
            MPI_Send(&x[i * j + ln], j, MPI_DOUBLE, i + 1, 0, MPI_COMM_WORLD);
            MPI_Send(&y[i * j + ln], j, MPI_DOUBLE, i + 1, 1, MPI_COMM_WORLD);
        }

        // P0: Producto escalar + sobrante.
        // Guardamos el resultado en el primer slot de la fracción.
        x[0] = x[0] * y[0];
        for (int i = 1; i < ln; i++)
        {
            x[i] = x[i] * y[i];
            x[0] += x[i];
        }

        // Esperamos a recibir.
        for (int i = 0; i < (total_processors - 1); i++)
            MPI_Recv(&x[i + 1], 1, MPI_DOUBLE, i + 1, 0, MPI_COMM_WORLD, &status);

        for (int i = 1; i < total_processors; i++)
            x[0] += x[i];

        printf("El producto escalar es: %f\n", x[0]);
    }
    else
    {
        // Código de los esclavos.
        x = (double *)malloc(sizeof(double) * j);
        y = (double *)malloc(sizeof(double) * j);

        MPI_Recv(x, j, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(y, j, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);

        // PX: Producto escalar.
        // Guardamos el resultado en el primer slot de la fracción.
        x[0] = x[0] * y[0];
        for (int i = 1; i < j; i++)
        {
            x[i] = x[i] * y[i];
            x[0] += x[i];
        }

        MPI_Send(x, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    // Eliberamos los vectores.
    free(x);
    free(y);

    // Finalizamos el proceso.
    MPI_Finalize();
    return 0;
}