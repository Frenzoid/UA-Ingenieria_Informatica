// Elvi Mihai Sabau Sabau

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAXN = 1000;
const int MAXNUMPROCS = 8;

int main(int argc, char **argv)
{
    // Pre-Defs

    float **createMatWeight(int, int);
    int **createMatPaths(int, int);

    void defStructure(int, float **, int **);

    void printMatWeight(float **, int, int);
    void printMatPaths(int **, int, int);

    void clearMatWeight(float **, int);
    void clearMatPaths(int **, int);

    void calcPath(float **, int **, int);

    int processor_rank = 0, total_processors = 0, n = 0, lm = 0, rest = 0, **paths;
    float **dist;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &processor_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &total_processors);

    // Checks

    if (total_processors > MAXNUMPROCS)
    {
        if (processor_rank == 0)
            printf("Superado el numero maximo de procesos.\n");

        MPI_Finalize();
        exit(1);
    }

    if (total_processors < 2)
    {
        printf("Tiene que haber minimo 2 procesadores en uso.\n");
        MPI_Finalize();
        exit(1);
    }

    if (processor_rank == 0)
    {
        printf("Numero de vertices: \n");
        if (!scanf("%d", &n))
        {
            printf("Debes introducir un numero.\n");
            MPI_Finalize();
            exit(1);
        }
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (n > MAXN)
    {
        if (processor_rank == 0)
            printf("numero maximo de vertices superado.\n");

        MPI_Finalize();
        exit(1);
    }
    else if (n <= 0)
    {
        if (processor_rank == 0)
            printf("Cantidad incorrecta de vertices.\n");

        MPI_Finalize();
        exit(1);
    }

    // Start

    lm = n / total_processors;
    dist = createMatWeight(n, n);
    paths = createMatPaths(n, n);

    if (processor_rank == 0)
    {
        defStructure(n, dist, paths);
        rest = n % total_processors;
    }

    // Barriers and scatters
    MPI_Barrier(MPI_COMM_WORLD);
    if (processor_rank != 0)
    {
        MPI_Scatter(&dist[0][0], lm * n, MPI_FLOAT, &dist[0][0], lm * n, MPI_FLOAT, 0, MPI_COMM_WORLD);
        MPI_Scatter(&paths[0][0], lm * n, MPI_INT, &paths[0][0], lm * n, MPI_INT, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Scatter(&dist[rest][0], lm * n, MPI_FLOAT, MPI_IN_PLACE, lm * n, MPI_FLOAT, 0, MPI_COMM_WORLD);
        MPI_Scatter(&paths[rest][0], lm * n, MPI_INT, MPI_IN_PLACE, lm * n, MPI_INT, 0, MPI_COMM_WORLD);
    }

    float *d = (float *)malloc(n * sizeof(float));

    int *c = (int *)malloc(n * sizeof(int));
    int sender = 0, row_k = 0;

    for (int k = 0; k < n; k++)
    {
        sender = (k < lm + n % total_processors) ? 0 : total_processors - 1 - ((n - k - 1) / lm);
        row_k = (sender == 0) ? k : k - (lm * sender) - n % total_processors;

        if (processor_rank == sender)
        {
            memcpy(&d[0], &dist[row_k][0], n * sizeof(float));
            memcpy(&c[0], &paths[row_k][0], n * sizeof(int));
        }

        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Bcast(&d[0], n, MPI_FLOAT, sender, MPI_COMM_WORLD);
        MPI_Bcast(&c[0], n, MPI_INT, sender, MPI_COMM_WORLD);

        for (int i = 0; i < lm + rest; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] * d[j] != 0)
                    if ((dist[i][k] + d[j] < dist[i][j]) || (dist[i][j] == 0))
                    {
                        dist[i][j] = dist[i][k] + d[j];
                        paths[i][j] = c[j];
                    }
    }

    free(d);
    free(c);

    if (processor_rank != 0)
    {
        MPI_Gather(&dist[0][0], lm * n, MPI_FLOAT, &dist[0][0], lm * n, MPI_FLOAT, 0, MPI_COMM_WORLD);
        MPI_Gather(&paths[rest][0], lm * n, MPI_INT, &paths[rest][0], lm * n, MPI_INT, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Gather(MPI_IN_PLACE, lm * n, MPI_FLOAT, &dist[rest][0], lm * n, MPI_FLOAT, 0, MPI_COMM_WORLD);
        MPI_Gather(MPI_IN_PLACE, lm * n, MPI_INT, &paths[rest][0], lm * n, MPI_INT, 0, MPI_COMM_WORLD);
    }

    // print after scatter
    if (processor_rank == 0)
    {
        if (n < 10)
        {
            printMatPaths(paths, n, n);
            printMatWeight(dist, n, n);
        }

        calcPath(dist, paths, n);
    }

    clearMatWeight(dist, n);
    clearMatPaths(paths, n);
    MPI_Finalize();
}

// Functions

void defStructure(int n, float **dist, int **paths)
{
    int i, j;

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
        {
            if (i == j)
                dist[i][j] = 0;
            else
            {
                dist[i][j] = (11.0 * rand() / (RAND_MAX + 1.0));
                dist[i][j] = ((double)((int)(dist[i][j] * 10))) / 10;

                if (dist[i][j] < 2)
                    dist[i][j] = 0;
            }

            if (dist[i][j] != 0)
                paths[i][j] = i + 1;
            else
                paths[i][j] = 0;
        }
}

float **createMatWeight(int filas, int columnas)
{
    if (filas <= 0 || columnas <= 0)
    {
        printf("Dimension incorrecta.\n");
        exit(1);
    }

    float **matrix = (float **)malloc(filas * sizeof(float *));
    matrix[0] = (float *)malloc(filas * columnas * sizeof(float));

    if (matrix == NULL)
    {
        printf("Memoria insuficiente.\n");
        exit(1);
    }

    for (int i = 1; i < filas; ++i)
        matrix[i] = matrix[i - 1] + columnas;

    return matrix;
}

int **createMatPaths(int filas, int columnas)
{
    if (filas <= 0 || columnas <= 0)
    {
        printf("Dimension incorrecta.\n");
        exit(1);
    }

    int **matrix = (int **)malloc(filas * sizeof(int *));
    matrix[0] = (int *)malloc(filas * columnas * sizeof(int));

    if (matrix == NULL)
    {
        printf("Memoria insuficiente.\n");
        exit(1);
    }

    for (int i = 1; i < filas; ++i)
        matrix[i] = matrix[i - 1] + columnas;

    return matrix;
}

void clearMatPaths(int **paths, int n)
{
    for (int i = 1; i < n; i++)
        paths[i] = NULL;

    free(paths[0]);
    free(paths);
}

void clearMatWeight(float **dist, int n)
{
    for (int i = 1; i < n; i++)
        dist[i] = NULL;

    free(dist[0]);
    free(dist);
}

void printMatPaths(int **a, int fila, int col)
{
    int i, j;

    printf("\nMatriz de caminos:\n");
    for (i = 0; i < fila; ++i)
    {
        for (j = 0; j < col; ++j)
            printf("%5d", a[i][j]);

        printf("\n");
    }

    printf("\n");
}

void printMatWeight(float **a, int fila, int col)
{
    int i, j;

    printf("\nMatriz de pesos:\n");
    for (i = 0; i < fila; ++i)
    {
        for (j = 0; j < col; ++j)
            printf("%5.1f", a[i][j]);

        printf("\n");
    }

    printf("\n");
}

void calcPath(float **a, int **b, int n)
{
    int i, count, countAux, prev, *path, start, end;

    printf("Vertice de inicio: \n");
    if (!scanf("%d", &start) || start == 0 || start > n)
    {
        printf("Debes introducir un numero, y que este entre 1 y %d.\n", n);
        MPI_Finalize();
        exit(1);
    }

    printf("Vertice final: \n");
    if (!scanf("%d", &end) || end == 0 || end > n)
    {
        printf("Debes introducir un numero, y que este entre 1 y %d.\n", n);
        MPI_Finalize();
        exit(1);
    }

    count = 2;

    while (start != 0 && end != 0)
    {
        prev = end;
        while (b[start - 1][prev - 1] != start)
        {
            prev = b[start - 1][prev - 1];
            count = count + 1;
        }

        countAux = count;
        path = malloc(count * sizeof(int));

        prev = end;
        path[count - 1] = end;

        while (b[start - 1][prev - 1] != start)
        {
            prev = b[start - 1][prev - 1];
            count = count - 1;
            path[count - 1] = prev;
        }

        path[0] = start;
        printf("\nCamino mas corto: de %d a %d, Peso: %4.1f, ", start, end, a[start - 1][end - 1]);
        printf("Camino: ");

        for (i = 0; i < countAux; i++)
            printf("%d ", path[i]);

        printf("\n");

        free(path);
        start = end = 0;
    }
}