/*
  Program: demo_data-race1_prod.c

  Funcționalitate: un producător, ce va "produce" 20 de texte, fiecare de lungime 10, la intervale de tip aleatoare, pe care le va "comunica"
                   partenerului său, consumatorul, prin scriere într-un fișier mapat în memorie.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define handle_error(msg) \
    { perror(msg); exit(EXIT_FAILURE); }

#define nr_texte  20
#define dim_texte 10

int main(int argc, char *argv[])
{
    int i,fd;
    size_t length;
    char *map_addr;
    char texte_de_scris[nr_texte][dim_texte];

    srandom( getpid() ); // Inițializarea generatorului de numere aleatoare.

    for(i = 0 ; i < nr_texte ; i++)
    {
        snprintf(texte_de_scris[i],dim_texte,"Textul %2d",i);  // Inițializarea textelor.

        // fprintf(stderr,"[Producer] Debug info: %d : %s\n",i,texte_de_scris[i]);
    }

    // step 1: crearea fișierului specificat, respectiv trunchierea lui în caz că exista deja.
    if(-1 == (fd = open("data.txt", O_RDWR | O_CREAT | O_TRUNC, 0600)) )
        handle_error("[Producer] Error at open");

    // step 2: maparea fișierului în memorie.

    length = nr_texte * dim_texte;

    if(-1 == ftruncate(fd, length) ) // "trunchiem" noul fișier la lungimea necesară pentru a stoca textele.
        handle_error("[Producer] Error at truncate");

    /* Apelul de mapare a întregului fișier specificat, în memorie. */
    map_addr = mmap( NULL,                   // Se va crea o mapare începând de la o adresă page-aligned aleasă de kernel (și returnată în map_addr)
                     length,                 // Lungimea mapării (de fapt, se alocă multiplu de pagini, dar restul din ultima pagină se umple cu zero-uri)
                     PROT_READ | PROT_WRITE, // Tipul de protecție a mapării: paginile mapării vor permite accese în citire și în scriere
                     MAP_SHARED,             // Maparea este partajată (altfel, ca mapare privată, nu se salvează nimic în fișierul de pe disc, la final)
                     fd,                     // Descriptorul de fișier, asociat fișierului ce se mapează în memorie
                     0                       // Offset-ul, de la care începe porțiunea de fișier mapată în memorie, este 0, i.e. BOF
                   );                            
    if (map_addr == MAP_FAILED)
        handle_error("[Producer] Error at mmap");
    fprintf(stderr, "[Producer] Notification: A shared file mapping in memory was created, for the file: data.txt\n");
    fprintf(stderr, "[Producer] Notification:   the mapping corresponds to the file's content starting at offset: 0, and with the length: %ld\n", length);

    /* După crearea mapării, descriptorul de fișier poate fi închis imediat, fără a se invalida maparea ! */
    if (-1 == close(fd) )
        handle_error("[Producer] Error at close");


    // step 3: scriem textele în fișierul mapat în memorie.
    for(i = 0; i < nr_texte; i++)
    {
        strcpy(map_addr + i*dim_texte, texte_de_scris[i]);  // scriem în memorie al i-lea text
        fprintf(stderr, "[Producer] Notification: I wrote the %dth text, \"%s\", in the mapping.\n", i, texte_de_scris[i]);

        sleep( random() % 3 ); // Facem o pauză aleatoare, de maxim 2 secunde, înainte de a continua cu următoarea iterație.
    }


    // step 4: salvăm modificările efectuate în memorie, pe disc. Mai exact:

    /* Ne asigurăm că modificările, operate în memorie asupra mapării, sunt salvate pe disc înainte de "ștergerea" mapării. */
    if (-1 == msync(map_addr, length, MS_SYNC) )
        handle_error("[Producer] Error at msync");
    // Conform documentației, trebuie folosit apelul msync() pentru a fi siguri că administratorul memoriei din cadrul SO-ului a apucat să scrie pe disc
    // conținutul modificat al paginilor dirty din memorie, corespunzătoare acelei mapări, ÎNAINTE de a "șterge/distruge" acea mapare prin apelul munmap() !


    // step 5: "ștergem/distrugem" maparea creată anterior. // Oricum, aceasta se făcea și implicit, la finalul programului.
    if (-1 == munmap(map_addr, length) )
        handle_error("[Producer] Error at munmap");

    fprintf(stderr, "[Producer] Notification: I finished my job!\n");
    exit(EXIT_SUCCESS);
}
