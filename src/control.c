#include "control.h"

#include <stdio.h>
#include <signal.h>
#include <unistd.h>


#define PID_FILE "/tmp/MiniFileSync.pid"



void detenerDaemon()
{

    FILE *archivo;

    int pid;



    archivo = fopen(
        PID_FILE,
        "r"
    );


    if(archivo == NULL)
    {
        return;
    }



    fscanf(
        archivo,
        "%d",
        &pid
    );


    fclose(archivo);



    kill(
        pid,
        SIGTERM
    );



    unlink(
        PID_FILE
    );

}