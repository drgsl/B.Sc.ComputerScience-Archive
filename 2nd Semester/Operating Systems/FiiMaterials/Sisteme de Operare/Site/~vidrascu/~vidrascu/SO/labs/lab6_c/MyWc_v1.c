#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main( int argc, char* argv[])
{
    int no_bytes, no_words, no_newlines; // nr. de octeți, nr. de cuvinte, nr. de linii de text, lungimea maximă a unei linii de text
    int fc,fw,fn;                        // flaguri pentru opțiunile prezente în linia de comandă, respectiv -c ,-w, -l, -L

    int last;      /* starea automatului (i.e., ce este ultimul caracter citit / ultima "porțiune" citită până la poziția curentă):
                      0: la început de fișier , 1: într-un cuvânt , 2: într-o zonă de spații albe  */

    int i,ch;
    char *nume_fisier = NULL;
    FILE *fd;

    no_bytes = no_words = no_newlines = 0;
    last = 0;
    fc = fw = fn = 0;

    // Parsarea liniei de comandă pentru a găsi numele fișierului și opțiunile introduse de utilizator.
    for(i = 1; i < argc; i++)
    {
        if(0 == strcmp(argv[i],"-c")) fc = 1;
        else if(0 == strcmp(argv[i],"-w")) fw = 1;
            else if(0 == strcmp(argv[i],"-l")) fn = 1;
                else if(! nume_fisier) nume_fisier = argv[i];
                    else { printf("Programul accepta (deocamdata) un singur nume de fisier, nu mai multe!\n");  exit(1); }
    }
    if( (argc == 1) || (nume_fisier == NULL) )
    {
        fprintf(stderr,"Ati uitat sa specificati numele fisierului de prelucrat!\n");
        exit(2);
    }

    if (0 == fc+fw+fn)   // Dacă nu-i specificată nici o opțiune în linia de comandă, le considerăm pe toate cele trei, similar comportamentului comenzii wc.
        fc = fw = fn = 1;

    // Inițializăm sesiunea de lucru cu fișierul de prelucrat.
    if(NULL == (fd = fopen(nume_fisier,"r")))
    {
        perror("Eroare la deschiderea fisierului de prelucrat!\n");
        exit(3);
    }

    // Parcurgem fișierul și calculăm toate cele trei numere.
    while(1)
    {
        ch = fgetc(fd);
        if( feof(fd) ) break;

        no_bytes++;

        if( isspace(ch) )
        {
            if(last == 1)  { no_words++; }
            last = 2;
        }
        else
            last = 1;

        if (ch == '\n') { no_newlines++; }
    }

    // La sfârșit de fișier, dacă avem starea 1, trebuie incrementat numărul de cuvinte.
    if (last == 1) { no_words++; }

    // Tot la sfârșit de fișier, dacă ultimul caracter nu fusese '\n', ar trebui incrementat numărul de linii, dar...
    // if (ch != '\n') { no_newlines++; }
    // ..., dar NU facem aceasta, căci nici comanda wc nu o face (de fapt, wc numără newline-urile din fișier, nu liniile de text !!)


    // Urmează afișarea doar a statisticilor corespunzătoare opțiunilor specificate
    printf("Fisierul %s contine: ", nume_fisier);
    if( fc )  printf("%d caractere (octeti) , ", no_bytes);
    if( fw )  printf("%d cuvinte , ", no_words);
    if( fn )  printf("%d linii de text (de fapt, newline-uri).", no_newlines);
    printf("\n");

    return 0;
}
