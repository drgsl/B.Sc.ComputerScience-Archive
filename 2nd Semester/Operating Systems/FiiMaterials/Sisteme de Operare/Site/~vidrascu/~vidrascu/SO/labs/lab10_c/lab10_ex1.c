/*
  Program: soluția pentru varianta de la pct. i) din enunțul problemei [Exec command #1: ls]
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int cod_term;
    char* dirname;

    dirname = (argc < 2) ? "." : argv[1];

    /* Creez un proces fiu, care va rula comanda ls prin exec. */
    if(-1 == (pid=fork()) )
    {
        perror("Eroare la fork");  exit(1);
    }

    if (pid == 0)
    {
        /* În procesul fiu apelez exec pentru a executa comanda dorită. */
        execlp("ls","ls","-l","-i",dirname,NULL);

        perror("Eroare la exec");
        exit(10); // Aici folosesc un numar mai mare, e.g. 10, și nu 1,2,... căci aceste valori mici ar putea fi returnate și de către comanda ls !
    }

    /* (Doar în procesul părinte) Acum cercetez cum s-a terminat procesul fiu. */

    wait(&cod_term);

    if( WIFEXITED(cod_term) )
    {
        switch( WEXITSTATUS(cod_term) )
        {
            case 10:  printf("Comanda ls nu a putut fi executata... (apelul exec a esuat).\n");  break;
            case  0:  printf("Comanda ls a fost executata cu succes!\n");  break;
            default:  printf("Comanda ls a fost executata, dar a esuat, terminandu-se cu codul de terminare: %d.\n", WEXITSTATUS(cod_term) );
        }
    }
    else
    {
        printf("Comanda ls a fost terminata fortat de catre semnalul: %d.\n", WTERMSIG(cod_term) );
    }

    return 0;
}
