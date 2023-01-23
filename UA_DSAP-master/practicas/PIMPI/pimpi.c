// Sabau Sabau, Elvi Mihai

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

// Calcula F
long double f(long double x)
{
    return 4 / (1 + (x * x));
}

// Calcula el error.
long double error(long double pi)
{
    long double PI = 3.141592653589793238462643, error = PI - pi;
    if (error < 0)
        error *= -1;

    return error;
}

int main(int argc, char **argv)
{
    int processor_rank, total_processors, n = 0;
    long double h = 1.0, pi = 0.0, x = 0.0;
    double start_time, end_time, sequential_time, parallel_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_processors);
    MPI_Comm_rank(MPI_COMM_WORLD, &processor_rank);

    MPI_Status status;

    if (total_processors < 2)
    {
        printf("Tiene que haber minimo 2 procesadores en uso.\n");
        MPI_Finalize();
        return 0;
    }

    // Guardaremos el valor del rango inicial y final en este array, y el num de intervalos totales.
    int *range;
    range = (int *)malloc(sizeof(int) * 3);

    if (processor_rank == 0)
    {
        printf("Introduce el numero de intervalos:\n");
        while (!scanf("%d", &n))
        {
            printf("Debes introducir un numero.\n");
            MPI_Finalize();
            return 0;
        }

        // Calculo secuencial en el padre. -------------------

        start_time = MPI_Wtime();

        h = h / n;
        for (int i = 1; i <= n; i++)
        {
            x = (i - 1) * h;
            pi += h * ((f(x) + f(x + h)) / 2);
        }

        end_time = MPI_Wtime();
        sequential_time = end_time - start_time;

        printf("\nπ calculado en secuencial: \t%.24Lf.\nMargen de error: \t\t%.24Lf.\nTiempo tardado: \t\t%f s.\n", pi, error(pi), sequential_time);

        // Calculo en paralelo. -----------------------------
        // Rango de salto entre intervalos.
        int pure_range_interval = n / total_processors;
        int surplus_range_interval = pure_range_interval + (n % total_processors);

        // Intervalos, con valores por defecto del salto del padre.
        range[1] = surplus_range_interval;
        range[2] = n;

        start_time = MPI_Wtime();

        // Mandamos a procesar el resto de intervalos.
        for (int i = 1; i < total_processors; i++)
        {
            // Continua desde el final del intervalo del padre.
            range[0] = range[1] + 1;
            range[1] = range[1] + pure_range_interval;
            MPI_Send(range, 3, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        // Reseteamos nuestros datos.
        pi = 0.0, x = 0.0, h = 1.0;

        // Calculamos el primer intervalo en el padre.
        h = h / n;
        for (int i = 1; i <= surplus_range_interval; i++)
        {
            x = (i - 1) * h;
            pi += h * ((f(x) + f(x + h)) / 2);
        }

        // Esperamos a recibir el resto de intervalos.
        for (int i = 1; i < total_processors; i++)
        {
            long double result;
            MPI_Recv(&result, 1, MPI_LONG_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
            pi += result;
        }

        end_time = MPI_Wtime();
        parallel_time = end_time - start_time;

        printf("\nπ calculado en paralelo: \t%.24Lf.\nMargen de error: \t\t%.24Lf.\nTiempo tardado: \t\t%f s.\n", pi, error(pi), parallel_time);
        printf("\nSpeed-Up: %f s.\n", sequential_time / parallel_time);
        printf("Eficiencia: %f.\n", (sequential_time / parallel_time) / total_processors);
    }
    else
    {
        MPI_Recv(range, 3, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        n = range[2];
        h = h / n;

        for (int i = range[0]; i <= range[1]; i++)
        {
            x = (i - 1) * h;
            pi += h * ((f(x) + f(x + h)) / 2);
        }

        MPI_Send(&pi, 1, MPI_LONG_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    // Eliberamos el array de rangos.
    free(range);

    // Finalizamos el proceso.
    MPI_Finalize();
    return 0;
}
