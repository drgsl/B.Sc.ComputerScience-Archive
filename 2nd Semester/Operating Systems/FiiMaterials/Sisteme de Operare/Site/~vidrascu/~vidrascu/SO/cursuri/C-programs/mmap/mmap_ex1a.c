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
    off_t offset;
    size_t length;
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

    if(offset % PageSize != 0)
    {
        fprintf(stderr, "Notification: the specified offset is not page-aligned! As such, the following mmap() call will fail!\n");
    }

    /* Apelul de mapare a porțiunii de fișier specificate, în memorie. */
    map_addr = mmap( NULL,           // Se va crea o mapare începând de la o adresă page-aligned aleasă de kernel (și returnată în map_addr)
                     length,         // Lungimea ne-aliniată (i.e. ne-ajustată page-aligned) a mapării (doar corectată, ca mai sus)
                     PROT_READ,      // Tipul de protecție a mapării: paginile mapării vor permite doar accese în citire
                     MAP_PRIVATE,    // Maparea este privată (i.e., nu este partajată cu alte procese)
                     fd,             // Descriptorul de fișier, din care se citesc octeții corespunzători porțiunii mapate în memorie
                     offset          // Offset-ul (deplasamentul) ne-aliniat (i.e. ne-ajustat page-aligned), de la care începe porțiunea de fișier mapată
               );                    //   în memorie, i.e. porțiunea din fișier din care se citesc cei actual_length octeți, în maparea din memorie
    if (map_addr == MAP_FAILED)
        handle_error("Error at mmap");
    fprintf(stderr, "Notification: A file mapping in memory was created, for the file: %s\n", argv[1]);
    fprintf(stderr, "Notification: \tthe mapping corresponds to the file's content starting at the offset: %ld, and with the length: %ld\n",
                     offset, length);

    long mmap_size_in_pages = ( length % PageSize ? 1 : 0 ) + ( length / PageSize );
    /* Aici, practic am calculat partea întreagă superioară a raportului dintre valorile length și PageSize. */
    fprintf(stderr, "Notification: \tthe length/size of the mapping in memory is: %ld page(s).\n", mmap_size_in_pages); 

    /* După crearea mapării, descriptorul de fișier poate fi închis imediat, fără a se invalida maparea ! */
    if (-1 == close(fd) )
        handle_error("Error at close");

    /* Scriem pe ecran (stdout) conținutul mapării. Mai precis, afișăm doar zona mapată din fișier (fără începutul ei), nu întreaga mapare ! */
    printf("\nThe initial content of the mapping (read from the file), started from the specified offset, is the following:\n");
    codw = write(STDOUT_FILENO, map_addr, length);
    if (codw == -1)
        handle_error("Error at write on screen");
    if (codw != length) {
        fprintf(stderr, "Error at write on screen: partial write completed.\n");
        exit(EXIT_FAILURE);
    }

    // "Ștergem/distrugem" maparea creată anterior.
    if (-1 == munmap(map_addr, length) )
        handle_error("Error at munmap");

    printf("\nTODO: verificati continutul fisierului la final (i.e. dupa 'distrugerea' maparii), cu ajutorul comenzii urmatoare:\ncat %s \n\n", argv[1] );
    exit(EXIT_SUCCESS);
}

