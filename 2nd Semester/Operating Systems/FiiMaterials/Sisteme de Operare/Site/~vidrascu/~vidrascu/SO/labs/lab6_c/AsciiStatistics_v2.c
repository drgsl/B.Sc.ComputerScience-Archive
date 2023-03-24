#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define ASCII_SET_SIZE 256
/* Codificarea ASCII a caracterelor folosește 1 octet, deci în total sunt 2^8=256 caractere posibil de reprezentat prin codificarea ASCII. */

#define BLOCK_SIZE 4096
/* 4096 este exact dimensiunea paginii de memorie, o folosim din motive de eficiență a operațiilor cu discul (vezi secțiunea preambul a paginii de laborator) !! */

unsigned char buffer[BLOCK_SIZE];   // un vector de octeți fără semn!

int fd, bytes_read, i, count[ASCII_SET_SIZE];  // inițializarea cu zero a vectorului de apariții (și a celorlalte variabile globale)

int main(int argc,char** argv)
{
    // verificare apelare cu (minim) un argument    
    if(argc == 1) { fprintf(stderr,"Specificati fisierul de prelucrat ca parametru!\n"); return 1; }

    // inițializarea sesiunii de lucru cu fișierul ce trebuie procesat
    if (-1 == (fd = open(argv[1],O_RDONLY)) ) { perror("Error opening the file"); return 2; }

    // bucla de procesare a fișierului de intrare -- se citește câte 1 sector (i.e., 4096 octeți) din fișier, la fiecare iterație!
    while(1)
    {
        bytes_read = read(fd, buffer, BLOCK_SIZE);

        if(bytes_read == 0)  break; // EOF

        if(bytes_read == -1) { perror("Error reading the file"); return 3; }

        for(i = 0; i < bytes_read; i++)
            count[ buffer[i] ]++;
    }

    // finalizarea sesiunii de lucru cu fișierul de intrare
    if(close(fd) == -1) { perror("Error closing the file"); exit(4); }

    // afișarea vectorului de apariții
    for(i = 0; i < ASCII_SET_SIZE; i++) {
        if(count[i])
            printf("Caracterul %c cu codul ASCII %d apare de %d ori in fisier.\n", i, i, count[i]);
    }

    return 0;
}
