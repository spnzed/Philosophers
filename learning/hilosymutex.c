#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Definir un mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Función que se ejecutará en el hilo secundario
void *miHilo(void *arg) {
    // Bloquear el mutex antes de entrar a la sección crítica
    pthread_mutex_lock(&mutex);

    printf("¡Hola! Soy el hilo secundario.\n");
    printf("¡Estoy emocionado por aprender sobre threads y mutex!\n");

    // Desbloquear el mutex después de salir de la sección crítica
    pthread_mutex_unlock(&mutex);

    // La función debe devolver un puntero (en este caso, no necesitamos devolver nada)
    return NULL;
}

int main() {
    // Identificador del hilo
    pthread_t hilo;

    printf("¡Hola! Soy el hilo principal.\n");

    // Crear el hilo secundario
    int resultado = pthread_create(&hilo, NULL, miHilo, NULL);

    // Verificar si la creación del hilo fue exitosa
    if (resultado != 0) {
        fprintf(stderr, "Error al crear el hilo: %d\n", resultado);
        exit(EXIT_FAILURE);
    }

    // Bloquear el mutex antes de entrar a la sección crítica
    pthread_mutex_lock(&mutex);

    printf("¡Estoy dentro de la sección crítica en el hilo principal!\n");

    // Desbloquear el mutex después de salir de la sección crítica
    pthread_mutex_unlock(&mutex);

    // Esperar a que el hilo secundario termine
    resultado = pthread_join(hilo, NULL);

    // Verificar si el join fue exitoso
    if (resultado != 0) {
        fprintf(stderr, "Error al hacer join con el hilo: %d\n", resultado);
        exit(EXIT_FAILURE);
    }

    printf("¡El hilo secundario ha terminado! Hasta luego.\n");

    // Terminar el programa
    exit(EXIT_SUCCESS);
}
