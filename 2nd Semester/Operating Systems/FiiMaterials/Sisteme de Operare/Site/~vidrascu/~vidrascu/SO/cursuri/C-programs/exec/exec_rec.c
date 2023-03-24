/*
*  Program: exec-rec.c  (exemplu de apel recursiv prin exec)
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char* argv[], char* env[])
{
    char **r, *s, *w[5];
	
    /* Afișăm environment-ul și linia de comandă, cu care a fost apelată instanța curentă de execuție a acestui program. */
    printf("PID=%d, PPID=%d, OWNER=%d\n",getpid(),getppid(),getuid());
    printf("ENVIRONMENT:\n");
    r=env;
    while(1)
    { 
         s=*r++;
         if(s == NULL) break;
         printf("%s\n",s);
    }
    putchar('\n');

    /* Modificăm environment-ul și linia de comandă, pentru apelul recursiv. */
    env[0]="Salut!";
    env[1]=NULL;

    w[0]=argv[0]; /* Acesta e numele executabilului ! */
    w[1]="2nd call"; // Vom folosi acest caracter '2' pentru o detecție simplă a faptului că nu mai suntem în prima instanță de execuție a acestui program.
    w[2]=NULL;

    /* Folosind una dintre valorilor modificate (indicată mai sus), vom evita recursia la infinit !!! */
    if( (argv[1] != NULL) && (argv[1][0] == '2') )
    {
         exit(0); /* Astfel, oprim recursia la al doilea apel ! */
    }
    else
    {
        printf("Urmeaza apelul primitivei exec.\n");
        if( execve(argv[0], w, env) == -1)
        {
            perror("Eroare la apelul execve");
            exit(1);
        }
    }
    return 0;
}
