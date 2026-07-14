#include "daemon.h"
#include "pid.h"
#include "control.h"
#include "monitor.h"
#include "logger.h"
#include "shared.h"

#include <string.h>
#include <stdio.h>


int main(
    int argc,
    char *argv[]
)
{

    if(argc > 1)
    {

        if(strcmp(argv[1], "stop") == 0)
        {
            detenerDaemon();
            return 0;
        }

    }





    crearPID();



    iniciarLogger();



    iniciarMemoriaCompartida();



    iniciarMonitor("test");



    return 0;

}