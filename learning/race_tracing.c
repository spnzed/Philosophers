#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int condicionDeCarrera = 0;

void *miHilo(void *arg) {
    usleep(1000);

    // Eliminamos el bloqueo del mutex antes de entrar a la sección crítica
    pthread_mutex_lock(&mutex);

    if (condicionDeCarrera == 0) {
        printf("¡Carrera detectada! El hilo secundario entró en la sección crítica sin bloquear el mutex.\n");
        condicionDeCarrera = 1;
    }

    printf("¡Hola! Soy el hilo secundario.\n");
    printf("¡Estoy emocionado por aprender sobre threads y mutex!\n");

    // Eliminamos el desbloqueo del mutex después de salir de la sección crítica
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t hilo;

    printf("¡Hola! Soy el hilo principal.\n");

    int resultado = pthread_create(&hilo, NULL, miHilo, NULL);

    if (resultado != 0) {
        fprintf(stderr, "Error al crear el hilo: %d\n", resultado);
        exit(EXIT_FAILURE);
    }

    // Eliminamos el bloqueo del mutex antes de entrar a la sección crítica
    pthread_mutex_lock(&mutex);

    printf("¡Estoy dentro de la sección crítica en el hilo principal!\n");

    // Eliminamos el desbloqueo del mutex después de salir de la sección crítica
    pthread_mutex_unlock(&mutex);

    resultado = pthread_join(hilo, NULL);

    if (resultado != 0) {
        fprintf(stderr, "Error al hacer join con el hilo: %d\n", resultado);
        exit(EXIT_FAILURE);
    }

    if (condicionDeCarrera == 0) {
        printf("El hilo secundario no experimentó una condición de carrera. Hasta luego.\n");
    }

    exit(EXIT_SUCCESS);
}
