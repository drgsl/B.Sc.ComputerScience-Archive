/*
* Program: info-ex.c
*
* Funcționalitate: ilustrează câteva dintre apelurile ce oferă diverse informații despre procesul curent.
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    printf("\nProcesul curent are PID-ul: %d , iar parintele lui este procesul cu PID-ul: %d.\n\n", getpid(), getppid() );

    printf("Proprietarul real al procesului curent este: UID=%d, GID=%d.\n", getuid(), getgid() );
    printf("Proprietarul efectiv al procesului curent  : UID=%d, GID=%d.\n\n", geteuid(), getegid() );

    printf("Start of sleeping for 3 seconds...\n\n");
    sleep(3);
    printf("Finish of sleeping for 3 seconds!\n");
    return 0;
}
