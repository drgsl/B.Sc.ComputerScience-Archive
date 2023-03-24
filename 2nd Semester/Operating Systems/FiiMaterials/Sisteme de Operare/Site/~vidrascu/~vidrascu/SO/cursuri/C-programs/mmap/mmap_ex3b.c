#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define handle_error(msg,cod) \
    { perror(msg); exit(cod); }

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
        handle_error("Error at sysconf",1);
    fprintf(stderr, "Notification: the page size on your hardware system is: %ld bytes.\n", PageSize);


    /* Validăm argumentele din linia de comandă. */
    if (argc < 3 || argc > 4) {
        fprintf(stderr, "Commandline:  %s file offset [length]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd = open(argv[1], O_RDWR);
    if (fd == -1)
        handle_error("Error at open",2);

    if (fstat(fd, &sb) == -1)   /* To obtain file size */
        handle_error("Error at fstat",3);

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
            length = sb.st_size - offset;   /* Can't display bytes past end of file */
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
                     MAP_SHARED,             // Maparea este partajată (altfel, ca mapare privată, nu se salvează nimic în fișierul de pe disc, la final)
                     fd,                     // Descriptorul de fișier, din care se citesc octeții corespunzători porțiunii mapate în memorie
                     pa_offset               // Offset-ul (deplasamentul) aliniat (i.e. ajustat page-aligned), de la care începe porțiunea de fișier mapată
               );                            //   în memorie, i.e. porțiunea din fișier din care se citesc cei actual_length octeți, în maparea din memorie
    if (map_addr == MAP_FAILED)
        handle_error("Error at mmap",4);
    fprintf(stderr, "Notification: A file mapping in memory was created, for the file: %s\n", argv[1]);
    fprintf(stderr, "Notification: \tthe mapping corresponds to the file's content starting at the aligned offset: %ld, and with the length: %ld\n",
                     pa_offset, adjusted_length);

    long mmap_size_in_pages = ( adjusted_length % PageSize ? 1 : 0 ) + ( adjusted_length / PageSize ); // Notă: și aici am fi putut folosi operatori pe biți!
    /* Aici, practic am calculat partea întreagă superioară a raportului dintre valorile adjusted_length și PageSize. */
    fprintf(stderr, "Notification: \tthe length/size of the mapping in memory is: %ld page(s).\n", mmap_size_in_pages); 

    /* După crearea mapării, descriptorul de fișier poate fi închis imediat, fără a se invalida maparea ! */
    if (-1 == close(fd) )
        handle_error("Error at close",5);

    /* Scriem pe ecran (stdout) conținutul mapării. Mai precis, afișăm doar zona mapată din fișier (fără începutul ei), nu întreaga mapare ! */
    printf("\nThe initial content of the mapping (read from the file), started from the original, non-aligned, offset, is the following:\n");
    codw = write(STDOUT_FILENO, map_addr + offset - pa_offset, length);
    if (codw == -1)
        handle_error("Error at 1st write on screen",6);
    if (codw != length) {
        fprintf(stderr, "Error at 1st write on screen: partial write completed.\n");
        exit(EXIT_FAILURE);
    }

    /* Modificăm parțial conținutul mapării, mai precis doar primii 9 octeți de la începutul ei. */
    int i;
    for (i = 0; i < 9; i++) {  *(map_addr + i) = 'A'+i ; }
    /* Notă: mai concis am fi putut scrie astfel:
       strncpy(map_addr,"ABCDEFGHI_!",9);  // Copie doar primele 9 caractere (deci fără caracterul null-terminated string), la începutul mapării.
       ..., dar apelul strncpy generează un warning la compilarea cu opțiunea -Wall și, în plus,
       am preferat să vă arăt cum modificăm efectiv adrese de mmemorie individuale din cadrul mapării. */

    /* Scriem pe ecran (stdout) conținutul mapării. Mai precis, afișăm doar zona mapată din fișier (fără începutul ei), nu întreaga mapare ! */
    printf("\nThe modified content of the mapping, started from the page-aligned offset, is the following:\n");
    codw = write(STDOUT_FILENO, map_addr, adjusted_length);
    if (codw == -1)
        handle_error("Error at 2nd write on screen",7);
    if (codw != adjusted_length) {
        fprintf(stderr, "Error at 2nd write on screen: partial write completed.\n");
        exit(EXIT_FAILURE);
    }

    int an_offset_outside_last_page = mmap_size_in_pages * PageSize + 5;

    fprintf(stderr, "\nNotification: now, we will try a second write in memory, past the end of mapped region of file, and outside the last allocated page.\n");

    /* Modificăm parțial conținutul memoriei, mai precis începând de la 5 octeți după finalul ultimei pagini alocate mapării. */
    for (i = 0; i < 3; i++) {  *(map_addr + an_offset_outside_last_page + i) = 'X' + i ; }
    /* Notă: mai concis am fi putut scrie astfel:
       strncpy(map_addr+an_offset_outside_last_page,"XYZ_!",3);  // Copie doar primele 3 caractere (deci fără caracterul null), la acea adresă
       ..., dar apelul strncpy generează un warning la compilarea cu opțiunea -Wall și, în plus,
       am preferat să vă arăt cum modificăm efectiv adrese de mmemorie individuale din cadrul mapării. */

    /* Practic, pe cele 5 poziții, de după ultima pagină alocată mapării, putem avea orice fel de conținut. Posibil zero-uri, dar nu olbigatoriu.
       Notă: dacă aceste 5 poziții sunt zerouri (sau coduri ale altor caractere neprintabile), ele nu vor fi vizibile la afișarea pe ecran, de mai jos!
       Pentru a le "vedea", trebuie redirectat output-ul execuției programului către un fișier, și inspectat acel fișier cu un viewer hexa, e.g. mcview. */


    /* Scriem pe ecran (stdout) conținutul mapării. Mai precis, afișăm nu doar zona mapată din fișier, plus porțiunea modificată în memorie,
       ci și zona de memorie modificată, de după ultima pagină alocată mapării ! */
    printf("\nThe 2nd modified content of the mapping, started from the aligned offset, is the following:\n");
    codw = write(STDOUT_FILENO, map_addr, an_offset_outside_last_page + 3);
    if (codw == -1)
        handle_error("Error at 3rd write on screen",8);
    if (codw != an_offset_outside_last_page + 3) {
        fprintf(stderr, "Error at 3rd write on screen: partial write completed.\n");
        exit(EXIT_FAILURE);
    }


    /* Ne asigurăm că modificările, operate în memorie asupra mapării, sunt salvate pe disc înainte de "ștergerea" mapării. */
    if (-1 == msync(map_addr, an_offset_outside_last_page, MS_SYNC) )
        handle_error("Error at msync",9);
    // Conform documentației, trebuie folosit apelul msync() pentru a fi siguri că administratorul memoriei din cadrul SO-ului a apucat să scrie pe disc
    // conținutul modificat al paginilor dirty din memorie, corespunzătoare acelei mapări, ÎNAINTE de a "șterge/distruge" acea mapare prin apelul munmap() !

    /* Notă: este nevoie de folosit și apelul msync(), pentru a fi siguri că scrierea pe disc se realizează înainte de "ștergerea" mapării.
       Cu alte cuvinte, fără apelul msync(), există un "race" între momentul când administratorul de memorie decide să scrie pe disc paginile de memorie
       și momentul când se execută apelul munmap() de mai jos. Ce înseamnă aceasta:
       Făcând un număr mare de execuții ale programului fără msync(), cu aceleași date de intrare, veți observa că pentru un anumit procent, p%, dintre execuții,
       "race"-ul va fi câștigat de administratorul de memorie (i.e., veți vedea că fișierul este actualizat la final), iar pentru restul de (100-p)% dintre ele,
       veți observa că "race"-ul va fi câștigat de apelul munmap() de mai jos (i.e., veți vedea că fișierul NU este actualizat la final).  */

    // "Ștergem/distrugem" maparea creată anterior.
    if (-1 == munmap(map_addr, adjusted_length) )
        handle_error("Error at munmap",10);

    printf("\n\nTODO: verificati continutul fisierului la final (i.e. dupa 'distrugerea' maparii), cu ajutorul comenzii urmatoare:\ncat %s \n\n", argv[1] );
    exit(EXIT_SUCCESS);
}

