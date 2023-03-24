/*
*   Program: șablonul producător-consumator din exemplul demonstrativ pipe_ex2.c, rescris cu fifo în loc de pipe.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(void)
{
	int nr, cod_r;
	FILE *fin,*fout;
	pid_t pid;

	/* creare canal fifo */
	if(-1 == mkfifo("canal_fifo", 0600) )
	{
		if(errno == EEXIST)   // errno=17 for "File already exists"
			fprintf(stdout,"Nota: canalul fifo 'canal_fifo' exista deja !\n");
		else
		{
			perror("Eroare la crearea canalului fifo. Cauza erorii");  exit(1);
		}
	}

	/* creare proces fiu */
	if(-1 == (pid=fork()) )
	{
		perror("Eroare la crearea unui proces fiu. Cauza erorii");  exit(2);
	}

	if(pid)
	{ /* in tata */

		/* tatal isi deschide capatul de scriere */
		fout = fopen("canal_fifo","w");

		/* citeste numere de la tastatura, pentru terminare: ENTER urmat de CTRL+D (i.e. EOF in UNIX), si le transmite prin canal procesului fiu.
			OBSERVATIE: in canal numerele sunt scrise formatat, nu binar, si de aceea trebuie separate printr-un
			caracter care nu-i cifra (in acest caz am folosit '\n') pentru a nu se "amesteca" cifrele de la
			numere diferite atunci cand sunt citite din canal!		*/
		printf("Usage: introduceti numere intregi, separate prin spatii si/sau ENTER, si terminati cu Ctrl+D.\n");
    
		while( (cod_r=scanf("%d",&nr)) != EOF)
		{
			if(cod_r == 1)
			{
				fprintf(fout,"%d\n",nr);
				fflush(fout);
			}
			else
			{
				fprintf(stderr,"Eroare: nu ati introdus caractere permise sa apara intr-un numar!\n");  exit(3);
			}
		}

		/* tatal isi inchide capatul Write, pentru ca fiul sa poata citi EOF din canal ... */
		fclose(fout);

		/* ... si apoi asteapta terminarea fiului */
		wait(NULL);
	}
	else
	{ /* in fiu */

		/* fiul isi deschide capatul de citire */
		fin = fopen("canal_fifo","r");

		/* fiul citeste numerele din canal si le afiseaza pe ecran, pana depisteaza EOF in canal.
			OBSERVATIE: conform celor spuse mai sus, caracterul '\n' este folosit ca separator de numere! 	*/
    
		while(fscanf(fin,"%d",&nr) != EOF)
		{
			printf("[Fiu] Am primit numarul: %d\n",nr);
			fflush(stdout);
		}

		/* fiul isi inchide capatul Read */
		fclose(fin);
			/* Observatie: nu este nevoie neaparat de acest apel fclose() explicit,
			   deoarece oricum toti descriptorii sunt inchisi la terminarea programului. */
	}
	
	return 0;
}
