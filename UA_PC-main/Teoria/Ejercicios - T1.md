ELVI MIHAI SABAU SABAU - 51254875L - 15/10/2022

# Ejercicios - Tema 1

## Ejercicio del apartado 4.1

<i>Usando las condiciones de Bernstein, construye una tabla como la anterior para el siguiente código:</i>

```js
S1 cuad := x * x;
S2 m1 := a * cuad;
S3 m2 := b * x;
S4 z := m1 + m2;
S5 y := z + c;
```

<hr>

Para que dos instrucciones se ejecuten concurrentemente, estas instrucciones no deben depender entre sí. Por ejemplo, si tenemos dos instrucciones que dependen de un mismo registro, estas instrucciones no se pueden ejecutar concurrentemente. En el caso de que las instrucciones no dependan entre sí, estas se pueden ejecutar concurrentemente.

En resumen, una instruccion no debe leer o escribir mientras la otra esté escribiendo en el mismo recurso.

De esto podemos obtener 3 reglas: 

1) No podemos escribir mientras otro proceso lee el mismo recurso.
2) No podemos leer mientras otro proceso escribe el mismo recurso.
3) No podemos escribir mientras otro proceso escribe el mismo recurso.

Aplicando estas reglas al código anterior, podemos obtener la siguiente tabla:

|  |S1|S2|S3|S4|S5|
|:-|:-|:-|:-|:-|:-|
|S1| |N|S|S|S|
|S2| | |S|N|S|
|S3| | | |N|S|
|S4| | | | |N|
|S5| | | | | |

<br>

## Ejercicio del apartado 12

<i>Ejemplo: supongamos que una variable se actualiza con dos funciones que se ejecutan concurrentemente, ¿qué valor tendría x al acabar el programa?</i>

```python

def incrementa_5_A():
  i = 0
  while i < 5:
    i = i + 1;
    x = x + 1;

def incrementa_5_B():
  i = 0
  while i < 5:
    i = i + 1;
    x = x + 1;

```

Si hacemos un análisis de los dos bucles, podemos ver que ambos bucles se ejecutan 5 veces, por lo que el valor de x al finalizar el programa será 10 ( en caso de que no hubiera una condicion de carrera ).

En caso de que la condición de carrera se cumpla, el valor de x al finalizar el programa será entre 5 y 10.

- Ejercicio:
<i>plantea una traza que haría que x valiese 5 al final de la ejecución. ¿Qué rango de valores crees que podría acabar teniendo x ?</i>

Este ejercicio está parcialmente explicado en la respuesta anterior.
El motivo para que x valga 5 es que ambas funciones estén machacando el resultado de cada una en cada iteración.

Para representar la traza, vamos a representarla con una tabla:

|I|A_Lee|B_Lee|A_Escribe|B_Escribe|X|
|:-|:-|:-|:-|:-|:-|
|1|0|0|1|1|1|
|2|1|1|2|2|2|
|3|2|2|3|3|3|
|4|3|3|4|4|4|
|5|4|4|5|5|5|


- Pregunta:
<i>¿De qué problemas de los nombrados en esta sesión adolece el programa?</i>

La exclusión mutua, y las condiciones de carrera.

<hr>

##  Cuestiones breves del punto 13
1) <i> ¿Cuál es la ventaja de la concurrencia en los sistemas monoprocesador?</i>

El aprovechamiento del procesador, ya que en caso de que el procesador esté libre, se puede ejecutar otra tarea, y la velocidad de ejecición de las tareas.

2) <i> ¿Cuáles son las diferencias entre programación concurrente, paralela y distribuida?</i>

La programación concurrente es la ejecución de varias tareas al mismo tiempo, pero en un mismo procesador.

La programación paralela es la ejecución de varias tareas al mismo tiempo, pero en diferentes procesadores.

La programación distribuida es la ejecución de varias tareas al mismo tiempo, pero en diferentes procesadores, y en diferentes máquinas.

3) <i> ¿Cuáles son los dos problemas principales inherentes a la programación concurrente?</i>

Las condiciones de carrera, y la exclusión mutua.

4) <i> ¿Qué es una sección crítica?</i>

Una sección crítica es una sección de código que puede ser ejecutada por varios procesos al mismo tiempo, y por ello puede provocar un error en el programa, por ello, en esta seccion solo puede trabajar un proceso a la vez.

5) <i>¿Cuáles son las características de un programa concurrente?</i>

Orden parcial y Indeterminismo.

5) <i>¿Qué se entiende por un programa concurrente correcto?</i>

Un programa concurrente correcto es aquel que no tiene condiciones de carrera, y que no tiene errores de exclusión mutua, y unas propiedades de vivacidad.