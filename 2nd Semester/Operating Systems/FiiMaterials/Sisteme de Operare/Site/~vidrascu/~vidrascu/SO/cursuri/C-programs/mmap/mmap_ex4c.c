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

int main(int argc, char *argv[])
{
    int i,fd;
    size_t length;
    char *map_addr;
    char* text_de_scris = "Acest mesaj se va scrie in fisierul mapat in memorie.";

    // step 1: crearea fișierului specificat, respectiv trunchierea lui în caz că exista deja.
    if(-1 == (fd = open("data.txt", O_RDWR | O_CREAT | O_TRUNC, 0600)) )
        handle_error("Eroare la crearea fisierului de date");

    // step 2: maparea fișierului în memorie.

    length = strlen(text_de_scris); // the length of the string pointed to by text_de_scris, excluding the terminating null byte ('\0').

    if(-1 == ftruncate(fd, length) ) // "trunchiem" noul fișier la lungimea necesară pentru a stoca textul.
        handle_error("Eroare la trunchierea fisierului de date");

    /* Apelul de mapare a întregului fișier specificat, în memorie. */
    map_addr = mmap( NULL,                   // Se va crea o mapare începând de la o adresă page-aligned aleasă de kernel (și returnată în map_addr)
                     length,                 // Lungimea mapării (de fapt, se alocă multiplu de pagini, dar restul din ultima pagină se umple cu zero-uri)
                     PROT_READ | PROT_WRITE, // Tipul de protecție a mapării: paginile mapării vor permite accese în citire și în scriere
                     MAP_SHARED,             // Maparea este partajată (altfel, ca mapare privată, nu se salvează nimic în fișierul de pe disc, la final)
                     fd,                     // Descriptorul de fișier, asociat fișierului ce se mapează în memorie
                     0                       // Offset-ul, de la care începe porțiunea de fișier mapată în memorie, este 0, i.e. BOF
                   );                            
    if (map_addr == MAP_FAILED)
        handle_error("Error at mmap");
    fprintf(stderr, "Notification: A file mapping in memory was created, for the file: data.txt\n");
    fprintf(stderr, "Notification: \tthe mapping corresponds to the file's content starting at offset: 0, and with the length: %ld\n", length);

    /* După crearea mapării, descriptorul de fișier poate fi închis imediat, fără a se invalida maparea ! */
    if (-1 == close(fd) )
        handle_error("Error at close");


    // step 3: scriem textul în fișierul mapat în memorie.
    for(i = 0; i < length; i++)
    {
        *(map_addr + i) = text_de_scris[i];  // scriem în memorie al i-lea caracter al acelui text
    }
    //sau, echivalent, puteam scrie: strcpy(map_addr,text_de_scris);


    // step 4: salvăm modificările efectuate în memorie, pe disc. Mai exact:

    /* Ne asigurăm că modificările, operate în memorie asupra mapării, sunt salvate pe disc înainte de "ștergerea" mapării. */
    if (-1 == msync(map_addr, length, MS_SYNC) )
        handle_error("Error at msync");
    // Conform documentației, trebuie folosit apelul msync() pentru a fi siguri că administratorul memoriei din cadrul SO-ului a apucat să scrie pe disc
    // conținutul modificat al paginilor dirty din memorie, corespunzătoare acelei mapări, ÎNAINTE de a "șterge/distruge" acea mapare prin apelul munmap() !


    // step 5: "ștergem/distrugem" maparea creată anterior. // Oricum, aceasta se făcea și implicit, la finalul programului.
    if (-1 == munmap(map_addr, length) )
        handle_error("Error at munmap");

    exit(EXIT_SUCCESS);
}
