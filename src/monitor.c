#include "monitor.h"


#include "scanner.h"
#include "fileinfo.h"
#include "process.h"
#include "stats.h"
#include "logger.h"


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>



void cerrarPrograma(int signal)
{

    remove( "/tmp/MiniFileSync.pid");


    exit(0);

}




void iniciarMonitor(const char *directorio)
{

    signal( SIGTERM,cerrarPrograma);



    iniciarWorkers();



    ArchivoInfo anterior[100];

    ArchivoInfo actual[100];



    int cantidadAnterior;



    cantidadAnterior = obtenerArchivos(directorio,anterior,100);



    while(1)
    {


        sleep(5);



        printf("\n--- Revisando cambios ---\n");



        int cantidadActual = obtenerArchivos(directorio, actual, 100);



        for(int i = 0; i < cantidadActual; i++)
        {

            for(int j = 0; j < cantidadAnterior; j++)
            {

                if(strcmp(actual[i].ruta, anterior[j].ruta) == 0)
                {


                    if(actual[i].tamano != anterior[j].tamano || actual[i].modificacion != anterior[j].modificacion)
                    {

                        printf("Nombre: %s\n", actual[i].nombre);

                        printf("Inodo: %ld\n", actual[i].inodo);

                        printf("Tamano: %ld bytes\n",actual[i].tamano);

                        printf("Permisos: %o\n",actual[i].permisos);

                        printf("Propietario UID: %d\n", actual[i].propietario);

                        printf("Grupo GID: %d\n",actual[i].grupo);

                        printf("Ultima modificacion: %ld\n",actual[i].modificacion);

                        enviarTrabajo(actual[i].ruta);
                    }

                }


            }


        

    
        }
        memcpy(anterior, actual, sizeof(actual));


        cantidadAnterior = cantidadActual;



        mostrarEstadisticas();


    }

}
