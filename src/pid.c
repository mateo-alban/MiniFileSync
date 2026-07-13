#include "pid.h"

#include <stdio.h>
#include <unistd.h>


#define PID_FILE "/tmp/MiniFileSync.pid"



void crearPID()
{

    FILE *archivo;


    archivo = fopen(
        PID_FILE,
        "w"
    );


    if(archivo == NULL)
    {
        return;
    }



    fprintf(
        archivo,
        "%d\n",
        getpid()
    );



    fclose(archivo);

}