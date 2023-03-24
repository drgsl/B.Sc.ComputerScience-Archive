/*
*   Program: suma_pipes.c
*
*   Funcționalitate: calculul "distribuit" al sumei, folosind două procese worker și comunicații prin canale anonime între supervisor și workeri.
*   Observație: este un exemplu de calcul paralel folosind strategia "supervisor-workers" (denumită uneori și "master-slaves").
*
*   Notă: practic, este problema cu suma distribuită de la lecția fork, rezolvată acum folosind canale anonime în loc de fișiere obișnuite.
*/
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

void master_init();
void master_work();
void slave_work(int fdi, int fdo);

/* Vectorii pentru cele 3 pipe-uri. */
int pipe1i[2], pipe2i[2], pipe3o[2]; 

int main(void)
{
    int pid1,pid2;
  
    printf("\n\n\n");
  
    /* Crearea celor 3 pipe-uri pipe1i, pipe2i și pipe3o. */ 
    master_init();

    /* Crearea primului proces worker/slave. */
    if(-1 == (pid1=fork()) )
    {
        perror("Eroare la fork pentru fiul #1");  exit(4);
    }
 
    if(pid1 == 0)
    {   /* Ramura then a if-ului este executată doar de procesul worker #1. */

    	/* Închid toate capetele de care nu am nevoie în acest proces. */
        close(pipe1i[1]);
        close(pipe3o[0]);
        close(pipe2i[0]); close(pipe2i[1]);
    
        slave_work(pipe1i[0],pipe3o[1]);

        return 0;  /* Sfârșitul execuției fiului #1. */ 
    }
    /* Altfel, sunt în procesul supervisor/master, executat în paralel cu ramura then a if-ului de mai sus, i.e. cu primul fiu !!! */

    /* Crearea celui de-al doilea proces worker/slave. */
    if(-1 == (pid2=fork()) )
    {
        perror("Eroare la fork pentru fiul #2");  exit(5);
    }
 
    if(pid2 == 0)
    {   /* Ramura then a if-ului este executată doar de procesul worker #2. */

        /* Închid toate capetele de care nu am nevoie în acest proces. */
        close(pipe2i[1]);
        close(pipe3o[0]);
        close(pipe1i[0]); close(pipe1i[1]);

        slave_work(pipe2i[0],pipe3o[1]);

        return 0;  /* Sfârșitul execuției fiului #2. */ 
    }
    /* Altfel, sunt în procesul supervisor/master, executat în paralel cu cei doi fii !!! */

    /* Închid toate capetele de care nu am nevoie în acest proces. */
    close(pipe1i[0]);
    close(pipe2i[0]);
    close(pipe3o[1]);

    /* Citește secvența de numere de la tastatură și o "împarte" fiilor,
    *  apoi primește de la fii cele două sume parțiale și afișează suma lor. */
    master_work();
    return 0;
}

/***********************************************************************/

void master_init()
{
    /* Crearea celor 3 pipe-uri fpipe1i, pipe2i și pipe3o. */ 

    if( pipe(pipe1i) == -1 )
    {
        perror("Eroare la crearea canalului pipe1i");  exit(1);
    }

    if( pipe(pipe2i) == -1 )
    {
        perror("Eroare la crearea canalului pipe2i");  exit(2);
    }

    if( pipe(pipe3o) == -1 )
    {
        perror("Eroare la crearea canalului pipe3o");  exit(3);
    }
}

/***********************************************************************/

void master_work()
{
    int nr, flag;
    int sump1,sump2;

    /* Putem citi numerele de la tastatură după crearea fiilor, deși citirea de la tastatură poate dura oricât de mult (!),
    *  deoarece sincronizarea necesară (fiul trebuie să-și aștepte tatăl să scrie în canal, pentru a avea ce citi)
    *  este realizata aici prin faptul că citirea din canal se face, implicit, în mod blocant. */
 
    /* Citirea secvenței de numere și "împărțirea" ei între cele două canale. */
    printf("Introduceti numerele (0 pentru terminare):\n");
    flag=1;
    while(1)
    {
        scanf("%d", &nr);
        if(nr == 0) break;

        write( (flag==1 ? pipe1i[1] : pipe2i[1]), &nr, sizeof(int));
        flag=3-flag;
    }
  
    close(pipe1i[1]);
    close(pipe2i[1]);

    /* Aici mai avem o problemă de sincronizare: masterul trebuie să citească sumele parțiale abia după ce acestea
    *  au fost calculate și scrise în canalul pipe3o de către procesele slave.
    *  Realizarea sincronizării se bazează, aici, pe faptul că citirea din canal este, implicit, blocantă. */ 
 
    /* Citește prima sumă parțială (sosită de la oricare dintre cei doi workeri). */
    if( read(pipe3o[0], &sump1, sizeof(int)) != sizeof(int) )
    {
        fprintf(stderr,"Eroare la prima citire din pipe-ul pipe3o\n");  exit(6);
    }
  
    /* Citește a doua sumă parțială. */
    if( read(pipe3o[0], &sump2, sizeof(int)) != sizeof(int))
    {
        fprintf(stderr,"Eroare la a doua citire din pipe-ul pipe3o\n");  exit(7);
    }

    close(pipe3o[0]);
  
    /* Afișează suma finală. */
    printf("Master[PID:%d]> Suma secventei de numere introduse este: %d\n", getpid(), sump1+sump2);
}

/***********************************************************************/

void slave_work(int fdi, int fdo)
{
    int nr, cod_r, suma_partiala = 0;

    /* Citirea numerelor din canal, într-o buclă, până "întâlnește" EOF în canal. */
    do
    {
        cod_r = read(fdi, &nr, sizeof(int));
        switch(cod_r)
        {
            case sizeof(int) : suma_partiala += nr ;  break;
            case 0           : break;  // 0 înseamnă EOF în canal
            default          : fprintf(stderr,"Eroare la citirea din canalul pipe%ci\n", (fdi==pipe1i[0] ? '1':'2') );  exit(8);
        }
    }while(cod_r != 0);
  
    close(fdi);

    /* Scrierea sumei (parțiale) calculate în canal. */  
    if(-1 == write(fdo, &suma_partiala, sizeof(int)) )
    {
        perror("Eroare la scrierea in canalul pipe3o");  exit(9);
    }
  
    close(fdo);

    /* Afișarea unui mesaj informativ pe ecran... */
    printf("Slave%c[PID:%d]> Suma partiala: %d\n", (fdi==pipe1i[0] ? '1' : '2'), getpid(), suma_partiala );
}

/***********************************************************************/
