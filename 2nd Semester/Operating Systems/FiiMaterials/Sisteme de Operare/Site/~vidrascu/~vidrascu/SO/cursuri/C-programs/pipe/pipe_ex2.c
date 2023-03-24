/*
*   Program: pipe_ex2.c
*
*   Funcționalitate: demonstrează modul de utilizare a unui pipe (i.e., canal anonim) pentru comunicația unul-la-unul între două procese,
*   folosind funcțiile I/O de nivel înalt (i.e., cele din biblioteca stdio).
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int pid, nr, p[2];
    FILE *fin,*fout;

    /* Creare canal anonim. */
    if(-1 == pipe(p) )
    {
        perror("Eroare la crearea canalului anonim");  exit(1);
    }

    /* Atașăm descriptori de tip FILE* la cei de tip int. */
    fin  = fdopen(p[0],"r");  // capătul de citire
    fout = fdopen(p[1],"w");  // capătul de scriere

    /* Creare proces fiu. */
    if(-1 == ( pid=fork() ) )
    {
        perror("Eroare la crearea unui proces fiu");  exit(2);
    }

    if(pid)
    { /* Secvența de cod executată doar de procesul tată. */

        /* Tatăl își închide capătul de citire din canal. */
        fclose(fin);

        /* Tatăl citește o secvență de numere de la tastatură, terminată cu CTRL+D (i.e., EOF în UNIX/Linux),
        *  și le transmite, prin canal, procesului fiu.
        *  OBSERVAȚIE: în canal numerele sunt scrise folosind reprezentarea 'textuală', nu cea 'binară', și de aceea trebuie separate printr-un caracter
        *  care nu-i cifră (în acest caz am folosit '\n') pentru a nu se "amesteca" cifrele de la numere diferite atunci când sunt citite din canal (!!!) */
        printf("Introduceti o secventa de numere diverse, terminata prin CTRL+D.\n");
        while( EOF != scanf("%d",&nr) )
        {
            fprintf(fout,"%d\n",nr);
            fflush(fout);
        }

        /* Tatăl își închide capătul de scriere în canal, pentru ca fiul să poată citi EOF din canal (!!!) */
        fclose(fout);

        /* Tatăl așteaptă terminarea fiului. */
        wait(NULL);
    }
    else
    { /* Secvența de cod executată doar de procesul fiu. */

        /* Fiul își închide capătul de scriere în canal, pentru ca ulterior să poată citi EOF din canal (!!!) */
        fclose(fout);

        /* Fiul citește numerele din canal și le afișează pe ecran, într-o buclă, până când detectează EOF în canal.
        *  OBSERVAȚIE: conform celor spuse mai sus, caracterul '\n' este folosit ca separator în secvența de numere (!!!) */
        while( fscanf(fin,"%d",&nr) != EOF )
        {
            printf("[Procesul consumator (fiul)] Am primit numarul: %d\n", nr);
            fflush(stdout);
        }

        printf("[Procesul consumator (fiul)] Sfarsit: am citit EOF din canal!\n");

        /* Fiul își închide capătul de citire din canal. */
        fclose(fin);
        /* Observație: aici nu este nevoie obligatoriu de acest fclose explicit,
        *  deoarece oricum toți descriptorii sunt închiși la terminarea programului. */
    }
    return 0;
}

