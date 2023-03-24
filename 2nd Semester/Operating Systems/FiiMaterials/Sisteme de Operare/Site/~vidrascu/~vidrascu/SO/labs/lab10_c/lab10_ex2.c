/*
*  Program: soluția pentru varianta de la pct. i) din enunțul problemei [Exec command #2: last]
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int cod_term;

    if(argc != 2)
    {
        fprintf(stderr,"Programul trebuie apelat cu un parametru (un nume de utilizator).\n");  exit(1);
    }

    /* Creez un proces fiu, care va rula comanda last prin exec. */
    switch( fork() )
    {
        case -1:  perror("Eroare la fork");
                  exit(2);

        case  0:  /* În procesul fiu apelez exec pentru a executa comanda dorită. */
                  execlp("last","last","--limit","10","-F",argv[1],NULL);
                  perror("Eroare la exec");
                  exit(10); // Aici folosesc un numar mai mare, e.g. 10, și nu 1,2,... căci aceste valori mici ar putea fi returnate și de către comanda last !

        default:  /* (Doar în procesul părinte) Acum cercetez cum s-a terminat procesul fiu. */
                  wait(&cod_term);

                  if( WIFEXITED(cod_term) )
                  {
                      switch( WEXITSTATUS(cod_term) )
                      {
                          case 10:  printf("Comanda last nu a putut fi executata... (apelul exec a esuat).\n");  break;
                          case  0:  printf("Comanda last a fost executata cu succes!\n");  break;
                          default:  printf("Comanda last a fost executata, dar a esuat, terminandu-se cu codul de terminare: %d.\n", WEXITSTATUS(cod_term) );
                      }
                  }
                  else
                  {
                      printf("Comanda last a fost terminata fortat de catre semnalul: %d.\n", WTERMSIG(cod_term) );
                  }
    }
    return 0;
}
