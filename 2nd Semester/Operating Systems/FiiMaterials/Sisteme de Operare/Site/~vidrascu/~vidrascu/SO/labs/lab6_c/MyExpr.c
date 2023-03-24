#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    // verificăm apelarea cu (minim) trei argumente
    if(argc < 4)
    {
        fprintf(stderr,"Usage: %s N fisier-sursa fisier-destinatie\n", argv[0]);
        exit(1);
    }

    // verificăm existența și dreptul de citire a fișierului de intrare
    if( -1 == access(argv[2],R_OK) )
    {
        fprintf(stderr,"Eroare la access pentru %s .\t", argv[2]);
        perror("Cauza este");
        exit(2);
    }

    // trebuie să convertim string-ul argv[1] la valoarea sa numerică ca și long int
    long int N;
    errno = 0;  /* To distinguish success/failure after call */
    N = strtol(argv[1],NULL,10);  /* facem conversia */
    if(errno != 0)
    {
        fprintf(stderr,"Eroare de conversie numerica pentru parametrul: %s\n", argv[1]);
        perror("Cauza este");
        exit(3);
    }

    // validarea parametrului de intrare numeric
    if(N <= 0)
    {
        fprintf(stderr,"Eroare: parametrul N trebuie sa fie numar strict pozitiv.\n");
        exit(4);
    }

    FILE *f_sursa, *f_dest;

    // inițializarea sesiunii de lucru cu fișierul de intrare
    if( NULL == (f_sursa = fopen(argv[2],"r")) )
    {
        fprintf(stderr,"Eroare la deschiderea read-only a fisierului %s\n", argv[2]);
        perror("Cauza este");
        exit(5);
    }

    // inițializarea sesiunii de lucru cu fișierul pentru rezultate, în modul APPEND
    if( NULL == (f_dest = fopen(argv[3],"a")) )
    {
        fprintf(stderr,"Eroare la deschiderea write-only cu append a fisierului %s\n",argv[3]);
        perror("Cauza este");
        exit(6);
    }

    int linia_curenta=0, nr1, nr2;
    float rezultat;
    char ch;

    // bucla de procesare a fișierului de intrare
    while( ! feof(f_sursa) )
    {
        int cod_r;
        cod_r = fscanf(f_sursa,"%d %d %c\n",&nr1, &nr2, &ch);
        if( (cod_r != 3) && (cod_r != EOF) )
        {
            fprintf(stderr,"Eroare: linia %d din fisierul %s nu respecta formatul specificat in enuntul problemei.\n", linia_curenta, argv[2]);
            exit(7);
        }

        linia_curenta++;
        if(linia_curenta == N)
        {
            int valid=1;
			
            switch(ch)
            {
                case '+': rezultat = nr1 + nr2; break;
                case '-': rezultat = nr1 - nr2; break;
                case '*': rezultat = nr1 * nr2; break;
                case '/': if (nr2 == 0)
                          {
                              fprintf(stderr,"Operatie imposibila: %d %c %d (impartire la zero)\n",nr1, ch, nr2);
                              valid=0;
                          }
                          else rezultat = (float) nr1 / nr2;
                          break;
                default : fprintf(stderr,"Eroare in linia %d din fisierul de intrare %s, operator necunoscut: %ch !\n", N, argv[2], ch);
                          valid=0;
            }

            if(valid)
            {
                fprintf(f_dest,"%d %c %d = %.2f\n", nr1, ch, nr2, rezultat);
            }

            break;   // ieșim din while
        }
    }

    if(linia_curenta < N)
    {
        fprintf(stderr,"Eroare: linia %ld nu exista in fisierul sursa (acesta are doar %d linii).\n",N,linia_curenta);
    }

    // finalizarea sesiunilor de lucru cu fișierele de intrare și de ieșire
    fclose(f_sursa);
    fclose(f_dest);

    return 0;
}
