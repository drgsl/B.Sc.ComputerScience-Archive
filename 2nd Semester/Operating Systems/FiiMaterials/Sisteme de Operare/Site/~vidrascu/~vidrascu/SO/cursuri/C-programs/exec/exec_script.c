/*
*  Program: exec_script.c, care va apela, cu execl, un script bash (!)
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


int main(int argc, char* argv[])
{
    printf("Apelam prin execv un script bash, care isi va lista parametrii cu care a fost apelat!\n");
    printf("-------------------------------------------------------------------------------------\n");

    /* Reacoperirea cu un script bash. */
    execv("my_script.sh",argv);


    /* Se va executa numai dacă eșuează apelul exec !!! */
    perror("Eroare la apelul execv");
    return 1;
}

