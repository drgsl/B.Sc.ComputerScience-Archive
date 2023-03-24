/*
* Filename: bin2txt_read-file.c
*
* Un program demonstrativ, care afișează pe ecran reprezentarea textuală a numerelor citite dintr-un fișier,
* numere ce sunt stocate în format binar, în fișierul de date specificat.
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
    int nr,fd,rcod;

    // step 1: verificare apelare cu (minim) un argument.
    char nume_fisier[PATH_MAX];

    if(argc == 1)
    {
        printf("Introduceti numele fisierului ce se va citi/procesa: ");
        scanf("%s", nume_fisier);
    }
    else
    {
        strcpy(nume_fisier, argv[1]);
    }

    // step 2: deschiderea fișierului specificat.
    if (-1 == (fd = open(nume_fisier,O_RDONLY)) )
    {
        perror("Eroare la deschiderea fisierului de date");  exit(1);
    }

    // step 3: bucla de procesare -- se citesc numere întregi din fișier, în format binar, și se afișează pe ecran (stdout), în format textual.
    printf("Secventa de numere din fisierul de date este urmatoarea:\n");
    while(1)
    {
        if (-1 == (rcod = read(fd,&nr,sizeof(int))) )
        {
            perror("Eroare la citirea din fisierul de date");  exit(2);
        }
        if (0 == rcod) break; // am ajuns la EOF în fișier

        printf("%d , ", nr);
    }
    printf("EndOfSequence!\n\n");

    close(fd);
    return 0;
}
