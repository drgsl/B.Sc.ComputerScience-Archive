/*
*  Program: redirect.c
*/
#include <unistd.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
  
int main()
{
    char *str1 = "Primul mesaj; va apare pe ecran.\n";
    write(1,str1,strlen(str1));
  

    /* Urmează redirectarea fluxului stdout către un fișier. */
    int fd;
    if(-1 == (fd = creat("fis.txt",0600)) ) {
        perror("Deschiderea fisierului a esuat. Motivul:");
        exit(1);
    }
    close(1);  /* Închidem descriptorul 1, "asociat" fluxului stdout. */
    if(-1 == dup2(fd,1))  /* Duplicăm fd cu 1 (i.e., intrarea 1, din tabelul local cu sesiuni de lucru cu fișiere,
                	         va fi asignată să refere aceeași sesiune din tabelul global, ca și intrarea fd. */
    {
        perror("Redirectarea a esuat. Motivul:");
        exit(2);
    }
    close(fd); /* Închidem descriptorul fd, de care nu mai avem nevoie. */
 
    /* Practic, astfel am redirectat fluxul stdout către fișierul fis.txt ! */

    char *str2 = "Al doilea mesaj scris pe stdout; va apare nu pe ecran, ci in fisier.\n";
    write(1,str2,strlen(str2));
  

    /* Urmează "anularea" redirectării realizată anterior. */
    int fd1;
    if(-1 == (fd1=open("/dev/tty",O_WRONLY)) ) {
        perror("Deschiderea terminalului a esuat. Motivul:");
        exit(3);
    }
    close(1);  /* Închidem descriptorul 1, "asociat" fluxului stdout. */
    if(-1 == dup2(fd1,1))   /* duplic fd1 cu 1 */
    {
        perror("Re-redirectarea a esuat. Motivul:");
        exit(4);
    }
    close(fd1); /* Închidem descriptorul fd1, de care nu mai avem nevoie. */
  
    char *str3 = "Al treilea mesaj; va apare pe ecran.\n";
    write(1,str3,strlen(str3));

    return 0;
}
