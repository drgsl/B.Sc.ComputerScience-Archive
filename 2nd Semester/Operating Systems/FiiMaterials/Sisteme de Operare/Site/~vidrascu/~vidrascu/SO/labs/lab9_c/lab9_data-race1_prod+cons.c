/*
  Program: lab9_data-race1_prod+cons.c

  Funcționalitate: se ilustrează cooperarea dintre două procese, tată și fiu, folosind memorie comună.

  Tatăl implementează un producător, ce va "produce" 20 de texte, fiecare de lungime 10, la intervale de tip aleatoare, pe care le va "comunica"
  partenerului său, consumatorul, prin scriere într-o mapare anonimă în memorie.

  Iar fiul implementează un consumator, ce va "consuma" 20 de texte, fiecare de lungime 10, la intervale de tip aleatoare, pe care le va "primi"
  de la partenerul său, producătorul, prin citirea lor dintr-o mapare anonimă în memorie, în care le-a scris producătorul.
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


void producer_work(); // Funcție definită mai jos, ce conține implementarea funcționalității de producător a tatălui

void consumer_work(); // Funcție definită mai jos, ce conține implementarea funcționalității de consumator a fiului


char *map_addr;

int main()
{
    pid_t pid_fiu;
    size_t length;

    length = nr_texte * dim_texte;   // Sau, pentru acele valori, putem și astfel:  length = 100;

    /* Determinăm dimensiunea paginilor corespunzătoare arhitecturii hardware a calculatorului dvs. */
    long PageSize = sysconf(_SC_PAGE_SIZE);
    if (PageSize == -1)
        handle_error("Error at sysconf");
    fprintf(stderr, "Notification: The page size on your hardware system is: %ld bytes.\n", PageSize);

    /* Calculăm partea întreagă superioară a raportului dintre valorile length și PageSize. */
    long mmap_size_in_pages = ( length % PageSize ? 1 : 0 ) + ( length / PageSize );


    /* Step 1: Crearea unei mapări anonime, partajate și cu drepturi de citire+scriere. Neapărat înaintea apelului de clonare a procesului... */

    map_addr = mmap( NULL,                       // Se va crea o mapare începând de la o adresă page-aligned aleasă de kernel (și returnată în map_addr)
                     length,                     // Lungimea dorită, preferabil multiplu de dimensiunea paginii (oricum, se vor aloca un număr de pagini "complete")
                     PROT_READ | PROT_WRITE,     // Tipul de protecție a mapării: paginile mapării vor permite accese în citire și scriere
                     MAP_SHARED | MAP_ANONYMOUS, // Maparea este anonimă și partajată, pentru a avea memorie comună între procesele tată și fiu
                     -1,                         // La descriptorul de fișier se pune -1, conform documentației
                     0                           // Offset-ul (deplasamentul) nu este luat în seamă, conform documentației
                   );
    if (map_addr == MAP_FAILED)
        handle_error("Error at mmap");
    fprintf(stderr, "Notification: An anonymous shared mapping in memory was created, with read/write permmission, and with the length: %ld.\n", length);
    fprintf(stderr, "Notification:   Actually, the length/size of the mapping in memory is: %ld page(s).\n", mmap_size_in_pages); 


    /* Step 2: Crearea unui proces fiu. */
    if(-1 == (pid_fiu=fork()) )
    {
        perror("Eroare la fork");  return 1;
    }


    /* Step 3: Ramificarea execuției în cele două procese, tată și fiu. */
    if(pid_fiu == 0)
    {   /* Zona de cod executată doar de către fiu. */

        fprintf(stderr, "[Consumer] Notification: sunt procesul fiu, cu PID-ul: %d.\n", getpid());
        consumer_work();
    }
    else
    {   /* Zona de cod executată doar de către părinte. */

        fprintf(stderr, "[Producer] Notification: sunt procesul tata, cu PID-ul: %d.\n", getpid());
        producer_work();
    }

    /* Zona de cod comună, executată de către ambele procese */

    // La final, "ștergem/distrugem" maparea anonimă creată anterior. Oricum, aceasta se făcea și implicit, la finalul programului.
    if (-1 == munmap(map_addr, length) )
        handle_error("Error at munmap");

    fprintf(stderr, "Notification: sfarsitul executiei procesului %s.\n\n", pid_fiu == 0 ? "fiu" : "parinte" );
    return EXIT_SUCCESS;
}

void producer_work()
{
    int i;
    char texte_de_scris[nr_texte][dim_texte];

    srandom( getpid() ); // Inițializarea generatorului de numere aleatoare.

    // Inițializarea textelor.
    for(i = 0 ; i < nr_texte ; i++)
    {
        snprintf(texte_de_scris[i],dim_texte,"Textul %2d",i); // Atenție, e important: pe poziția a 10-a din text se va stoca zero-ul ce indică null-terminated string!
    }

    // Scriem textele în maparea anonimă din memorie.
    for(i = 0; i < nr_texte; i++)
    {
        strcpy(map_addr + i*dim_texte, texte_de_scris[i]);  // scriem în memorie al i-lea text
        fprintf(stderr, "[Producer] Notification: I wrote the %dth text, \"%s\", in the mapping.\n", i, texte_de_scris[i]);

        sleep( random() % 3 ); // Facem o pauză aleatoare, de maxim 2 secunde, înainte de a continua cu următoarea iterație.
    }

    fprintf(stderr, "[Producer] Notification: I finished my job!\n");
    return; //exit(EXIT_SUCCESS);
}

void consumer_work()
{
    int i;
    char texte_de_citit[nr_texte][dim_texte];

    srandom( getpid() ); // Inițializarea generatorului de numere aleatoare.

    // Citim textele din maparea anonimă din memorie.
    for(i = 0; i < nr_texte; i++)
    {
        strcpy(texte_de_citit[i], map_addr + i*dim_texte);  // citim din memorie al i-lea text
        fprintf(stderr, "[Consumer] Notification: I read the %dth text, \"%s\", from the mapping.\n", i, texte_de_citit[i]);

        sleep( random() % 3 ); // Facem o pauză aleatoare, de maxim 2 secunde, înainte de a continua cu următoarea iterație.
    }

    fprintf(stderr, "[Consumer] Notification: I finished my job!\n");
    return; //exit(EXIT_SUCCESS);
}

