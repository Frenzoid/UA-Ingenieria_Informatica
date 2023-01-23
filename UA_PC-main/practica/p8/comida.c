// P7 - Practicas de Programación Concurrente 
// Problema de la comida de los filósofos con monitores
// Elvi Mihai Sabau Sabau - 51254875L

#include "comida.h"
#include <stdio.h>

int palillo_der(int id) {
    return (id + NUM_FILOSOFOS - 1) % NUM_FILOSOFOS;
}

int palillo_izq(int id) {
    return (id + 1) % NUM_FILOSOFOS;
}

void coger_palillo(mesa_t *mes, int id) {

    // Bloquear acceso a la mesa.
    pthread_mutex_lock(&mes->seccion_critica);

    // Esperamos hasta tener 2 palillos.
    while(mes->palillos[id] != 2) pthread_cond_wait(&mes->pueden_comer[id], &mes->seccion_critica);

    // Al coger los palillos, los filosofos de nuestros lados tendran un palillo menos cada uno.
    mes->palillos[palillo_izq(id)] -= 1;
    mes->palillos[palillo_der(id)] -= 1;

    printf("El filosofo %d coge los palillos\n", id);

    // Desbloquear acceso a la seccion critica.
    pthread_mutex_unlock(&mes->seccion_critica);
}

void dejar_palillo(mesa_t *mes, int id) {

    // Bloquear acceso a la seccion critica.
    pthread_mutex_lock(&mes->seccion_critica);
    
    printf("El filosofo %d deja los palillos\n", id);

    // Al dejar los palillos, los filosofos de nuestros lados tendran un palillo más cada uno.
    mes->palillos[palillo_izq(id)] += 1;
    mes->palillos[palillo_der(id)] += 1;

    // Si algun filosofo vecino ya puede comer, lo despertamos.
    if (mes->palillos[palillo_izq(id)] == 2) pthread_cond_signal(&mes->pueden_comer[palillo_izq(id)]);
    if (mes->palillos[palillo_der(id)] == 2) pthread_cond_signal(&mes->pueden_comer[palillo_der(id)]);

    // desbloquear acceso a la seccion critica.
    pthread_mutex_unlock(&mes->seccion_critica);
}