/*
  Program: șablonul de creare a unei liste de N procese, varianta recursivă.
*/
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>

int N=0;

void creaza_fiu(int i);
/* Fiecare apel al acestei funcții va crea un singur proces, i.e. va executa un singur apel fork() ! */


int main(int argc, char* argv[])
{
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

    /* Apelul recursiv, ce creează lista celor N procese. */
    creaza_fiu(1);

    return 0;
}

void creaza_fiu(int i)
{
    int codterm;
    pid_t pid;

    if(i < N)
    {
        if(-1 == (pid=fork()) )
        {
            perror("Eroare la fork");  exit(2);
        }

        if(0 != pid)
        {
            wait(&codterm); // Aici fiecare proces va aștepta terminarea prcesului fiu direct, ca să-i obțină codul de terminare.
                /* Notă: chiar dacă nu se cerea afișarea codului de terminare, tot ar fi nevoie aici de un apel wait(NULL); (!)
                   Altfel, câteodată (i.e., nu neapărat la toate execuțiile) este posibil ca unele procese să apară ca fiind orfane (i.e.,
                   având drept părinte procesul cu PID-ul 1). */

            //printf("Sunt procesul %d din lantul de procese, avand PID-ul: %d, parintele meu este procesul cu PID-ul: %d, iar fiul creat de mine "
            //       "are PID-ul: %d si s-a terminat cu codul de terminare: %d.\n", i, getpid(), getppid(), pid, codterm>>8 );

            /* Afișare prescurtată: */
            printf("Sunt procesul %d, avand PID-ul: %d, parintele are PID-ul: %d, iar fiul creat are PID-ul: %d si s-a terminat cu codul: %d.\n",
                    i, getpid(), getppid(), pid, codterm>>8 );

            exit(i); // Important: tatăl nu trebuie să reia execuția buclei for, ca să nu creeze un al doilea proces fiu direct, apoi un al treilea, ș.a.m.d.
        }
        else
        {
            creaza_fiu(i+1);    // apelul recursiv, ce creează următorul proces din "lanț"
        }
    }
    else  // Adică i==N, deci este vorba de ultimul proces din "lanțul de procese", care nu va crea vreun proces fiu.
    {
        printf("Sunt procesul ultim, %d din lantul de procese, avand PID-ul: %d, iar parintele meu este procesul cu PID-ul: %d.\n",
                N, getpid(), getppid() );
        exit(N);
    }
}
