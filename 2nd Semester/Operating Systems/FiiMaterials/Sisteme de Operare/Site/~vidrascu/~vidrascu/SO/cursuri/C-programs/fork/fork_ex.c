/*
* Program: fork-ex.c
*
* Funcționalitate: ilustrează șablonul pentru crearea unui proces fiu, al procesului curent.
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid_fiu;
    int   nr = 0;

    /* Crearea unui proces fiu. */
    if(-1 == (pid_fiu=fork()) )
    {
        perror("Eroare la fork");
        return 1;
    }

    /* Ramificarea execuției... */
    if(pid_fiu == 0)
    {   /* Secvență de cod ce va fi executată doar de către procesul fiu. */

        printf("\nProcesul fiu cu PID-ul: %d , avand parintele cu PID-ul: %d.\n",getpid(),getppid());
        printf("In procesul fiu: dupa apelul fork, variabila nr are initial valoarea: %d.\n", nr);
        nr = 5;
        printf("In procesul fiu: dupa modificarea ei, variabila nr are valoarea: %d.\n", nr);
    }
    else
    {   /* Secvență de cod ce va fi executată doar de către procesul părinte. */

        printf("\nProcesul tata cu PID-ul: %d , avand parintele cu PID-ul: %d si un fiu cu PID-ul: %d.\n", getpid(), getppid(), pid_fiu );
        sleep(2);
        printf("In procesul tata, dupa 2 secunde: variabila nr are valoarea: %d.\n", nr);
    }

    /* Secvență de cod comună, executată de către ambele procese. */
    printf("Zona de cod comuna, executata de catre %s.\n\n", pid_fiu == 0 ? "fiu" : "parinte" );
    return 0;
}
