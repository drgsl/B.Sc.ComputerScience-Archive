/*
*   Program: șablonul producător-consumator din exemplul demonstrativ pipe_ex1.c, rescris cu fifo în loc de pipe.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define NMAX 1000

int main(void)
{
	int p[2];
	char ch;
	pid_t pid;

	/* Creare canal fifo. */
	if(-1 == mkfifo("canal_fifo", 0600) )
	{
		if(errno == EEXIST)   // errno=17 for "File already exists"
			fprintf(stdout,"Nota: canalul fifo 'canal_fifo' exista deja !\n");
		else
		{
			perror("Eroare la crearea canalului fifo. Cauza erorii");  exit(1);
		}
	}

	/* Creare proces fiu. */
	if(-1 == (pid=fork()) )
	{
		perror("Eroare la crearea unui proces fiu. Cauza erorii");  exit(2);
	}

	if(pid)
	{ /* Secvență de cod executată doar de procesul tată. */

		/* Tatăl își deschide capătul de scriere în canal. */
		p[1] = open("canal_fifo", O_WRONLY);

		/* Tatăl citește o secvență de caractere de la tastatură, pentru terminare: ENTER urmat de CTRL+D (i.e. EOF in UNIX),
		   si le transmite fiului prin canal doar pe acelea care sunt litere mici.		*/
		printf("Usage: tastati orice caractere si terminati cu ENTER urmat de Ctrl+D.\n");
	
		while( (ch=getchar()) != EOF)
			if((ch >= 'a') && (ch <= 'z'))
				write(p[1],&ch,1);

		/* tatal isi inchide capatul Write, pentru ca fiul sa poata citi EOF din canal ... */
		close(p[1]);

		/* ... si apoi asteapta terminarea fiului */
		wait(NULL);
	}
	else
	{ /* in fiu */
		char buffer[NMAX];
		int nIndex = 0;

		/* fiul isi deschide capatul de citire */
		p[0] = open("canal_fifo", O_RDONLY);

		/* fiul citeste caracterele din pipe si le salveaza in buffer,
		   pana depisteaza EOF, apoi afiseaza continutul bufferului.   */

		while( read(p[0],&ch,1) != 0)
			if(nIndex < NMAX)
				buffer[nIndex++] = ch;

		buffer[ (nIndex==NMAX) ? NMAX-1 : nIndex ] = '\0';
		printf("Fiu: am primit mesajul: %s\n",buffer);

		/* fiul isi inchide capatul Read */
		close(p[0]);
			/* Observatie: nu este nevoie neaparat de acest apel close() explicit,
			   deoarece oricum toti descriptorii sunt inchisi la terminarea programului. */
	}

	return 0;
}