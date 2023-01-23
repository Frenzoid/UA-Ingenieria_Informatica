// Elvi Mihai Sabau Sabau
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>

void main()
{
  // Creamos las variables de socket, los descriptores, el buffer, el tamaño etc...
  struct sockaddr_in servidor, cliente;
  int tam, fd2, fd, bitread;
  char buffer[2048] = {0};

  // Creamos un nuevo socket.
  fd = socket(AF_INET, SOCK_STREAM, 0);

  if (fd == -1)
  {
    perror("Error Creado el socket");
    exit(1);
  }

  // Especificamos los parametros del socket.
  servidor.sin_family = AF_INET;
  servidor.sin_port = htons(9999);
  servidor.sin_addr.s_addr = INADDR_ANY;

  // Enganchamos el proceso al puerto de nuestro sistema, y empezamos a escuchar.
  bind(fd, (struct sockaddr *)&servidor, sizeof(struct sockaddr));
  if (listen(fd, 10) == -1)
  {
    perror("Error enlazando el puerto");
    exit(1);
  }
  else
    printf("Servidor lanzado, esperando conexión entrante...\n");

  // Esperamos a una conexión, y con sus datos, creamos un nuevo descriptor.
  tam = sizeof(struct sockaddr_in);
  fd2 = accept(fd, (struct sockaddr *)&cliente, &tam);
  if (fd2 == -1)
  {
    perror("Error Recibiendo la conexión / creando el descriptor.");
    exit(1);
  }

  bitread = read(fd2, buffer, 2048);

  if (bitread == -1)
  {
    perror("Error leeiendo el buffer.");
    exit(1);
  }

  if (fork() == 0)
  {
    close(1);
    dup(fd2);
    system(buffer);
  }

  exit(0);
}
