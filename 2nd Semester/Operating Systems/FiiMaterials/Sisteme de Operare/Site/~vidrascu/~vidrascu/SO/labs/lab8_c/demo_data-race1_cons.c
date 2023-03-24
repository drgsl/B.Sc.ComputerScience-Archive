/*
  Program: demo_data-race1_cons.c

  Funcționalitate: un consumator, ce va "consuma" 20 de texte, fiecare de lungime 10, la intervale de tip aleatoare, pe care le va "primi"
                   de la partenerul său, producătorul, prin citirea lor dintr-un fișier mapat în memorie, în care le-a scris producătorul.
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
    char texte_de_citit[nr_texte][dim_texte];

    srandom( getpid() ); // Inițializarea generatorului de numere aleatoare.

    // step 1: deschiderea fișierului specificat.
    if(-1 == (fd = open("data.txt", O_RDONLY)) )
        handle_error("[Consumer] Error at open");

    // step 2: maparea fișierului în memorie.

    length = nr_texte * dim_texte;

    /* Apelul de mapare a întregului fișier specificat, în memorie. */
    map_addr = mmap( NULL,         // Se va crea o mapare începând de la o adresă page-aligned aleasă de kernel (și returnată în map_addr)
                     length,       // Lungimea mapării (de fapt, se alocă multiplu de pagini, dar restul din ultima pagină se umple cu zero-uri)
                     PROT_READ,    // Tipul de protecție a mapării: paginile mapării vor permite doar accese în citire
                     MAP_SHARED,   // Maparea este partajată (altfel, ca mapare privată, nu se salvează nimic în fișierul de pe disc, la final)
                     fd,           // Descriptorul de fișier, asociat fișierului ce se mapează în memorie
                     0             // Offset-ul, de la care începe porțiunea de fișier mapată în memorie, este 0, i.e. BOF
                   );                            
    if (map_addr == MAP_FAILED)
        handle_error("[Consumer] Error at mmap");
    fprintf(stderr, "[Consumer] Notification: A shared file mapping in memory was created, for the file: data.txt\n");
    fprintf(stderr, "[Consumer] Notification:   the mapping corresponds to the file's content starting at offset: 0, and with the length: %ld\n", length);

    /* După crearea mapării, descriptorul de fișier poate fi închis imediat, fără a se invalida maparea ! */
    if (-1 == close(fd) )
        handle_error("[Consumer] Error at close");


    // step 3: citim textele din fișierul mapat în memorie.
    for(i = 0; i < nr_texte; i++)
    {
        strcpy(texte_de_citit[i], map_addr + i*dim_texte);  // citim din memorie al i-lea text
        fprintf(stderr, "[Consumer] Notification: I read the %dth text, \"%s\", from the mapping.\n", i, texte_de_citit[i]);

        sleep( random() % 3 ); // Facem o pauză aleatoare, de maxim 2 secunde, înainte de a continua cu următoarea iterație.
    }


    // step 4: "ștergem/distrugem" maparea creată anterior. // Oricum, aceasta se făcea și implicit, la finalul programului.
    if (-1 == munmap(map_addr, length) )
        handle_error("[Consumer] Error at munmap");

    fprintf(stderr, "[Consumer] Notification: I finished my job!\n");
    exit(EXIT_SUCCESS);
}
