// Sabau Sabau, Elvi Mihai

#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int processor_rank, total_processors, numero = 0;

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

    if (processor_rank == 0)
    {
        printf("Introduce un entero para transmitir:\n");

        if (!scanf("%d", &numero))
        {
            printf("Debes introducir un numero.\n");

            // Nota: Deberiamos enviar un mensaje al resto de procesos tirando en el resto de procesadores,
            //  para que se cerrasen, ya que, ahora como está, solo se cierra el proceso 0, y el resto se quedan
            //  colgados. Pero esto no se puede hacer con un recv normal, ya que en el caso de que funcionase
            //  bien, los procesos se quedarian colgados esperando en el segundo recv, creo que esto se deberia
            //  hacer con un recv asincrono, pero no lo hemos dado, y tampoco se si se pueden usar cosas que aún
            //  no hemos dado en las primeras prácticas.
            MPI_Finalize();
            return 0;
        }

        printf("El entero introducido es %d\n", numero);

        MPI_Send(&numero, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        MPI_Recv(&numero, 1, MPI_INT, total_processors - 1, 1, MPI_COMM_WORLD, &status);

        printf("Soy el proceso %d. El entero que he recibido es: %d\n", processor_rank, numero);
    }
    else
    {
        MPI_Recv(&numero, 1, MPI_INT, processor_rank - 1, 1, MPI_COMM_WORLD, &status);
        printf("Soy el proceso %d. El entero que he recibido es: %d\n", processor_rank, numero);
        numero++;

        if (processor_rank != (total_processors - 1))
        {
            MPI_Send(&numero, 1, MPI_INT, processor_rank + 1, 1, MPI_COMM_WORLD);
        }
        else
        {
            MPI_Send(&numero, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}