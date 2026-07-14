#include "daemon.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


void iniciarDaemon()
{

    pid_t pid = fork();


    if(pid < 0)
    {
        exit(EXIT_FAILURE);
    }


    if(pid > 0)
    {
        exit(EXIT_SUCCESS);
    }



    if(setsid() < 0)
    {
        exit(EXIT_FAILURE);
    }



    pid = fork();


    if(pid < 0)
    {
        exit(EXIT_FAILURE);
    }


    if(pid > 0)
    {
        exit(EXIT_SUCCESS);
    }



    chdir("/");



    int fd = open("/dev/null",O_RDWR);


    if(fd != -1)
    {

        close(fd);
    }

}