#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main( int argc, char* argv[])
{
    unsigned long no_bytes, no_words;      // nr. de octeți, nr. de cuvinte
    unsigned int no_newlines, max_length;  // nr. de linii de text, lungimea maximă a unei linii de text
    unsigned char fc,fw,fn,fL;             // flaguri pentru opțiunile prezente în linia de comandă, respectiv -c ,-w, -l, -L

    unsigned char last;        /* starea automatului (i.e., ce este ultimul caracter citit / ultima "porțiune" citită până la poziția curentă):
                                  0: la început de fișier , 1: într-un cuvânt , 2: într-o zonă de spații albe  */

    unsigned int iterator, no_chars_per_line = 0;
    unsigned char ch;
    char *nume_fisier = NULL;
    FILE *fd;

    no_bytes = no_words = no_lines = max_length = 0;
    last = 0;
    fc = fw = fn = fL = 0;

    /* Parsarea liniei de comandă pentru a găsi numele fișierului și opțiunile. */
    for (iterator = 1; iterator < argc; iterator++)
    {
        if(0 == strcmp(argv[iterator],"-c")) fc = 1;
        else if(0 == strcmp(argv[iterator],"-w")) fw = 1;
            else if(0 == strcmp(argv[iterator],"-l")) fn = 1;
                else if(0 == strcmp(argv[iterator],"-L")) fL = 1;
                    else if(! nume_fisier) nume_fisier = argv[iterator];
                        else { printf("Programul accepta (deocamdata) un singur nume de fisier, nu mai multe!\n");  exit(1); }
    }
    if( (argc == 1) || (nume_fisier == NULL) )
    {
        fprintf(stderr,"Ati uitat sa specificati numele fisierului de prelucrat!\n");  exit(2);
    }

    if (0 == fc+fw+fn+fL)   // Dacă nu-i specificată nici o opțiune în linia de comandă, le considerăm pe cele trei, similar comportamentului comenzii wc.
        fc = fw = fn = 1;

    /* Inițializăm sesiunea de lucru cu fișierul de prelucrat. */
    if(NULL == (fd = fopen(nume_fisier,"r")))
    {
        perror("Eroare la deschiderea fisierului de prelucrat!\n");  exit(3);
    }

    /* Parcurgem fișierul și calculăm doar ceea ce s-a cerut. */
    while(1)
    {
        ch = fgetc(fd);
        if( feof(fd) ) break;

        /* Numai dacă este prezentă opțiunea -c , facem calculele pentru a număra octeții. */
        // if( fc ) { no_bytes++; }
        no_bytes++;    // Notă: este mai eficient așa, deoarece un test if este mai costisitor decât o incrementare!

        /* Numai dacă este prezentă opțiunea -w , facem calculele pentru a număra cuvintele. */
        if( fw )
        {
            if( isspace(ch) )
            {
                if(last == 1)  { no_words++; }
                last = 2;
            }
            else
                last = 1;
        }

        /* Numai dacă este prezentă opțiunea -l , facem calculele pentru a număra liniile de text (de fapt, newline-urile). */
        if( fn )
        {
            if(ch == '\n') { no_newlines++; }
        }

        /* Numai dacă este prezentă opțiunea -L , facem calculele pentru a afla lungimea maximă a liniilor de text. */
        if( fL )
        {
            if(ch != '\n')
            {
                if(ch == '\t')
                    no_chars_per_line += 8;  // Notă: comanda wc numără 8 poziții pentru fiecare caracter TAB !
                else
                    no_chars_per_line++;
            }
            else
            {
                if(max_length < no_chars_per_line) { max_length = no_chars_per_line; }
                no_chars_per_line = 0;
            }
        }
    }

    /* La sfârșit de fișier avem de făcut trei lucruri: */

    /* a) Dacă starea este 1, trebuie incrementat numărul de cuvinte. */
    if( fw )
    {
        if(last == 1) { no_words++; }
    }

    /* b) Dacă ultimul caracter nu fusese '\n', ar trebui incrementat numărul de linii, dar... */
    // if( fn )
    // {
    //    if(ch != '\n') { no_newlines++; }
    // }
    /* ..., dar NU mai facem această acțiune b), căci nici comanda wc nu o face (practic, wc numără nu liniile de text, ci caracterele newline!) */

    /* c) Dacă ultimul caracter nu fusese '\n', trebuie văzut dacă nu cumva ultima linie este de lungime maximă. */
    if( fL )
    {
        if(ch != '\n')
        {
            if(max_length < no_chars_per_line) { max_length = no_chars_per_line; }
        }
    }

    /* Urmează afișarea statisticilor corespunzătoare opțiunilor specificate de utilizator. */
    printf("Fisierul %s contine: ", nume_fisier);
    if( fc )  printf("%lu caractere (octeti) , ", no_bytes);
    if( fw )  printf("%lu cuvinte , ", no_words);
    if( fn )  printf("%u linii de text (de fapt, newline-uri) , ", no_newlines);
    if( fL )  printf("%u lungimea maxima a liniilor de text.", max_length);
    printf("\n");

    return 0;
}
