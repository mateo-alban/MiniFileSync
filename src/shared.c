#include "shared.h"

#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


#define SHARED_NAME "/minifilesync_stats"



typedef struct
{

    int archivos;

    long bytes;

    int errores;


} DatosCompartidos;



DatosCompartidos *datos;



void iniciarMemoriaCompartida()
{

    int fd;


    fd = shm_open(
        SHARED_NAME,
        O_CREAT | O_RDWR,
        0666
    );


    if(fd < 0)
    {
        exit(1);
    }



    ftruncate(
        fd,
        sizeof(DatosCompartidos)
    );



    datos = mmap(
        NULL,
        sizeof(DatosCompartidos),
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd,
        0
    );



    datos->archivos = 0;

    datos->bytes = 0;

    datos->errores = 0;


}



void cerrarMemoriaCompartida()
{

    munmap(
        datos,
        sizeof(DatosCompartidos)
    );


    shm_unlink(
        SHARED_NAME
    );

}