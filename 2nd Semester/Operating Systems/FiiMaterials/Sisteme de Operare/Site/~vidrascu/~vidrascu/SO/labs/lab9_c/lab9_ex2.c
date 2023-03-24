/*
  Program: șablonul de creare a N fii ai procesului curent, varianta iterativă.
*/
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int N=0, i, codterm;
    pid_t pid;

    /* Obținerea parametrului de intrare N. */
    if(argc < 2)
    {
        printf("Introduceti numarul de procese: ");
        while( (1 != scanf("%d", &N)) && (N < 1) ) { fprintf(stderr,"\nEroare: nu ati introdus un numar intreg strict pozitiv! Incercati din nou..."); }
    }
    else
    {
        if(1 != sscanf(argv[1],"%d", &N)) { fprintf(stderr,"Eroare: nu ati specificat un numar intreg strict pozitiv!\n");  exit(1); }
    }

    /* Bucla de producere a celor N procese "înlănțuite". */
    for(i = 1; i < N; i++)
    {
        if(-1 == (pid=fork()) )
        {
            perror("Eroare la fork");  exit(2);
        }

        if(0 != pid)
        {
            wait(&codterm); // Aici fiecare proces va aștepta terminarea procesului fiu direct, ca să-i obțină codul de terminare
                /* Notă: chiar dacă nu se cerea afișarea codului de terminare, tot ar fi nevoie aici de un apel wait(NULL); (!)
                   Altfel, câteodată (i.e., nu neapărat la toate execuțiile) este posibil ca unele procese să apară ca fiind orfane (i.e.,
                   având drept părinte procesul cu PID-ul 1).  */

            // printf("Sunt procesul %d din lantul de procese, avand PID-ul: %d, parintele meu este procesul cu PID-ul: %d, iar fiul creat de mine "
            //       "are PID-ul: %d si s-a terminat cu codul de terminare: %d.\n", i, getpid(), getppid(), pid, codterm >> 8 );

            /* Afișare prescurtată: */
            printf("Sunt procesul %d, avand PID-ul: %d, parintele are PID-ul: %d, iar fiul creat are PID-ul: %d si s-a terminat cu codul: %d.\n",
                        i, getpid(), getppid(), pid, codterm>>8 );

            return i;  // Important: tatăl nu trebuie săa reia execuția buclei for, ca să nu creeze un al doilea proces fiu direct, apoi un al treilea, ș.a.m.d.
        }
        else
        {
            if(i == N-1)  // Acesta este ultimul proces din lanț, care nu va crea un proces fiu.
            {
                printf("Sunt procesul ultim, %d din lantul de procese, avand PID-ul: %d, iar parintele meu este procesul cu PID-ul: %d.\n", N, getpid(), getppid() );
                return N;
            }
        }

    }//end for

    return 0;
}
