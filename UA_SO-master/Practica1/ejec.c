// Elvi Mihai Sabau Sabau - 51254875L

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

// Callback.
void alarma()
{
}

int main(int argc, char *argv[])
{

    // Revisamos que haya el numero correcto de argumentos.
    if (argc <= 1)
    {
        perror("Se deben pasar 1 argumento: ./ejec segudos");
        exit(1);
    }

    int i = 0, status;

    // X, Y e Z recogidos del wait.
    int hijosMuertos[3];
    int arb, A, B;

    // Pids especificos del proceso.
    int abuelo, padre;

    int segundos;
    segundos = atoi(argv[1]);

    // Pid del padre de todos, la raiz.
    arb = getpid();
    printf("Soy el proceso ejec: Mi pid es: %d\n", getpid());

    // Creamos A.
    A = fork();
    if (A < 0)
    {
        perror("Fallo al crear proceso hijo (A), linea 437.");
        exit(1);
    }

    abuelo = getpid();

    // Si estamos en A..
    if (A == 0)
    {
        printf("Soy el proceso A: Mi pid es: %d. Mi padre es: %d\n", getpid(), getppid());

        // Creamos B.
        B = fork();
        if (B < 0)
        {
            perror("Fallo al crear proceso hijo (B), linea 45.");
            exit(1);
        }

        padre = getpid();

        // Si estamos en B..
        if (B == 0)
        {
            printf("Soy el proceso B: Mi pid es: %d. Mi padre es: %d, mi abuelo es: %d\n", getpid(), getppid(), arb);

            // Creamos X, Y e Z.
            for (i; i < 3; i++)
            {
                int hijo;
                hijo = fork();

                if (hijo < 0)
                {
                    perror("Fallo al crear proceso hijo, linea 54.");
                    exit(1);
                }
                else if (hijo == 0)
                {
                    switch (i)
                    {
                    case 0:
                        printf("Soy el proceso X: Mi pid es: %d. Mi padre es %d, abuelo %d, mi bisabuelo es: %d\n", getpid(), getppid(), abuelo, arb);
                        break;

                    case 1:
                        printf("Soy el proceso Y: Mi pid es: %d. Mi padre es %d, abuelo %d, mi bisabuelo es: %d\n", getpid(), getppid(), abuelo, arb);
                        break;

                    case 2:
                        printf("Soy el proceso Z: Mi pid es: %d. Mi padre es %d, abuelo %d, mi bisabuelo es: %d\n", getpid(), getppid(), abuelo, arb);
                        signal(SIGALRM, alarma);
                        alarm(segundos);
                        pause();

                        execlp("pstree", "pstree", NULL);
                    }

                    break;
                }
                else if (hijo > 0)
                {
                    hijosMuertos[i] = wait(&status);

                    if (i == 2)
                    {
                        printf("Soy Z (%d) y muero\n", hijosMuertos[2]);

                        kill(hijosMuertos[1], SIGKILL);
                        printf("Soy Y (%d) y muero\n", hijosMuertos[1]);

                        kill(hijosMuertos[0], SIGKILL);
                        printf("Soy X (%d) y muero\n", hijosMuertos[0]);
                    }
                }
            }
        }
        else
        {
            wait(&status);
            kill((pid_t)padre, SIGKILL);
        }
    }
    else
        wait(NULL);

    if (i == 3)
    {
        printf("Soy B (%d) y muero\n", padre);
        printf("Soy A (%d) y muero\n", abuelo);

        kill(abuelo, SIGKILL);
        printf("Soy ejec (%d) y muero\n", arb);

        exit(0);
    }
}
