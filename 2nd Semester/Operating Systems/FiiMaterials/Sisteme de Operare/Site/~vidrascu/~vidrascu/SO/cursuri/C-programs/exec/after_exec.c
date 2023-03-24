/*
*  Program: after_exec.c, care va fi apelat, cu exec, din programul before_exec.c
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>  // necesar pentru PATH_MAX

char tab_ref[PATH_MAX];

int main()
{
    int  nrBytesRead;
    char ch;

    printf("Caracteristici dupa exec\n");
    printf("------------------------\n");
    printf("ID-ul procesului : %d\n",getpid());
    printf("ID-ul parintelui : %d\n",getppid());
    printf("Proprietarul real : %d\n",getuid());
    printf("Proprietarul efectiv : %d\n",geteuid());
    printf("Directorul curent de lucru : %s\n\n",getcwd(tab_ref,PATH_MAX));

    /* Următorul apel va eșua, din motiv de:
       "EBADF - fd is not a valid file descriptor or is not open for reading."
    */ 
    nrBytesRead = read(STDIN_FILENO, &ch, 1);

    printf("Numarul de caractere citite: %d\n",nrBytesRead);
    if( -1 == nrBytesRead )
        perror("Eroare la citirea din fluxul stdin (deoarece este inchisa !) ");

    return 0;
}
