#include "copy.h"

#include "stats.h"


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>



void copiarArchivo( const char *origen,const char *destino)
{

    int entrada;


    int salida;



    char buffer[4096];


    ssize_t bytes;



    entrada = open(origen, O_RDONLY);



    if(entrada < 0)
    {

        registrarError();

        return;

    }



    salida = open( destino,O_WRONLY | O_CREAT | O_TRUNC,0644);



    if(salida < 0)
    {

        close(entrada);

        registrarError();

        return;

    }



    long total = 0;



    while( (bytes = read(entrada, buffer,sizeof(buffer) )) > 0)
    {


        write( salida, buffer,bytes);


        total += bytes;


    }



    close(entrada);


    close(salida);



    registrarBytes(total);



    printf("Archivo copiado: %s\n", destino );


}