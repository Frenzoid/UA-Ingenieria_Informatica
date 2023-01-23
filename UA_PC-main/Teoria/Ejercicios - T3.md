Elvi Mihai Sabau Sabau - 51254875L

#### Indicar las condiciones exigidas por los protocolos de E/S a una correcta solución al problema de la exclusión mutua

  - Condicion de no inanición.
  - Condicion de progreso de la ejecución.

#### Formular varios problemas donde se requieran condiciones de sincronización
  
  - Problema de los productores y consumidores.
  - Problema de los fumadores.
  - Problema de los filósofos.

#### ¿A qué hace referencia el término espera ocupada?
  - Es cuando un proceso se encuentra en espera activa, es decir, no se bloquea, sino que se queda en un bucle infinito comprobando si se ha producido la condición de espera. 

#### ¿Cuál es el principal inconveniente de las soluciones basadas en espera ocupada?
  - El principal inconveniente es que el proceso que está en espera ocupada no puede realizar ninguna otra tarea, por lo que se está perdiendo tiempo de procesamiento.


#### Explicar por qué el algoritmo de Lamport no presenta espera ilimitada
  - El algoritmo de Lamport no presenta espera ilimitada porque cada proceso tiene un número de identificación, y cada proceso sólo puede solicitar el recurso si el número de identificación es el siguiente al que tiene el recurso. Por lo tanto, si un proceso tiene el recurso, sólo puede solicitarlo de nuevo si el siguiente proceso en solicitarlo es el suyo. Por lo tanto, no hay espera ilimitada.
