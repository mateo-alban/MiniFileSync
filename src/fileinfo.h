#ifndef FILEINFO_H
#define FILEINFO_H
#include <sys/types.h>


typedef struct
{

    char nombre[256];
    char ruta[512];

    long tamano;
    long modificacion;

    ino_t inodo;

    mode_t permisos;

    uid_t propietario;

    gid_t grupo;

    int tipo;


} ArchivoInfo;

#endif