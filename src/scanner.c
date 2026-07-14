#include "scanner.h"


#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>



int obtenerArchivos(const char *ruta, ArchivoInfo archivos[],int max)
{

    DIR *directorio;


    struct dirent *entrada;


    struct stat info;



    int cantidad = 0;



    directorio = opendir(ruta);



    if(directorio == NULL)
    {
        return 0;
    }



    while((entrada = readdir(directorio)) != NULL && cantidad < max)
    {


        if(strcmp(entrada->d_name,".") == 0 || strcmp(entrada->d_name,"..") == 0)
        {
            continue;
        }



        char rutaCompleta[512];


        snprintf(rutaCompleta, sizeof(rutaCompleta), "%s/%s", ruta, entrada->d_name);



        stat( rutaCompleta, &info);



        strcpy( archivos[cantidad].nombre, entrada->d_name);



        strcpy( archivos[cantidad].ruta, rutaCompleta);



        archivos[cantidad].tamano = info.st_size;


        archivos[cantidad].modificacion = info.st_mtime;


        archivos[cantidad].inodo = info.st_ino;


        archivos[cantidad].permisos = info.st_mode & 0777;


        archivos[cantidad].propietario = info.st_uid;


        archivos[cantidad].grupo = info.st_gid;



        if(S_ISDIR(info.st_mode))
        {
            archivos[cantidad].tipo = 1;
        }
        else
        {
            archivos[cantidad].tipo = 0;
        }



        cantidad++;

    }



    closedir(directorio);



    return cantidad;

}