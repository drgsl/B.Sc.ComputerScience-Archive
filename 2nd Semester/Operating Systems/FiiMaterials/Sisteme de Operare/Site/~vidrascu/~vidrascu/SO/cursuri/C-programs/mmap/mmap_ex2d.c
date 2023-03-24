#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define handle_error(msg) \
    { perror(msg); exit(EXIT_FAILURE); }

int main(int argc, char *argv[])
{
    char *map_addr;
    int fd;
    struct stat sb;
    off_t offset, pa_offset;
    size_t length, adjusted_length;
    ssize_t codw;

    /* Determinăm dimensiunea paginilor corespunzătoare arhitecturii hardware a calculatorului dvs. */
    long PageSize = sysconf(_SC_PAGE_SIZE);
    if (PageSize == -1)
        handle_error("Error at sysconf");
    fprintf(stderr, "Notification: the page size on your hardware system is: %ld bytes.\n", PageSize);


    /* Validăm argumentele din linia de comandă. */
    if (argc < 3 || argc > 4) {
        fprintf(stderr, "Commandline:  %s file offset [length]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        handle_error("Error at open");

    if (fstat(fd, &sb) == -1)   /* To obtain file size */
        handle_error("Error at fstat");

    offset = atoi(argv[2]);
    fprintf(stderr, "Notification: the specified offset was: %ld\n", offset);

    if (offset >= sb.st_size) {
        fprintf(stderr, "Error: offset is past end of file\n");
        exit(EXIT_FAILURE);
    }

    pa_offset = offset & ~(PageSize - 1);   /* offset for mmap() must be page aligned */
    fprintf(stderr, "Notification: the page-aligned ajusted offset is: %ld\n", pa_offset);
    /* Aici, practic am calculat câtul întreg al împărțirii offset-ului la dimensiunea paginii, folosind operatori pe biți. */

    if (argc == 4) {
        length = atoi(argv[3]);
        fprintf(stderr, "Notification: the specified length was: %ld\n", length);

        if (offset + length > sb.st_size)
            length = sb.st_size - offset;  /* Can't display bytes past end of file */
    }
    else {    /* No length arg ==> display to end of file */
        length = sb.st_size - offset;
    }
    fprintf(stderr, "Notification: the corrected length (taking EOF into account) is: %ld\n", length);

    /* Aici, practic am ajustat lungimea cerută pentru porțiunea de fișier ce se va mapa în memorie,
       astfel încât porțiunea să se termine la poziția dată de minimul dintre offset+length și EOF. */

    adjusted_length = length + offset - pa_offset; 
    fprintf(stderr, "Notification: the adjusted length (to the page-aligned offset) is: %ld\n", adjusted_length);
    /* Calculăm dimensiunea reală a mapării, căci în realitate se va mapa în memorie porțiunea din fișier ce începe
       NU de la poziția offset specificată ca argument, ci de la poziția pa_offset (pentru că adresa de start trebuie să fie page aligned),
       iar lungimea porțiunii de fișier mapate în memorie va fi adjusted_length. */

    /* Notă: lungimea/dimensiunea reală a mapării va fi cel mai mic multiplu de PageSize, care depășește valoarea adjusted_length,
       iar zona din memorie ce depășește acea valoare, va fi inițializată cu zero-uri, iar la final, modificările operate asupra ei, NU se salvează
       în fișier, căci sunt peste EOF (deci nu se face append de informații la fișier) !!!   */

    /* Apelul de mapare a porțiunii de fișier specificate, în memorie. */
    map_addr = mmap( NULL,                   // Se va crea o mapare începând de la o adresă page-aligned aleasă de kernel (și returnată în map_addr)
                     adjusted_length,        // Lungimea aliniată (i.e. ajustată page-aligned) a mapării (calculată mai sus)
                     PROT_READ | PROT_WRITE, // Tipul de protecție a mapării: paginile mapării vor permite accese în citire și în scriere
                     MAP_PRIVATE,            // Maparea este privată (i.e., nu este partajată cu alte procese)
                     fd,                     // Descriptorul de fișier, din care se citesc octeții corespunzători porțiunii mapate în memorie
                     pa_offset               // Offset-ul (deplasamentul) aliniat (i.e. ajustat page-aligned), de la care începe porțiunea de fișier mapată
               );                            //   în memorie, i.e. porțiunea din fișier din care se citesc cei actual_length octeți, în maparea din memorie
    if (map_addr == MAP_FAILED)
        handle_error("Error at mmap");
    fprintf(stderr, "Notification: A file mapping in memory was created, for the file: %s\n", argv[1]);
    fprintf(stderr, "Notification: \tthe mapping corresponds to the file's content starting at the aligned offset: %ld, and with the length: %ld\n",
                     pa_offset, adjusted_length);

    long mmap_size_in_pages = ( adjusted_length % PageSize ? 1 : 0 ) + ( adjusted_length / PageSize ); // Notă: și aici am fi putut folosi operatori pe biți!
    /* Aici, practic am calculat partea întreagă superioară a raportului dintre valorile adjusted_length și PageSize. */
    fprintf(stderr, "Notification: \tthe length/size of the mapping in memory is: %ld page(s).\n", mmap_size_in_pages); 

    /* După crearea mapării, descriptorul de fișier poate fi închis imediat, fără a se invalida maparea ! */
    if (-1 == close(fd) )
        handle_error("Error at close");

    /* Scriem pe ecran (stdout) conținutul mapării. Mai precis, afișăm doar zona mapată din fișier (fără începutul ei), nu întreaga mapare ! */
    printf("\nThe initial content of the mapping (read from the file), started from the original, non-aligned, offset, is the following:\n");
    codw = write(STDOUT_FILENO, map_addr + offset - pa_offset, length);
    if (codw == -1)
        handle_error("Error at 1st write on screen");
    if (codw != length) {
        fprintf(stderr, "Error at 1st write on screen: partial write completed.\n");
        exit(EXIT_FAILURE);
    }

    /* Modificăm parțial conținutul mapării, mai precis doar primii 9 octeți de la începutul ei. */
    //   Notă: față de exemplul mmap_ex2a.c, acum scrierea nu va mai cauza eroarea la execuție 'Segmentaion fault', deoarece am modificat în mod
    //   adecvat, în apelul mmap() de mai sus, parametrul ce descrie permisiunile de acces. */
    int i;
    for (i = 0; i < 9; i++) {  *(map_addr + i) = 'A'+i ; }
    /* Notă: mai concis am fi putut scrie astfel:
       strncpy(map_addr,"ABCDEFGHI_!",9);  // Copie doar primele 9 caractere (deci fără caracterul null-terminated string), la începutul mapării.
       ..., dar apelul strncpy generează un warning la compilarea cu opțiunea -Wall și, în plus,
       am preferat să vă arăt cum modificăm efectiv adrese de mmemorie individuale din cadrul mapării. */

    /* Scriem pe ecran (stdout) conținutul mapării. Mai precis, afișăm doar zona mapată din fișier (fără începutul ei), nu întreaga mapare ! */
    printf("\nThe modified content of the mapping, started from the original, non-aligned, offset, is the following:\n");
    codw = write(STDOUT_FILENO, map_addr + offset - pa_offset, length);
    if (codw == -1)
        handle_error("Error at 2nd write on screen");
    if (codw != length) {
        fprintf(stderr, "Error at 2nd write on screen: partial write completed.\n");
        exit(EXIT_FAILURE);
    }

    /* Ne asigurăm că modificările, operate în memorie asupra mapării, sunt salvate pe disc înainte de "ștergerea" mapării. */
    if (-1 == msync(map_addr, adjusted_length, MS_SYNC) )
        handle_error("Error at msync");
    // Conform documentației, trebuie folosit apelul msync() pentru a fi siguri că administratorul memoriei din cadrul SO-ului a apucat să scrie pe disc
    // conținutul modificat al paginilor dirty din memorie, corespunzătoare acelei mapări, ÎNAINTE de a "șterge/distruge" acea mapare prin apelul munmap() !

    /* Notă: totuși, veți constata că nici astfel, cu apelul msync(), nu vom observa la final modificările pe disc, în fișierul respectiv !!!
       Motivația: deoarece maparea am făcut-o de tipul MAP_PRIVATE, ceea ce, conform documentației, înseamnă că paginile din memorie ale mapării au setat
       atributul COW (Copy-on-Write), ceea ce înseamnă că, scrierile în memorie de mai sus s-au făcut NU pe "originalul din memorie" al fișierului,
       ci într-o pagină nouă, clonată, privată procesului. Apelul msync() a "salvat" pe disc "originalul din memorie" (și nu clona privată), iar acesta
       râmăsese însă nemodificat față de conținutul de pe disc, deci practic apelul msync() nu a avut ce să salveze înapoi pe disc. */

    // "Ștergem/distrugem" maparea creată anterior.
    if (-1 == munmap(map_addr, adjusted_length) )
        handle_error("Error at munmap");

    printf("\nTODO: verificati continutul fisierului la final (i.e. dupa 'distrugerea' maparii), cu ajutorul comenzii urmatoare:\ncat %s \n\n", argv[1] );
    exit(EXIT_SUCCESS);
}

