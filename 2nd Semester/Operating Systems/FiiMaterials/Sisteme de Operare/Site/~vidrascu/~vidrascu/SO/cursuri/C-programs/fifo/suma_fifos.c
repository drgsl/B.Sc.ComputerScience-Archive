/*
*   Program: suma_fifos.c
*
*   Funcționalitate: calculul "distribuit" al sumei, folosind două procese worker și comunicații prin canale fifo între supervisor și workeri.
*   Observație: este un exemplu de calcul paralel folosind strategia "supervisor-workers" (denumită uneori și "master-slaves").
*
*   Notă: practic, este problema cu suma distribuită de la lecția fork, rezolvată acum folosind canale fifo în loc de fișiere obișnuite.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

void master_init();
void master_work();
void slave_work(char* fi, char* fo);

int main()
{
    int pid1,pid2;
  
    printf("\n\n\n");
  
    /* Crearea celor 3 fifo-uri fifo1i, fifo2i și fifo3o. */ 
    master_init();
 
    /* Crearea primului proces worker/slave. */
    if(-1 == ( pid1=fork() ) )
    {
        perror("Eroare la fork pentru fiul #1");  exit(4);
    }
 
    if(pid1 == 0)
    {   /* Ramura then a if-ului este executată doar de procesul worker #1. */

        slave_work("fifo1i","fifo3o");

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

        slave_work("fifo2i","fifo3o");

        return 0;  /* Sfârșitul execuției fiului #2. */ 
    }
    /* Altfel, sunt în procesul supervisor/master, executat în paralel cu cei doi fii !!! */

    /* Citește secvența de numere de la tastatură și o "împarte" fiilor,
    *  apoi primește de la fii cele două sume parțiale și afișează suma lor. */
    master_work();
    return 0;
}

/***********************************************************************/

void master_init()
{
    /* Crearea celor 3 fifo-uri fifo1i, fifo2i și fifo3o. */ 

    if( mkfifo("fifo1i", 0600) == -1 )
    {
        if(errno == EEXIST)  // EEXIST=17 : valoarea lui errno pentru situația "File exists"
        {
            perror("Eroare la crearea fifo-ului fifo1i");  exit(1);
        }
    }

    if( mkfifo("fifo2i", 0600) == -1 )
    {
        if(errno == EEXIST)  // EEXIST=17 : valoarea lui errno pentru situația "File exists"
        {
            perror("Eroare la crearea fifo-ului fifo2i");  exit(2);
        }
    }

    if( mkfifo("fifo3o", 0600) == -1 )
    {
        if(errno == EEXIST)  // EEXIST=17 : valoarea lui errno pentru situația "File exists"
        {
            perror("Eroare la crearea fifo-ului fifo3o");  exit(3);
        }
    }
}

/***********************************************************************/

