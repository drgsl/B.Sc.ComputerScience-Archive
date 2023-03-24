/*
*   Program: pipe_capacity.c
*
*   Funcționalitate: calculează capacitatea unui pipe (i.e., canal anonim) pe sistemul Linux folosit.
*/

#define _GNU_SOURCE  // Este necesară această definiție, înaintea includerii oricăror headere (!!!), pentru definirea constantei F_GETPIPE_SZ.
// _GNU_SOURCE is a Linux glibc feature test macro (See: man 7 feature_test_macros)

#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


int main(void)
{
    int p[2], count = 0;
    char ch = 'A';

    /* Creare pipe. */
    if(-1 == pipe(p) )
    {  perror("Eroare la crearea canalului anonim. Cauza erorii");  exit(1);  }

    /* Setare comportament non-blocking pentru capătul de scriere. */
	if(-1 == fcntl(p[1], F_SETFL, O_NONBLOCK) )
	{  perror("Eroare la setarea non-blocking. Cauza erorii");  exit(2);  }

    /* Bucla de umplere a canalului... */
    printf("Începem să scriem în canalul anonim, până la umplerea sa!\n\nProgresul scrierii: ");
    while(1)
    {
        if(-1 == write(p[1],&ch,1) )
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

    printf("\nCapacitatea, calculată, a canalului anonim este de %d octeti.\n\n", count);

    sleep(3);
    int capacity = fcntl(p[1], F_GETPIPE_SZ);

    if(-1 == capacity)
    {
        if(errno == EINVAL)
        {  fprintf(stderr,"Versiunea de Linux de pe sistemul dvs. nu suporta operatia F_GETPIPE_SZ in apelul fcntl !\n");  exit(4);  }
        else
        {  perror("Eroare la apelul fcntl(..., F_GETPIPE_SZ); datorita cauzei");  exit(5);  }
    }
    else
        printf("Capacitatea, aflată cu fcntl(), a canalului anonim este de %d octeti.\n", capacity);

    sleep(1);
    printf("\nMaximum configurable pipe size for unprivileged user is (in bytes): "); fflush(stdout);
    system("cat /proc/sys/fs/pipe-max-size");
    long PageSize = sysconf(_SC_PAGE_SIZE);
    printf("\nMinimum configurable pipe size for unprivileged user is the page size, i.e. %ld bytes.\n\n", PageSize);

    sleep(3);
    printf("Încercăm să reconfigurăm capacitatea canalului la o valoare, e.g. %ld octeți, mai mică decât cea curentă.\n" , 5 * PageSize);

    if(-1 == fcntl(p[1], F_SETPIPE_SZ, 5 * PageSize) )
    {
       perror("Eroare la prima reconfigurare a capacitatii canalului");
       fprintf(stderr,"Încercarea a eșuat, cu eroarea EBUSY, deoarece canalul era deja plin cu 64 KB, i.e. 65536 octeți, de informații !!!\n\n");
    }

    sleep(3);
    printf("Încercăm să reconfigurăm capacitatea canalului la o valoare, e.g. %ld octeți, mai mare decât cea curentă.\n" , 20 * PageSize);

    if(-1 == fcntl(p[0], F_SETPIPE_SZ, 20 * PageSize) )
    {  perror("Eroare la a doua reconfigurare a capacitatii canalului");  exit(6);  }

    sleep(1);
    int new_pipe_size = fcntl(p[1], F_GETPIPE_SZ);
    if(-1 == new_pipe_size)
    {  perror("Eroare la aflarea noii capacitati a canalului");  exit(7);  }

    printf("Noua capacitate a canalului anonim, dupa reconfigurarea reusita, este de %d octeti.\n\n", new_pipe_size);

    close(p[0]);
    close(p[1]);
    return 0;
}

