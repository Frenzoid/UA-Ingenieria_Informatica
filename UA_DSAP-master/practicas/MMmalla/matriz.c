// Elvi Mihai Sabau Sabau

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MAXBLOQ 100

main(int argc, char **argv)
{
    int myrank, numprocs, numprocvalido = 0, bloqtam, bloqvalido = 0, dimension, init = 0, dst, src, sizeBuffer, errorMargin;
    int fila, columna, i, k = 0;
    double *a, *b, *c, *buffer;
    double *atmp;

    int *mifila;

    MPI_Status status;
    MPI_Request request;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    if (myrank == 0)
    {

        dimension = sqrt(numprocs);
        if (dimension > 4)
        {
            printf("La dimensión de las matrices no puede ser superior a 4.\n");
            MPI_Finalize();
            exit(1);
        }

        if (dimension * dimension != numprocs)
        {
            printf("El numero de procesadores debe ser un cuadrado perfecto.\n");
            MPI_Finalize();
            exit(1);
        }

        printf("Introduce el tamaño de la matriz\n");

        if (scanf("%d", &bloqtam) && !(bloqtam > 0 && bloqtam <= MAXBLOQ))
        {
            printf("El bloque debe ser menor de 100\n");
            MPI_Finalize();
            exit(1);
        }

        for (dst = 1; dst < numprocs; dst++)
        {
            MPI_Send(&bloqtam, 1, MPI_INT, dst, 8, MPI_COMM_WORLD);
            MPI_Send(&dimension, 1, MPI_INT, dst, 8, MPI_COMM_WORLD);
        }
    }

    if (myrank == 0)
    {
        b = malloc(bloqtam * bloqtam * sizeof(double));
        c = malloc(bloqtam * bloqtam * sizeof(double));

        mifila = malloc((dimension - 1) * sizeof(int));
        atmp = malloc(bloqtam * bloqtam * sizeof(double));

        matInitializate(a, b, c, dimension, bloqtam, 0, 0, i, myrank);
        calcRow(mifila, dimension, columna, fila, myrank);
    }
    else
    {
        MPI_Recv(&bloqtam, 1, MPI_INT, 0, 8, MPI_COMM_WORLD, &status);
        MPI_Recv(&dimension, 1, MPI_INT, 0, 8, MPI_COMM_WORLD, &status);

        a = malloc(bloqtam * bloqtam * sizeof(double));
        b = malloc(bloqtam * bloqtam * sizeof(double));
        c = malloc(bloqtam * bloqtam * sizeof(double));

        atmp = malloc(bloqtam * bloqtam * sizeof(double));
        mifila = malloc((dimension - 1) * sizeof(int));

        fila = myrank / dimension;
        columna = myrank % dimension;

        matInitializate(a, b, c, dimension, bloqtam, fila, columna, i, myrank);

        calcRow(mifila, dimension, columna, fila, myrank);
    }

    MPI_Pack_size(pow(bloqtam, 2), MPI_DOUBLE, MPI_COMM_WORLD, &sizeBuffer);

    sizeBuffer = numprocs * (sizeBuffer + MPI_BSEND_OVERHEAD);
    buffer = malloc(sizeBuffer * sizeof(double));

    MPI_Buffer_attach(buffer, sizeBuffer);

    int tarea;
    fila++;

    while (k < dimension)
    {
        // A

        if (columna == (fila + k) % dimension)
        {
            for (tarea = 0; tarea < dimension - 1; tarea++)
            {
                MPI_Send(a, pow(bloqtam, 2), MPI_DOUBLE, mifila[tarea], k, MPI_COMM_WORLD);
            }

            mult(a, b, c, bloqtam);
        }
        else
        {
            src = ((fila + k) % dimension) + fila * dimension;

            printf("SRC: %d\n", src);
            MPI_Recv(atmp, pow(bloqtam, 2), MPI_DOUBLE, src, k, MPI_COMM_WORLD, &status);

            mult(atmp, b, c, bloqtam);
        }

        // B
        if (fila == 0)
            dst = (dimension - 1) * dimension + columna;
        else
            dst = myrank - dimension;

        if (fila == dimension - 1)
            src = columna;
        else
            src = myrank + dimension;

        MPI_Bsend(b, pow(bloqtam, 2), MPI_DOUBLE, dst, 20 * k, MPI_COMM_WORLD);
        MPI_Recv(b, pow(bloqtam, 2), MPI_DOUBLE, src, 20 * k, MPI_COMM_WORLD, &status);
    }

    MPI_Buffer_detach(buffer, &sizeBuffer);
    errorMargin = checkIntegrity(a, b, c, bloqtam, myrank);

    if (myrank == 0)
    {
        int tot_errorMargin = 0;

        for (i = 1; i < numprocs; i++)
        {
            MPI_Recv(&errorMargin, 1, MPI_INT, i, 100, MPI_COMM_WORLD, &request);

            printf("El margen de error del proceso %d es %d.\n", i, errorMargin);
            tot_errorMargin = errorMargin + tot_errorMargin;
        }

        printf("El total del margen de error es %d.\n", tot_errorMargin);
    }
    else
        MPI_Send(&errorMargin, 1, MPI_INT, 0, 100, MPI_COMM_WORLD);

    MPI_Finalize();
    exit(0);
}

void matInitializate(double *a, double *b, double *c, int dimension, int bloqtam, int fila, int columna, int i, int myrank)
{
    int rellenob = 0;
    int tam = pow(bloqtam, 2);
    float pos = pow((fila * columna + 1), 2);

    for (i = 0; i < tam; i++)
    {

        a[i] = i * pos / tam;

        if (i == rellenob && fila == columna)
        {
            b[i] = 1;
            rellenob = rellenob + bloqtam + 1;
        }
        else
            b[i] = 0;

        c[i] = 0;
    }
}

void calcRow(int *mifila, int dimension, int columna, int fila, int myrank)
{
    int i, j = 0;
    for (i = 0; i < dimension; i++)
        if (i != columna)
        {
            mifila[j] = (fila * dimension) + i;
            j++;
        }
}

int checkIntegrity(double a[], double b[], double c[], int bloqtam, int myrank)
{
    int i;
    int tam = pow(bloqtam, 2);
    int errorMargin = 0;

    for (i = 0; i < tam; i++)
        if (abs(a[i] - c[i]) > 0.000000001)
            errorMargin++;

    return errorMargin;
}

void mult(double a[], double b[], double *c, int m)
{
    int i, j, k;
    for (i = 0; i < m; i++)
        for (j = 0; j < m; j++)
            for (k = 0; k < m; k++)

                c[i * m + j] = c[i * m + j] + a[i * m + k] * b[k * m + j];
}