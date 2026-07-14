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


                    if(actual[i].tamaño != anterior[j].tamaño || actual[i].modificacion != anterior[j].modificacion)
                    {

                        fprintf(stderr, "\nENTRO AL CAMBIO\n");

                        fprintf(stderr, "Cambio detectado: %s\n", actual[i].ruta);

                        fprintf(stderr, "Nombre: %s\n", actual[i].nombre);

                        fprintf(stderr, "Tamano: %ld\n", actual[i].tamaño);

                        fprintf(stderr, "Modificacion: %ld\n", actual[i].modificacion);


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
