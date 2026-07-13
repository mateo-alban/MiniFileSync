#include "worker.h"

#include "copy.h"
#include "logger.h"
#include "stats.h"


#include <stdio.h>
#include <unistd.h>
#include <string.h>



void iniciarWorker(
    int pipeLectura
)
{

    char archivo[512];



    while(1)
    {


        int bytes = read(
            pipeLectura,
            archivo,
            sizeof(archivo)-1
        );



        if(bytes > 0)
        {


            archivo[bytes] = '\0';



            printf(
                "Worker copiando: %s\n",
                archivo
            );



            char destino[512];



            char *nombre =
                strrchr(
                    archivo,
                    '/'
                );



            if(nombre != NULL)
            {
                nombre++;
            }
            else
            {
                nombre = archivo;
            }



           snprintf(destino,sizeof(destino),"backu/%.500s", nombre);



            copiarArchivo(
                archivo,
                destino
            );



            registrarCopia(
                archivo
            );



            escribirLog(
                "Archivo sincronizado correctamente\n"
            );


        }


    }


}