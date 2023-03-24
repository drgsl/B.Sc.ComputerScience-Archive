/*
* Filename: bin2txt_read-mapped-file.c
*
* Un program demonstrativ, care afișează pe ecran reprezentarea textuală a numerelor citite dintr-un fișier mapat în memorie,
* numere ce sunt stocate în format binar, în fișierul de date specificat.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>  // necesar pentru PATH_MAX

#define handle_error(msg) \
    { perror(msg); exit(EXIT_FAILURE); }

int main(int argc, char *argv[])
{
    int nr,fd,i;
    struct stat sb;
    size_t file_length;
    char *map_addr;
    int *p_nr = NULL;
    char nume_fisier[PATH_MAX];

    // step 1: verificare apelare cu (minim) un argument.

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
        handle_error("Eroare la deschiderea fisierului de date");

    // step 3: maparea fișierului în memorie.

    if (fstat(fd, &sb) == -1)   // pentru a obține dimensiunea fișierului, în octeți.
        handle_error("Error at fstat");
    file_length = sb.st_size;

    /* Apelul de mapare a întregului fișier specificat, în memorie. */
    map_addr = mmap( NULL,          // Se va crea o mapare începând de la o adresă page-aligned aleasă de kernel (și returnată în map_addr)
                     file_length,   // Lungimea mapării (de fapt, se alocă multiplu de pagini, dar restul din ultima pagină se umple cu zero-uri)
                     PROT_READ,     // Tipul de protecție a mapării: paginile mapării vor permite accese doar în citire
                     MAP_PRIVATE,   // Maparea este privată (doar pentru citirea fișierului, este suficient să fie privată)
                     fd,            // Descriptorul de fișier, din care se citesc octeții corespunzători porțiunii mapate în memorie
                     0              // Offset-ul, de la care începe porțiunea de fișier mapată în memorie, este 0, i.e. BOF
                   );                            
    if (map_addr == MAP_FAILED)
        handle_error("Error at mmap");
    fprintf(stderr, "Notification: A file mapping in memory was created, for the file: %s\n", nume_fisier);
    fprintf(stderr, "Notification: \tthe mapping corresponds to the file's content starting at offset: 0, and with the length: %ld\n", file_length);

    /* După crearea mapării, descriptorul de fișier poate fi închis imediat, fără a se invalida maparea ! */
    if (-1 == close(fd) )
        handle_error("Error at close");


    // step 4: bucla de procesare -- se citesc numere întregi, în format binar, din fișierul mapat în memorie, și se afișează pe ecran (stdout), în format textual.
    printf("Secventa de numere citite din fisierul de date mapat in memorie este urmatoarea:\n");
   
    for(i = 0, p_nr = (int *) map_addr ; i < file_length/sizeof(int) ; i++, p_nr++ )
    {
        nr = *p_nr;  // "Citim" din memorie cel de-al i-lea număr, ...

        printf("%d , ", nr);     // ... și îl afișăm pe ecran.
    }
    printf("EndOfSequence!\n\n");


    // step 5: "ștergem/distrugem" maparea creată anterior. // Oricum, aceasta se făcea și implicit, la finalul programului.
    if (-1 == munmap(map_addr, file_length) )
        handle_error("Error at munmap");

    exit(EXIT_SUCCESS);
}

