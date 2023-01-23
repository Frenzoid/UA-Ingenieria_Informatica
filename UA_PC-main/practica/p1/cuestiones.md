ELVI MIHAI SABAU SABAU


# PRACTICA 1 

## Ejercicio 1: Procesos en Unix/C

1. El programa arranca 5 procesos y el proceso padre se espera a que finalizen sus hijos e imprime información sobre estos.
   Cada proceso hijo imprime 50 veces su iterador ( i ) y la cantidad de iteraciones totales ( I ), y va incrementando I.

   `WEXITSTATUS` es una función que se encarga de evaluar la variable `salida` para saber de que modo ha finalizado el proceso hijo.



## Ejercicio 2: Hilos POSIX


1. El programa arranca 5 hilos usando pthread_create, esta funcion permite arrancar hilos ejecutando la logica de una función en concreto.

Esta funcion es `*codigo_del_hilo`, y basicamente imprime el numero de iteraciones ( 50 ) y el total de interaciones ( `I` ).

Despues, en el padre, con `pthread_join` se espera a que finalicen los hilos hijos.

## Diferencias

Las diferencias entre usar `fork` y `pthread_create`.

### fork()

El propósito es crear un nuevo proceso, que se convierte en el proceso hijo del proceso que lo llama.

Ambos procesos ejecutarán las instrucciones que estén por debajo de `fork()` una vez se haya llamado.

Se crean dos copias idénticas del espacio de direcciones, el código y la pila, una para el padre y el hijo.

En resumen: `fork()` crea un clone del proceso padre.

### pthread_create()

El propósito es crear un nuevo hilo en el programa al que se le da el mismo proceso que el proceso que lo llama.

Los subprocesos dentro del mismo proceso pueden comunicarse utilizando la memoria compartida.

El segundo subproceso compartirá datos, archivos abiertos, controladores de señales, estados de las señales, directorio de trabajo actual, ID de usuario y grupo, etc.

Sin embargo, el nuevo subproceso obtendrá su propia pila, ID de subproceso y registros.