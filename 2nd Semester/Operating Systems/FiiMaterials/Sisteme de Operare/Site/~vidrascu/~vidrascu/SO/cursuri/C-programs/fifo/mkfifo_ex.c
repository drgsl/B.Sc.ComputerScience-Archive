/*
*   Program: mkfifo_ex.c
*
*   Funcționalitate: ilustrează crearea unui canal cu nume (i.e., fișier fifo).
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        fprintf(stderr,"Sintaxa apel: mkfifo_ex nume_fifo\n");  exit(1);
    }

    /* Creăm un fișier fifo cu numele dorit și cu drepturile minimale necesare: doar r și w pentru proprietar. */
    if(-1 == mkfifo(argv[1], 0600) )
    /*
    *  sau, echivalent, putem scrie astfel, folosind apelul general mknod():
    *
    *  if(-1 == mknod(argv[1], S_IFIFO | 0600, 0) )
    */
    {
        if(errno == EEXIST)   // EEXIST=17 : valoarea lui errno pentru situația "File exists" 
        {
           fprintf(stdout,"Observatie: fisierul fifo %s exista deja !\n", argv[1]);
        }
        else
        {
            fprintf(stderr,"Eroare: creare fisier fifo imposibila, errno=%d\n", errno);
            perror("Cauza erorii este");
            exit(2);
        }
    }
    return 0;
}
