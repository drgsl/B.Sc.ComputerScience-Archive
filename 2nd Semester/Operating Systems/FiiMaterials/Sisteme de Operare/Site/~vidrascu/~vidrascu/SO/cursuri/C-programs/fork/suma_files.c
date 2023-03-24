/*
*   Program: suma_files.c
*
*   Funcționalitate: calculul "distribuit" al sumei, folosind două procese worker și comunicații prin fișiere între supervisor și workeri.
*   Observație: este un exemplu de calcul paralel folosind strategia "supervisor-workers" (denumită uneori și "master-slaves").
*/
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>

void master_init();
void master_finish();
void slave_work(char* fi, char* fo);

int main()
{
    int pid1,pid2;

    printf("\n\n\n");

    /* Curăță rezultatele execuțiilor anterioare -> necesar !!! */
    remove("f1o"); remove("f2o");

    /* Citirea secvenței de numere de la tastatură și scrierea ei divizată între fișierele f1i și f2i */ 
    master_init();
 
    /* Atenție: am citit numerele înainte de (și NU după) crearea fiilor, deoarece este nevoie de următoarea sincronizare:
       fiecare proces fiu (aka worker) trebuie să aștepte ca tatăl (aka supervisorul) să scrie numerele în fișier, pentru a avea ce citi din fișier,
       iar citirea numerelor de la tastatură în supervisor poate dura oricât de mult... */
 
    /* Crearea primului proces worker/slave. */
    if(-1 == (pid1=fork()) )
    {
        perror("Eroare la fork pentru fiul #1");  exit(1);
    }
 
    if(pid1 == 0)
    {   /* Ramura then a if-ului este executată doar de procesul worker #1. */

        slave_work("f1i","f1o");

        return 0;  /* Sfârșitul execuției fiului #1. */ 
    }
    /* Altfel, sunt în procesul supervisor/master, executat în paralel cu ramura then a if-ului de mai sus, i.e. cu primul fiu !!! */
 
    /* Crearea celui de-al doilea proces worker/slave. */
    if(-1 == (pid2=fork()) )
    {
        perror("Eroare la fork pentru fiul #2");  exit(2);
    }
 
    if(pid2 == 0)
    {   /* Ramura then a if-ului este executată doar de procesul worker #2. */
 
        slave_work("f2i","f2o");

        return 0;  /* Sfârșitul execuției fiului #2. */ 
    }
    /* Altfel, sunt în procesul supervisor/master, executat în paralel cu cei doi fii !!! */
 
    /* Citește cele două sume parțiale și afișează suma lor. */
    master_finish();
    return 0;
}

/***********************************************************************/

void master_init()
{
    FILE *f1,*f2;
    int nr, flag;

    if( (f1=fopen("f1i","wt")) == NULL)
    {
        fprintf(stderr,"Error opening file f1i, err=%d\n",errno);  exit(4);
    }
    if( (f2=fopen("f2i","wt")) == NULL)
    {
        fprintf(stderr,"Error opening file f2i, err=%d\n",errno);  exit(5);
    }

    printf("Introduceti numerele (0 pentru terminare):\n");
    flag=1;
    do
    {
        scanf("%d", &nr);

        fprintf( (flag==1?f1:f2), "%d ", nr);
		/* Atenție: spațiul din formatul de la fprintf este necesar, ca și separator între numere întregi reprezentate 'textual' !!! */

        flag=3-flag;

    }while(nr!=0);

    fclose(f1);  fclose(f2);
}

/***********************************************************************/

void master_finish()
{
    /* Aici mai apare necesitatea unei sincronizări:
       procesul supervisor/master trebuie să citească sumele parțiale din fișierele f1o și f2o abia după 
       ce acestea au fost calculate și scrise în fișierele respective de către procesele worker/slave (!)
       
       Rezolvare: supervisorul face încercări repetate de citire, cu o mică pauză între două încercări succesive. (Aceasta este soluția generală,
       aplicabilă când procesele worker nu se termină imediat după ce au scris sumele parțiale în fișiere, ci mai au și altceva de calculat...)
	   
       Sau, aici, deoarece în cazul nostru procesele worker se termină imediat după ce au scris sumele parțiale în fișiere, putem aplica și o altă idee,
       mai simplă: supervisorul poate aștepta terminarea celor doi fii, folosind două apeluri wait(NULL); , și abia apoi să citească cele două sume parțiale.
    */ 

    FILE *f1,*f2;
    int sp1,sp2, cod;

    /* În continuare, ilustrez soluția generală: încearcă să citească, în mod repetat, până reușeste...).
    /* Citește prima sumă parțială, în mod repetat, până reușeste... */
    cod = 0;
    do
    {
        if( (f1=fopen("f1o","rt")) != NULL)
            cod = (fscanf(f1,"%d",&sp1)==1);
        if(!cod)
            sleep(3);
    }while(!cod);
    fclose(f1);

    /* Citește a doua sumă parțială, în mod repetat, până reușeste... */
    cod = 0;
    do
    {
        if( (f2=fopen("f2o","rt")) != NULL)
            cod = (fscanf(f2,"%d",&sp2)==1);
        if(!cod)
            sleep(3);

    }while(!cod);
    fclose(f2);

    /* Afișează suma finală. */
    printf("[Master PID=%d] Suma numerelor introduse este: %d\n", getpid(), sp1+sp2);
}

/***********************************************************************/

void slave_work(char* fi, char* fo)
{
    FILE *f1,*f2;
    int nr,cod, suma_partiala=0;

    if( (f1 = fopen(fi,"rt")) == NULL)
    {
        fprintf(stderr,"Error opening file %s, err=%d\n",fi,errno);  exit(6);
    }

    do
    {
        cod=fscanf(f1,"%d", &nr);
        if(cod == 1)
            suma_partiala += nr; 

    }while(cod != EOF);

    fclose(f1);

    if( (f2 = fopen(fo,"wt")) == NULL)
    {
        fprintf(stderr,"Error opening file %s, err=%d\n",fo,errno);  exit(7);
    }

    fprintf(f2,"%d",suma_partiala);

    fclose(f2);

    printf("[Slave PID=%d] Suma partiala: %d\n", getpid(), suma_partiala);
}

/***********************************************************************/
