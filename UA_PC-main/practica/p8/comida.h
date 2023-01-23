// P7 - Practicas de Programación Concurrente 
// Problema de la comida de los filósofos con monitores
// Elvi Mihai Sabau Sabau - 51254875L

#ifndef _MESA_H_

    #define _MESA_H_
    #include <sys/types.h>
    #include <pthread.h>

    #define NUM_FILOSOFOS 5

    // Definimos una macro para inicializar la mesa, con todos los palillos disponibles, las variables condicionantes, y el mutex.
    #define INIT_MESA {{[0 ... (NUM_FILOSOFOS - 1)] = 2}, {[0 ... (NUM_FILOSOFOS - 1)] = PTHREAD_COND_INITIALIZER}, PTHREAD_MUTEX_INITIALIZER}

    // Struct que contiene la información de la mesa.
    typedef struct mesa {

        // Numero de palillos disponibles de cada filosofo.
        int palillos[NUM_FILOSOFOS];

        // Variable condicionante de cada filosofo.
        pthread_cond_t pueden_comer[NUM_FILOSOFOS];

        // Mutex para el acceso a la mesa.
        pthread_mutex_t seccion_critica;

    } mesa_t;

    // Funciones para usar los palillos.
    int palillo_der(int id);
    int palillo_izq(int id);

    void coger_palillo(mesa_t *c, int id);
    void dejar_palillo(mesa_t *c, int id);

#endif