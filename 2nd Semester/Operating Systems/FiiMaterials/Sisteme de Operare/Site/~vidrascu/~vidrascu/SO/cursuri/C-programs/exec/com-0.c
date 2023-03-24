/*
*  Program: com-0.c
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    int fd;

    /* Redirectăm fluxul stdout în fișierul fis.txt */
    if(-1 == (fd = creat("fis.txt",0600)) )  { perror("Eroare la crearea fisierului"); abort(); }
    close(1);  /* Închidem descriptorul 1, "asociat" fluxului stdout. */
    dup(fd);   /* Duplicăm fd cu 1  (1 fiind, în acest moment, prima intrare gasită liberă, de către functia dup, în tabelul local cu sesiuni de lucru cu fișiere). */
    close(fd); /* Închidem descriptorul fd. */

    /* Scriem pe fluxul stdout, adică în fișier. */
    write(1,"Salut",5);
    execl("com-2","com-2",NULL);


    /* Se va executa numai dacă eșuează apelul exec !!! */
    perror("Eroare la apelul execl");
    return 1;
}
