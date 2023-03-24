/*
* Filename: sortare_fara-lacate.c
*
* Prima variantă de sortare a unui fișier, incompletă, în sensul că NU folosim lacăte pentru acces exclusiv la secțiunea de fișier modificată la un moment dat.
*
* Ca urmare, soluția este corectă, i.e. va funcționa întotdeauna producând rezultatele corecte, DOAR dacă se lansează în execuție o singură instanță
* a programului, pentru a sorta un fișier de date.
* Dacă, însă, se lansează simultan mai multe instanțe ale programului (i.e., un job de tip SPMD), pentru a sorta concurent un același fișier de date,
* rezultatele finale sunt imprevizibile, putând fi incorecte, datorită fenomenelor de <i>data race</i> !!!
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void bubble_sort(int filedescr);

int main(int argc,char *argv[])
{
	int fd;
	if(argc < 2)
	{
		printf("Usage: %s datafile\n", argv[0]);  exit(1);
	}

	if(-1 == (fd = open(argv[1],O_RDWR)))
	{
		perror("Eroare la deschiderea fisierului de date");  exit(2);
	}
    
	bubble_sort(fd);

	close(fd);

	fprintf(stderr, "Notificare: [PID: %d] Am terminat (contributia mea la) sortarea fisierului %s !\n", getpid(), argv[1]);
	return 0;
}

void bubble_sort(int filedescr)
{
	int rcod1,rcod2;
	int numar1,numar2;

	int modificare = 1;

	/* Bucla while în care facem parcurgeri repetate ale fișierului. */
	while(modificare)
	{
		modificare = 0; /* va fi setat daca se face macar o inversiune la parcurgerea curenta */

		/* Bucla while pentru o singură parcurgere a fișierului. */
		while(1)
		{
			rcod1 = read(filedescr, &numar1, sizeof(int));
			if(rcod1 == 0) break; /* am ajuns la EOF */
			if(rcod1 ==-1)
			{
				perror("Eroare la citirea primului numar dintr-o pereche");  exit(3);
			}	

			rcod2 = read(filedescr, &numar2, sizeof(int));
			if(rcod2 == 0) break; /* am ajuns la EOF */
			if(rcod2 ==-1)
			{
				perror("Eroare la citirea celui de-al doilea numar dintr-o pereche");  exit(4);
			}	

			/* Dacă este inversiune, inter-schimbăm cele două numere în fișier. */
			if(numar1 > numar2)
			{
				modificare = 1;
			
				/* Ne întoarcem înapoi cu 2 întregi pentru a face rescrierea. */
				if(-1 == lseek(filedescr, -2*sizeof(int), SEEK_CUR))
				{
					perror("Eroare (1) la repozitionarea inapoi in fisier");  exit(5);
				}
	
				if(-1 == write(filedescr, &numar2, sizeof(int)))
				{
					perror("Eroare la rescrierea primului numar dintr-o pereche");  exit(6);
				}
			
				if(-1 == write(filedescr, &numar1, sizeof(int)))
				{
					perror("Eroare la rescrierea celui de-al doilea numar dintr-o pereche");  exit(7);
				}
			}
		
			/* Pregătim următoarea iterație: primul număr din noua pereche este cel de-al doilea număr din perechea precedentă. */
			if(-1 == lseek(filedescr, -sizeof(int), SEEK_CUR))
			{
				perror("Eroare (2) la repozitionarea inapoi in fisier");  exit(8);
			}
		}/* Sfârșitul buclei while pentru o singură parcurgere a fișierului. */

		/* Pregătim următoarea parcurgere: ne repoziționăm la începutul fișierului. */
		if(-1 == lseek(filedescr, 0L, SEEK_SET))
		{
			perror("Eroare (3) la repozitionarea inapoi in fisier");  exit(9);
		}

	}/* Sfârșitul buclei while de parcurgeri repetate ale fișierului. */
	
}
