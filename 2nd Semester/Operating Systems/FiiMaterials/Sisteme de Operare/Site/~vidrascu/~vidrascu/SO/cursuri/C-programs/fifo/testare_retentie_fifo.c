/*
*   Program: testare_retentie_fifo.c
*
*   Funcționalitate: testează "durata de persistență" a conținutului unui fișier fifo,
*   i.e. răspunde la întrebarea "Care este perioada de retenție, într-un canal fifo, a informațiilor scrise în el?"
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char** argv)
{
    int   fdR, fdW, fdRW, codW, codR;
    char  bufW[10] = "123abc789";
    char  bufR[10];
    char* canal;
 
    if(argc != 2)
    {
        fprintf(stderr,"Sintaxa apel: testare_retentie_fifo nume_fifo\n");  exit(1);
    }
  
    canal = argv[1];

    char  comanda_ls[100] = "ls -l ";
    strcat(comanda_ls,canal);

    if(-1 == mkfifo(canal, 0600) )
    {
        if(errno == EEXIST)   // EEXIST=17 : valoarea lui errno pentru situația "File exists"
        {
           fprintf(stdout,"Observatie: fisierul fifo %s exista deja !\n",canal);
        }
        else
        {
            perror("Eroare: creare fisier fifo imposibila; cauza erorii este");  exit(2);
        }
    }


    fdR = open(canal, O_RDONLY | O_NONBLOCK );
    if(-1 == fdR)
    {
        perror("Eroare la deschiderea neblocanta a capatului de citire al canalului");  exit(3);
    }

    fdW = open(canal, O_WRONLY);
    if(-1 == fdW)
    {
        perror("Eroare la deschiderea capatului de scriere al canalului");  exit(4);
    }

    /* De ce am deschis pe rând capetele? Am fi putut scrie, echivalent, un singur apel open: fd = open(canal, O_RDWR);
    *  Însă, mai jos, am nevoie de descriptori diferiți pentru cele două capete, ca să le pot închide individual, și pentru a avea citire neblocantă (!!!) */

    codW = write(fdW,bufW,strlen(bufW));
    if(-1 == codW)
    {
        perror("Eroare la scrierea unui mesaj in canal");  exit(5);
    }
    else
        printf("\nS-au scris %d octeti in canal --> si anume, secventa de caractere: '%s'\n", codW, bufW);
  
    sleep(1);
    printf("Dimensiunea fisierului fifo, dupa scrierea in el, este:\n");
    system(comanda_ls);
  
    sleep(4);
    codR = read(fdR,bufR,3);
    if(-1 == codR)
    {
        perror("Eroare la prima citire din canal");
        if(errno == EAGAIN)
            fprintf(stderr,"Eroare EAGAIN la citire (i.e. canalul este gol)!\n");
        else
            { fprintf(stderr,"Eroare errno=%d la citire.\n", errno); perror("Cauza ei"); }
        exit(6);
    }
    bufR[codR] = 0;
    printf("\nS-au citit din canal primii %d octeti: '%s'\n", codR, bufR);

    sleep(1);
    printf("Dimensiunea fisierului fifo, dupa prima citire a 3 octeti din el, este:\n");
    system(comanda_ls);
  
    sleep(2);
    close(fdW);
    printf("\nAm inchis capatul de scriere. Dimensiunea fisierului fifo, dupa inchiderea capatului de scriere, este:\n");
    system(comanda_ls);
  
    sleep(4);
    codR = read(fdR,bufR,3);
    if(-1 == codR)
    {
        perror("Eroare la a doua citire din canal");
        if(errno == EAGAIN)
        {
            fprintf(stderr,"Eroare EAGAIN la citire (i.e. canalul este gol)!\n");
            printf("Asadar, nu s-a mai putut citi nimic din canal dupa inchiderea capatului de scriere (i.e., ceilalti 6 octeti din canal s-au 'pierdut').\n");
            exit(7);
        }
        else
        {
            fprintf(stderr,"Eroare errno=%d la citire.\n",errno);  perror("Cauza ei");
            exit(8);
        }
    }
    else
    { /* Sigur codR > 0 , căci capătul de citire al canalului a fost setat cu comportament neblocant... */
        bufR[codR] = 0;
        printf("\nS-au citit din canal urmatorii %d octeti: '%s'\n", codR, bufR);
    }

    sleep(2);
    close(fdR);
    printf("\nAm inchis si capatul de citire. Dimensiunea fisierului fifo, in acest moment, este:\n");
    system(comanda_ls);

    sleep(5);
    fdRW = open(canal, O_RDWR | O_NONBLOCK );  /* Este necesar acest atribut O_NONBLOCK, ca să nu rămână blocat apelul read ce urmează mai jos (!!!) */
    if(-1 == fdRW)
    {
        perror("Eroare la redeschiderea canalului (simultan la ambele capete ale canalului)");  exit(9);
    }

    codR = read(fdRW,bufR,3);
    if(-1 == codR)
    {
        perror("\nEroare la a treia citire din canal");
        if(errno == EAGAIN)
        {
            fprintf(stderr,"Eroare EAGAIN la citire (i.e. canalul este gol)!\n");
            printf("Asadar, nu s-a mai putut citi nimic din canal dupa inchiderea ambelor capete si apoi redeschiderea lor "
             "(i.e., ultimii 3 octeti din canal s-au 'pierdut' cand am inchis si capatul de citire)!\n");
            //exit(10);
        }
        else
        {
            fprintf(stderr,"Eroare errno=%d la citire.\n",errno);
            exit(11);
        }
    }
    else // sigur codR > 0 , caci canalul (i.e. la ambele sale capete) a fost setat cu comportament neblocant...
    { /* Sigur codR > 0 , căci canalul (i.e., ambele capete ale lui) a fost setat cu comportament neblocant... */
        bufR[codR] = 0;
        printf("\nS-au citit din canal ultimii %d octeti: '%s'\n", codR, bufR);
    }
    close(fdRW);

    sleep(1);
    printf("\nSfarsitul programului de testare a retentiei.\n");
    return 0;
}

/*
*  Concluzii:
*
*  1) Comanda ls -l va afișa întotdeauna lungimea 0 pentru un fișier fifo, chiar dacă are informație în el (!)
*
*  2) Perioada de retenție într-un canal fifo a informațiilor scrise în el:
*
*     - Informația scrisă în canal nu se pierde atât timp cât măcar vreunul dintre capetele canalului este menținut deschis de vreun proces;
*       Spre exemplu, în situația ilustrată de programul de mai sus, informația încă mai putea fi citită și după ce nu mai existau scriitori (i.e.,
*       niciun proces care să mențină deschis capătul de scriere), dar înca mai era activ cititorul (i.e., un proces ce are deschis capătul de citire).
*
*     - În schimb, dacă nu mai există nici cititori și nici scriitori (i.e., niciun proces nu mai menține deschis niciunul dintre capetele canalului),
*       informația neconsumată din canal se pierde, i.e. nu mai poate fi regăsită ulterior prin redeschiderea canalului și citirea din el!
*/