void master_work()
{
    int fd1, fd2, fd3;
    int nr, flag;
    int sump1,sump2;

    /* Putem citi numerele de la tastatură după crearea fiilor, deși citirea de la tastatură poate dura oricât de mult (!),
    *  deoarece sincronizarea necesară (fiul trebuie să-și aștepte tatăl să scrie în canal, pentru a avea ce citi)
    *  este realizata aici prin faptul că citirea din canal se face, implicit, în mod blocant. */
 
 
    /* Deschiderea celor două canale fifo de intrare (i.e., cele prin care trimite numerele către workeri). */
    if( (fd1=open("fifo1i",O_WRONLY)) == -1)
    {
        perror("Eroare la deschiderea fifo-ului fifo1i\n");  exit(6);
    }
    if( (fd2=open("fifo2i",O_WRONLY)) == -1)
    {
        perror("Eroare la deschiderea fifo-ului fifo2i\n");  exit(7);
    }

    /* Citirea secvenței de numere și "împărțirea" ei între cele două canale. */
    printf("Introduceti numerele (0 pentru terminare):\n");
    flag=1;
    while(1)
    {
        scanf("%d", &nr);
        if(nr == 0) break;

        write( (flag==1?fd1:fd2), &nr, sizeof(int));
        flag=3-flag;
    }
  
    close(fd1);
    close(fd2);


    /* Aici mai avem o problemă de sincronizare: masterul trebuie să citească sumele parțiale abia după ce acestea
    *  au fost calculate și scrise în canalul fifo3o de către procesele slave.
    *  
    *  Rezolvare posibilă: deschiderea în master (implicit, blocantă!) a fifo-ului se va sincroniza cu deschiderea sa în primul dintre cei doi slaves.
    *  Dar astfel ar putea fi pierdută suma de la celălalt slave, datorită unui data-race (!)
    *  (Scenariu posibil: primul slave închide fifo-ul și masterul "citește" astfel EOF înainte ca al doilea slave să apuce să deschidă fifo-ul).
    *
    *  O soluție pentru acest data-race: vom folosi wait() în master pentru a fi siguri că s-a terminat și al doilea slave.  */ 
 

    /* Deschiderea canalului fifo de ieșire (i.e., cel prin care primește sumele parțiale de la slaves). */
    if( (fd3=open("fifo3o",O_RDWR)) == -1)
    {
        perror("Eroare la deschiderea fifo-ului fifo3o\n");  exit(8);
    }

    /* Citește prima sumă parțială (sosită de la oricare dintre cei doi workeri). */
    if( read(fd3, &sump1, sizeof(int)) != sizeof(int))
    {
        fprintf(stderr,"Eroare la prima citire din fifo-ul fifo3o\n");  exit(9);
    }
  
    /* Citește a doua sumă parțială...
    *
    *  Aici trebuie să ne asigurăm ca și al doilea slave a apucat să deschidă fifo-ul, căci altfel read-ul următor va "citi" EOF.
    *  Deci îl vom aștepta (cu 2 apeluri wait):

    wait(NULL);
    wait(NULL);

    *  Totuși, această soluție nu este cea mai optimă -- ea funcționeaza numai în acest caz: trimiterea sumei de către slave
    *  se face chiar înainte de terminarea sa.
    *
    *  În cazul general (dacă slave-ul ar mai fi avut apoi și altceva de făcut), soluția optimă este următoarea:
    *  deschiderea în master a canalului fifo3o la ambele capete, nu doar la cel de citire (cel de care avea nevoie masterul),
    *  ceea ce am și făcut în apelul open de mai sus (i.e., am folosit O_RDWR, în loc de 0_RDONLY).   */

    if( read(fd3, &sump2, sizeof(int)) != sizeof(int))
    {
        fprintf(stderr,"Eroare la a doua citire din fifo-ul fifo3o\n");  exit(10);
    }

    close(fd3);
  
    /* Afișează suma finală. */
    printf("Master[PID:%d]> Suma secventei de numere introduse este: %d\n", getpid(), sump1+sump2);
}

/***********************************************************************/

void slave_work(char* fi, char* fo)
{
    int fd1,fd2;
    int nr, cod_r, suma_partiala = 0;

    /* Deschiderea fifo-ului de intrare (prin care primește numere de la master). */
    if(-1 == (fd1 = open(fi,O_RDONLY)) )
    {
        fprintf(stderr,"Eroare la deschiderea fifo-ului %s\n",fi);  perror("Cauza erorii");  exit(11);
    }

    /* Citirea numerelor din canal, într-o buclă, până "întâlnește" EOF în canal. */
    do
    {
        cod_r = read(fd1, &nr, sizeof(int));
        switch(cod_r)
        {
            case sizeof(int) : suma_partiala += nr ;  break;
            case 0           : break;  // 0 înseamnă EOF în canal
            default          : fprintf(stderr,"Eroare la citirea din canalul fifo %s\n", fi);  exit(12);
        }
    }while(cod_r != 0);

    close(fd1);

  /* Deschiderea fifo-ului de ieșire (prin care trimite suma parțială calculată către master). */
  if(-1 == (fd2 = open(fo,O_WRONLY)) )
  {
    fprintf(stderr,"Eroare la deschiderea canalului %s\n",fo);  perror("Cauza erorii");  exit(13);
  }

    /* Scrierea sumei (parțiale) calculate în canal. */  
    if(-1 == write(fd2, &suma_partiala, sizeof(int)) )
    {
        fprintf(stderr,"Eroare la scrierea in canalul %s\n",fo);  perror("Cauza erorii");  exit(14);
    }

    close(fd2);

    /* Afișarea unui mesaj informativ pe ecran... */
    printf("Slave%c[PID:%d]> Suma partiala: %d\n", (!strcmp(fi,"fifo1i") ? '1' : '2'), getpid(), suma_partiala);
}

/***********************************************************************/
