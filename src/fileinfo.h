#ifndef FILEINFO_H
#define FILEINFO_H


typedef struct
{

    char nombre[256];

    char ruta[512];

    long tamaño;

    long modificacion;

    int tipo;


} ArchivoInfo;


#endif