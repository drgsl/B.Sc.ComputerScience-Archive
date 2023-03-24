#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // verificăm apelarea cu (minim) două argumente
    if(argc < 3)
    {
        fprintf(stderr,"Usage: %s fisier-sursa fisier-destinatie\n", argv[0]);
        exit(1);
    }

    // verificăm existența și dreptul de citire a fișierului de intrare
    if( -1 == access(argv[1],R_OK) )
    {
        fprintf(stderr,"Eroare la access pentru %s .\t", argv[1]);
        perror("Cauza este");
        exit(2);
    }

    FILE *f_sursa, *f_dest;

    // inițializarea sesiunii de lucru cu fișierul ce trebuie procesat
    if( NULL == (f_sursa = fopen(argv[1],"r")) )
    {
        fprintf(stderr,"Eroare la deschiderea read-only a fisierului %s\n",argv[1]);
        perror("Cauza este");
        exit(3);
    }

    // inițializarea sesiunii de lucru cu fișierul pentru rezultate
    if( NULL == (f_dest = fopen(argv[2],"w")) )
    {
        fprintf(stderr,"Eroare la deschiderea write-only a fisierului %s\n",argv[2]);
        perror("Cauza este");
        exit(4);
    }

    int val=0, nr=0, sum=0;

    // bucla de procesare a fișierului de intrare
    while(1)    /* Sau, echivalent:  while(! feof(f_sursa))  */
    {
        int cod_r;
        cod_r = fscanf(f_sursa,"%d",&val);

        if(cod_r == EOF) break;
             /* Observație: apelul feof() întoarce true abia după ce un apel de genul fscanf()/fread() "citește" poziția End-Of-File,
                            situație în care variabila noastră val va rămâne cu valoarea veche (de la iterația precedentă),
                            deci trebuie să ne asigurăm că nu prelucrăm de două ori ultimul număr din fișierul de intrare !!!        */

        if(cod_r != 1)
        {
            fprintf(stderr,"Eroare la citirea din fisierul %s\n",argv[1]);
            perror("Cauza este");
            exit(5);
        }

        if(0 != val)
        {
            sum += val;
            nr++;
            printf("%d %d %d\n", val, sum, nr); /* afișare pe ecran, cu rol informativ */
        }
        else /* am găsit un zero ce indică sfârșitul unui grup de numere */
        {
            if(0 != nr) {   // trebuie să ne asigurăm că avem cel puțin un număr în grup, altfel este împărțire la zero!
                fprintf(f_dest,"%.2f\n",(float)sum/nr);
            }
            sum = 0;
            nr  = 0;
        }
    }

    if(0 != nr) fprintf(f_dest,"%.2f\n",(float)sum/nr);  // ultimul grup de numere, pentru care lipsește 0-ul final, delimitatorul de grup fiind chiar EOF !

    // finalizarea sesiunilor de lucru cu fișierele de intrare și de ieșire
    fclose(f_sursa);
    fclose(f_dest);

    return 0;
}
