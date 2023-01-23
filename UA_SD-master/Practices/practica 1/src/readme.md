# Practica 1 - Elvi Mihai Sabau Sabau

Los archivos que hay son `servidor.py` y `cliente.py`.

El servidor ejecuta comandos enviados por el cliente en la maquina del servidor.

Se usan las librerias:
- `_thread` para ejecutar nuevos hilos por cada conexion.
- `os` para ejecutar los comandos en el servidor.
- `sys` para leer los parametros.
- `socket` para manejar los sockets.

## Ejecucion del servidor.

El servidor ejecuta una funcion `Main`, revisa los parametros (direccion del servidor, y puerto en el cual ejecutar).

Crea un controlar socket, y bindea la direccion del host y del puerto, y se pone a escuchar.

En un bucle infinito, se espea a recibir una conexion, y cuando recibe, se guarda el controlador de dicha conexion ( variable llamada `c` ), y crea un nuevo proceso, ademas de imprimir por pantalla que se ha recibido una nueva conexion.

Este proceso ejecuta una funcion llamada `clientProcess` que tiene de parametro el controlador de la conexion del socket.

En esta funcion `clientProcess` hay un bucle infinito, que se espera a recibir datos por el canal, los decodifica, y revisa si lo enviado es un string llamado `exit`, si lo es, envia al cliente un string llamado `CLS001` que el cliente revisara para confirmar que el servidor esta a punto de cerrar la conexion. Una vez enviado el codigo al cliente, el servidor cierra la conexion.

En caso de que el dato recibido no sea un string llamado `exit`, se ejcutaa en un try catch, la funcion auxiliar `run` con el comando a ejecutar en el servidor.

Esta funcion `run` ejecuta el comando, y devuelve el output, en caso de que no haya output, devuelve un mensaje por defecto, esto se debe a que hay comandos que no devuelve nada por pantalla, como por ejemplo el comando `mkdir`.

Una vez ejecutada esta funcion, `clientProcess` guarda su salida en una variable, la codifica, y la envia al cliente, ademas de imprimirla en la consola del servidor.

## Ejecucion del cliente.

El cliente ejecuta una funcion `Main`, revisa los parametros (direccion del servidor y puerto al cual conectar).

Crea un controlar socket, y bindea la direccion del host y del puerto, y conecta.

En un bucle infinito, pide al usuario un comando por consola, y al leerlo, comprueba que no sea `exit`, si lo es, lo codifica, lo manda al servidor, se espera a recibir un codigo de confirmacion para saber que el servidor cerrara la conexion, una vez recibido, el cliente rompe el bucle infinito y cierra su conexion.

En caso contrario, codifica el comando, lo manda al servidor, se espera a recibir el output del comando, lo imprime por pantalla, y vuelve a esperar un input por consola.


## Como ejecutar.

- Servidor: `python3 servidor.py [direccion] [puerto]`
- Cliente: `python3 cliente.py [direccion] [puerto]`

Ejemplo:

- en una consola aparte, ejecutamos el servidor.
    - `python3 servidor.py localhost 9001`

- en otra consola aparte, ejecutamos el cliente.
    - `python3 cliente.py localhost 9001`