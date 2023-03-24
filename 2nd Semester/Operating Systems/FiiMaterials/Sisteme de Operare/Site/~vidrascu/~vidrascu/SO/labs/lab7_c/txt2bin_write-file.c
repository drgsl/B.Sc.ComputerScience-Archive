/*
* Filename: txt2bin_write-file.c
*
* Un program demonstrativ, care citește de la tastatură o secvență de numere întregi, introduse prin reprezentarea lor textuală,
* și le stochează în format binar, în fișierul de date specificat.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>  // necesar pentru PATH_MAX

int main(int argc, char *argv[])
{
    unsigned int i;
    int n,nr,fd;

    // step 1: verificare apelare cu (minim) un argument.
    char nume_fisier[PATH_MAX];

    if(argc == 1)
    {
        printf("Introduceti numele fisierului ce se va crea/suprascrie: ");
        scanf("%s", nume_fisier);
    }
    else
    {
        strcpy(nume_fisier, argv[1]);
    }

    // step 2: crearea fișierului specificat, respectiv trunchierea lui în caz că exista deja.
    if (-1 == (fd = creat(nume_fisier,0600)) )
    {
        perror("Eroare la crearea fisierului de date");  exit(1);
    }

    // step 3: bucla de procesare -- se citesc numere întregi de la tastatură (stdin), în format textual, și se salvează în fișier, în format binar.
    printf("Introduceti lungimea secventei de numere: ");
    if( 1 != scanf("%d", &n) )  {  fprintf(stderr, "Error: incorrect format for an integer number!\n"); exit(EXIT_FAILURE);  }
    if( n <= 0 )  {  fprintf(stderr, "Error: you need to input a strictly positive integer number!\n"); exit(EXIT_FAILURE);  }    

    for(i = 0; i < n; i++)
    {
        printf("Introduceti al %d-lea numar: ",i);   // Citim de la tastatură câte un număr, ...
        if( 1 != scanf("%d", &nr) )  {  fprintf(stderr, "Error: incorrect format for an integer number!\n"); exit(EXIT_FAILURE);  }

        if(-1 == write(fd, &nr, sizeof(int)) )  // ... și "scriem" în fișier acel număr (i.e., cel de-al i-lea număr)
        {
            perror("Eroare la scrierea in fisierul de date");  exit(2);
        }
    }

    close(fd);
    return 0;
}
