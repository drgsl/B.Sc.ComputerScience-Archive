#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>   // necesar pentru variabila errno si constantele simbolice asociate codurilor numerice de eroare
#include <limits.h>  // necesar pentru PATH_MAX

#define ASCII_SET_SIZE 256

int main (int argc, char* argv[])
{

    // step 1: verificare apelare cu (minim) un argument    
    char nume_fisier[PATH_MAX];

    if(argc == 1)
    {
        // fprintf(stderr,"Argumente insuficiente! Specificati numele fisierului de prelucrat!");  exit(1);

        printf("Dati numele fisierului de prelucrat:");
        scanf("%s", nume_fisier);
    }
    else
    {
        strcpy(nume_fisier, argv[1]);
    }

    // step 2: inițializarea vectorului de apariții
    int vector_ap[ASCII_SET_SIZE], i;

    for(i = 0; i < ASCII_SET_SIZE; i++)
        vector_ap[i] = 0;

    // step 3: procesarea fișierului de intrare

    // sub-step 3a: inițializarea sesiunii de lucru cu fișierul ce trebuie procesat
    int fd;

    fd = open(nume_fisier, O_RDONLY);
    if(fd == -1)
    {
        perror("Eroare la deschiderea fisierului de intrare");
        exit(2);
    }

    // sub-step 3b: bucla de procesare a fișierului de intrare -- se citește câte 1 octet din fișier, la fiecare iterație!
    unsigned char ch;  // 1 octet fără semn!
    int cod_r;

    do{
        cod_r = read(fd, &ch, 1);

        if(cod_r == -1)
        {
            perror("Eroare la citire");
            exit(3);
        }
        if(cod_r == 0)  // EOF (i.e., am ajuns la sfârșitul fișierului)
            break;

        vector_ap[ch]++;
    }
    while(1);

    // sub-step 3c: finalizarea sesiunii de lucru cu fisierul de intrare
    if(close(fd) == -1)
    {
        perror("Eroare la inchidere");
        exit(4);
    }

    // step 4: afișarea vectorului de apariții
    for(i = 0; i < ASCII_SET_SIZE; i++)
        if(vector_ap[i] != 0)
            printf("Caracterul %c cu codul ASCII %d apare de %d ori in fisier.\n", i, i, vector_ap[i]);

    return 0;
}
