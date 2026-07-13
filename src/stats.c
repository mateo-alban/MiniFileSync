#include "stats.h"


#include <stdio.h>
#include <pthread.h>



int archivosCopiados = 0;

long bytesCopiados = 0;

int errores = 0;



pthread_mutex_t mutex =
PTHREAD_MUTEX_INITIALIZER;



void registrarCopia(
    const char *archivo
)
{

    pthread_mutex_lock(
        &mutex
    );


    archivosCopiados++;


    pthread_mutex_unlock(
        &mutex
    );

}



void registrarBytes(
    long bytes
)
{

    pthread_mutex_lock(
        &mutex
    );


    bytesCopiados += bytes;


    pthread_mutex_unlock(
        &mutex
    );

}



void registrarError()
{

    pthread_mutex_lock(
        &mutex
    );


    errores++;


    pthread_mutex_unlock(
        &mutex
    );

}



void mostrarEstadisticas()
{

    pthread_mutex_lock(
        &mutex
    );


    printf(
        "\n========== ESTADISTICAS ==========\n"
    );


    printf(
        "Archivos copiados: %d\n",
        archivosCopiados
    );


    printf(
        "Bytes copiados: %ld\n",
        bytesCopiados
    );


    printf(
        "Errores: %d\n",
        errores
    );


    printf(
        "==================================\n"
    );


    pthread_mutex_unlock(
        &mutex
    );

}