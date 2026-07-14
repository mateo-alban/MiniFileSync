#include "logger.h"


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>



#define FIFO "minifilesync_fifo"



void iniciarLogger()
{

    mkfifo(FIFO, 0666);

}



void escribirLog(const char *mensaje)
{

    int fd;


    fd = open(FIFO, O_WRONLY | O_NONBLOCK);



    if(fd < 0)
    {
        return;
    }



    write(fd,mensaje,strlen(mensaje));



    close(fd);

}