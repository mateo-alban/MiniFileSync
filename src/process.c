#include "process.h"

#include "worker.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>



int pipeWorker[2];



void iniciarWorkers()
{

    pipe( pipeWorker);



    pid_t worker1 = fork();



    if(worker1 == 0)
    {

        close(pipeWorker[1]);


        iniciarWorker(pipeWorker[0]);


        exit(0);

    }



    pid_t worker2 = fork();



    if(worker2 == 0)
    {

        close(pipeWorker[1]);


        iniciarWorker(pipeWorker[0]);


        exit(0);

    }



    close(pipeWorker[0]);


}



void enviarTrabajo(const char *archivo)
{

    write(pipeWorker[1],archivo,strlen(archivo) + 1);


}