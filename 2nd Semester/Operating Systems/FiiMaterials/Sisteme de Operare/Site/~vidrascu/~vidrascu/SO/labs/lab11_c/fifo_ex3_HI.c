/*
*   Programul #1: hi.c , este programul care afișează "hi"-uri pe ecran.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

int main(void)
{
	int fd_in, fd_out, nr_iteratii = 100;
	char ch='0';

	/* Creare canale fifo. */
	if(-1 == mkfifo("fifo_hi2ho", 0600) )
	{
		if(errno != EEXIST)   // errno=17 for "File already exists"
		{
			perror("Eroare la crearea canalului 'fifo_hi2ho'. Cauza erorii");  exit(1);
		}
	}

	/* Deschiderile strict necesare, i.e. doar ale capetelor de scriere sau de citire absolut necesare */
	fd_out = open("fifo_hi2ho",O_WRONLY);
	fd_in  = open("fifo_ho2hi",O_RDONLY);

	/* Bucla principală, ce afișează "hi"-uri pe ecran, conform șablonului de sincronizare specificat. */
	while(nr_iteratii > 0)
	{
		printf("Hi-"); fflush(stdout);  // Afișez pe ecran mesajul meu...

		write(fd_out,&ch,1);            // Îi trimit "notificare" celuilalt că este rândul lui (să afișeze pe ecran).

		read(fd_in,&ch,1);              // Aștept să primesc "notificare" de la celălalt că este rândul meu (să afișez pe ecran).

		nr_iteratii--;
	}

	return 0;
}
