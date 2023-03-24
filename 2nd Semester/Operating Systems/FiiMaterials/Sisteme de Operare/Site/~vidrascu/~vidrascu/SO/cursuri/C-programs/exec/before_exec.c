/*
*  Program: before_exec.c, care va apela, cu execl, programul after_exec.c
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>  // necesar pentru PATH_MAX

char tab_ref[PATH_MAX];

int main()
{
    printf("Caracteristici inainte de exec\n");
    printf("------------------------------\n");
    printf("ID-ul procesului : %d\n",getpid());
    printf("ID-ul parintelui : %d\n",getppid());
    printf("Proprietarul real : %d\n",getuid());
    printf("Proprietarul efectiv : %d\n",geteuid());
    printf("Directorul curent de lucru : %s\n\n",getcwd(tab_ref,PATH_MAX));

    /* Cerere de închidere a intrării standard la reacoperire. */
    fcntl(STDIN_FILENO, F_SETFD, FD_CLOEXEC);

    /* Reacoperirea cu programul after_exec. */
    execl("after_exec.exe","after_exec",NULL);


    /* Se va executa numai dacă eșuează apelul exec !!! */
    perror("Eroare la apelul execl");
    return 1;
}

