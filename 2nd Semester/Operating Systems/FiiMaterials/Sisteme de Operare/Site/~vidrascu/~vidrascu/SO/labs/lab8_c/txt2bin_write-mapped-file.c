/*
* Filename: txt2bin_write-mapped-file.c
*
* Un program demonstrativ, care citește de la tastatură o secvență de numere întregi, introduse prin reprezentarea lor textuală,
* și le scrie în format binar, în fișierul de date specificat, mapat în memorie.
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
    unsigned int i;
    int n,nr,fd;
    size_t file_length;
    char *map_addr;
    int *p_nr = NULL;
    char nume_fisier[PATH_MAX];

    // step 1: verificare apelare cu (minim) un argument.

    if(argc == 1)
    {
        printf("Introduceti numele fisierului ce se va crea/suprascrie: ");
        scanf("%s", nume_fisier);
    }
    else
    {
        strcpy(nume_fisier, argv[1]);
    }


    // step 2: "pregătirea" fișierului în care vom salva rezultatul procesării efectate de acest program.

    printf("Introduceti lungimea secventei de numere: ");  // pentru a obține dimensiunea viitoare a fișierului, în octeți.
    if( 1 != scanf("%d", &n) )  {  fprintf(stderr, "Error: incorrect format for an integer number!\n"); exit(EXIT_FAILURE);  }
    if( n <= 0 )  {  fprintf(stderr, "Error: you need to input a strictly positive integer number!\n"); exit(EXIT_FAILURE);  }    

    file_length = n * sizeof(int); // aceasta va fi dimensiunea viitoare a fișierului, în octeți.
	
	/* Deschiderea cu drept de read & write a fișierului specificat, plus eventuala sa creare, în caz că nu exista deja. */
    if(-1 == (fd = open(nume_fisier, O_RDWR | O_CREAT, 0600)) )  // fără O_TRUNC, trunchierea o facem mai jos
        handle_error("Eroare la crearea fisierului de date");

    /* Trunchierea fișierului la lungimea exactă necesară pentru salvarea rezultatului procesării efectate de acest program. */
    if(-1 == ftruncate(fd, file_length) ) // "trunchiem" noul fișier la lungimea necesară pentru a stoca cele n numere.
        handle_error("Eroare la trunchierea fisierului de date");


    // step 3: maparea fișierului în memorie.

    /* Apelul de mapare a întregului fișier specificat, în memorie. */
    map_addr = mmap( NULL,                   // Se va crea o mapare începând de la o adresă page-aligned aleasă de kernel (și returnată în map_addr)
                     file_length,            // Lungimea mapării (de fapt, se alocă multiplu de pagini, dar restul din ultima pagină se umple cu zero-uri)
                     PROT_READ | PROT_WRITE, // Tipul de protecție a mapării: paginile mapării vor permite accese în citire și în scriere
                     MAP_SHARED,             // Maparea este partajată (altfel, ca mapare privată, nu se salvează nimic în fișierul de pe disc, la final)
                     fd,                     // Descriptorul de fișier, asociat fișierului ce se mapează în memorie
                     0                       // Offset-ul, de la care începe porțiunea de fișier mapată în memorie, este 0, i.e. BOF
                   );                            
    if (map_addr == MAP_FAILED)
        handle_error("Error at mmap");
    fprintf(stderr, "Notification: A file mapping in memory was created, for the file: %s\n", nume_fisier);
    fprintf(stderr, "Notification: \tthe mapping corresponds to the file's content starting at offset: 0, and with the length: %ld\n", file_length);

    /* După crearea mapării, descriptorul de fișier poate fi închis imediat, fără a se invalida maparea ! */
    if (-1 == close(fd) )
        handle_error("Error at close");


    // step 4: bucla de procesare -- se citesc numere întregi de la tastatură, în format textual, și se scriu, în format binar, în fișierul mapat în memorie.

    for(i = 0, p_nr = (int *) map_addr ; i < n ; i++, p_nr++ )
    {
        printf("Introduceti al %d-lea numar: ",i);   // Citim de la tastatură câte un număr, ...
        if( 1 != scanf("%d", &nr) )  {  fprintf(stderr, "Error: incorrect format for an integer number!\n"); exit(EXIT_FAILURE);  }

        *p_nr = nr;  // ... și "scriem" în memorie acel număr (i.e., cel de-al i-lea număr)
    }

    // step 5: salvăm modificările efectuate în memorie, pe disc. Mai exact:

    /* Ne asigurăm că modificările, operate în memorie asupra mapării, sunt salvate pe disc înainte de "ștergerea" mapării. */
    if (-1 == msync(map_addr, file_length, MS_SYNC) )
        handle_error("Error at msync");
    // Conform documentației, trebuie folosit apelul msync() pentru a fi siguri că administratorul memoriei din cadrul SO-ului a apucat să scrie pe disc
    // conținutul modificat al paginilor dirty din memorie, corespunzătoare acelei mapări, ÎNAINTE de a "șterge/distruge" acea mapare prin apelul munmap() !


    // step 6: "ștergem/distrugem" maparea creată anterior. // Oricum, aceasta se făcea și implicit, la finalul programului.
    if (-1 == munmap(map_addr, file_length) )
        handle_error("Error at munmap");

    exit(EXIT_SUCCESS);
}
