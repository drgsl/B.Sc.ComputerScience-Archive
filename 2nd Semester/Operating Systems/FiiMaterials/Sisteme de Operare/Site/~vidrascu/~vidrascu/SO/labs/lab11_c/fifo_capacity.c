/*
*   Program: fifo_capacity.c
*
*   Funcționalitate: calculează capacitatea unui fifo (i.e., canal cu nume) pe sistemul Linux folosit.
*/

#define _GNU_SOURCE  // Este necesară această definiție, înaintea includerii oricăror headere (!!!), pentru definirea constantei F_GETPIPE_SZ.
// _GNU_SOURCE is a Linux glibc feature test macro (See: man 7 feature_test_macros)

#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(void)
{
    int fd, count = 0;
    char ch = 'A';

    /* Creare canal fifo. */
    if(-1 == mkfifo("canal",0600) )
    {
        if(errno == EEXIST)  // EEXIST=17 : valoarea lui errno pentru situația "File exists"
        {  fprintf(stdout,"Observatie: fisierul fifo 'canal' exista deja !\n");  }
        else
        {  perror("Eroare la crearea fisierului fifo. Cauza erorii");  exit(1);  }
    }

    /* Deschiderea canalului cu setarea non-blocking, necesară pentru capătul de scriere. */
    if(-1 == (fd = open("canal", O_RDWR | O_NONBLOCK) ) )
    {  perror("Eroare la deschiderea fisierului fifo cu setare non-blocking. Cauza erorii");  exit(2);  }

    /* Bucla de umplere a canalului... */
    printf("Începem să scriem în canalul fifo, până la umplerea sa!\n\nProgresul scrierii: ");
    while(1)
    {
        if(-1 == write(fd,&ch,1) )
        {
            perror("\nEroare (posibil umplere pipe ?). Cauza erorii");
            fprintf(stderr,"errno = %d\n", errno);
            if(errno == EAGAIN)
            {  fprintf(stderr,"Intr-adevar, cauza erorii este umplerea canalului!\n");  break;  }
            else
            {  fprintf(stderr,"Cauza erorii este alta decat umplerea canalului!\n");  exit(3);  }
        }
        else
        {
            count++;
            if(count % 1024 == 0) { printf(" %d Ko ..., ", count/1024); fflush(stdout); usleep(100000); }
        }
    }

    printf("\nCapacitatea, calculată, a canalului fifo este de %d octeti.\n\n", count);

    sleep(3);
    int capacity = fcntl(fd, F_GETPIPE_SZ);

    if(-1 == capacity)
    {
        if(errno == EINVAL)
        {  fprintf(stderr,"Versiunea de Linux de pe sistemul dvs. nu suporta operatia F_GETPIPE_SZ in apelul fcntl !\n");  exit(4);  }
        else
        {  perror("Eroare la apelul fcntl(..., F_GETPIPE_SZ); datorita cauzei");  exit(5);  }
    }
    else
        printf("Capacitatea, aflată cu fcntl(), a canalului fifo este de %d octeti.\n", capacity);

    close(fd);
    return 0;
}

