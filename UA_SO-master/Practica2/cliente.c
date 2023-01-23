// Elvi Mihai Sabau Sabau
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

void main(int argc, char const *argv[])
{
  // Declaramos las variables, los descriptores, el buffer...
  struct sockaddr_in servidor;
  int fd;
  char buffer[2048] = {0};

  const char *comando = argv[2];

  // Creamos el socket.
  fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1)
  {
    perror("Error creando el socket");
    exit(1);
  }

  // Especificamos los parametros del socket.
  servidor.sin_family = AF_INET;
  servidor.sin_port = htons(9999);
  servidor.sin_addr.s_addr = inet_addr(argv[1]);

  // Abrimos una nueva conxión.
  if (connect(fd, (struct sockaddr *)&servidor, sizeof(servidor)) == -1)
  {
    perror("Error realizando la conexión.");
    exit(1);
  }

  // Enviamos los comandos, y recibimos los datos.
  if (send(fd, comando, sizeof(comando), 0) == -1)
  {
    perror("Error enviando datos.");
    exit(1);
  }

  if (recv(fd, buffer, sizeof(buffer), 0) == -1)
  {
    perror("Error recibiendo datos.");
    exit(1);
  }

  printf("----------SALIDA DEL COMANDO %s ----------\n%s", comando, buffer);

  exit(0);
}
