/*
* Program: wait-ex2.c
*
* Funcționalitate: ilustrează terminarea anormală (cu abort) a fiului creat de procesul inițial.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid_fiu;

    /* Crearea unui proces fiu. */
    if(-1 == (pid_fiu=fork()) ) { perror("Eroare la fork"); return 1; }

    /* Ramificarea execuției... */
    if (pid_fiu == 0)
    {   /* Secvență de cod ce va fi executată doar de către procesul fiu. */

        printf("\nProcesul fiu, cu PID-ul: %d.\n", getpid());

        abort();  /* Terminare anormală, cu semnalul SIGABRT */
    }
    else
    {   /* Secvență de cod ce va fi executată doar de către procesul părinte. */
        int cod_term;

        pid_fiu = wait(&cod_term);
        printf("\nProcesul tata: fiul cu PID-ul %d s-a sfarsit cu status-ul: %d.\n", pid_fiu, cod_term);

        /* Ilustrarea folosirii macro-urilor de inspecție a valorii stocate de apelul wait() în variabila cod_term ... */
        if( WIFSIGNALED(cod_term) )
            printf("Mai exact, fiul a fost terminat fortat, cu semnalul: %d.\n", WTERMSIG(cod_term) );
        if( WIFEXITED(cod_term) )
            printf("..., iar codul de terminare al fiului este: %d.\n", WEXITSTATUS(cod_term) );

        return 0;
    }
}
