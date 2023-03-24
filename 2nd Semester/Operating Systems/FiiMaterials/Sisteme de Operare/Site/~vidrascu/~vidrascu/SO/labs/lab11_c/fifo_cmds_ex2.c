/*
*   Program: executarea a trei comenzi simple în paralel, înlănțuite! Varianta cu canale fifo, în loc de canale anonime.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main()
{
	pid_t pid1, pid2;
	int fdi, fdo;

	if(-1 == mkfifo("fifo_Cmd1toCmd2", 0600) )
	{
		if(errno != EEXIST)   // errno=17 for "File already exists"
		{  perror("Eroare la crearea canalului fifo. Cauza erorii");  exit(1);  }
	}

	if(-1 == mkfifo("fifo_Cmd2toCmd3", 0600) )
	{
		if(errno != EEXIST)   // errno=17 for "File already exists"
		{  perror("Eroare la crearea canalului fifo. Cauza erorii");  exit(2);  }
	}

	if(-1 == (pid1=fork()) )
	{  perror("Eroare: nu am putut crea primul fiu. Cauza erorii");  exit(3);  }

	if(pid1 == 0)
	{

		if(-1 == (pid2=fork()) )
		{  perror("Eroare: nu am putut crea al doilea proces fiu. Cauza erorii");  exit(4);  }

		if(pid2 == 0)
		{
			if(-1 == (fdo = open("fifo_Cmd1toCmd2",O_WRONLY)) )
			{  perror("Eroare: apelul open in al doilea proces fiu a esuat. Cauza erorii");  exit(5);  }

			if(-1 == dup2(fdo,1) )
			{  perror("Eroare: redirectarea iesirii standard in al doilea proces fiu a esuat. Cauza erorii");  exit(6);  }
	
			execlp("grep","grep","/bin/bash","/etc/passwd",NULL);
			perror("Eroare la execlp() in al doilea proces fiu. Cauza erorii");  exit(7);
		}
		else
		{
			if(-1 == (fdi = open("fifo_Cmd1toCmd2",O_RDONLY)) )
			{  perror("Eroare: apelul open in primul fiu a esuat. Cauza erorii");  exit(8);  }
	
			if(-1 == dup2(fdi,0) )
			{  perror("Eroare: redirectarea intrarii standard in primul fiu a esuat. Cauza erorii");  exit(9);  }


			if(-1 == (fdo = open("fifo_Cmd2toCmd3",O_WRONLY)) )
			{  perror("Eroare: apelul open in primul proces fiu a esuat. Cauza erorii");  exit(10);  }

			if(-1 == dup2(fdo,1) )
			{  perror("Eroare: redirectarea iesirii standard in primul fiu a esuat. Cauza erorii");  exit(11);  }
	
			execlp("cut","cut","-d:","-f1,3-5",NULL);
			perror("Eroare la execlp() in primul fiu. Cauza erorii");  exit(12);
		}

	}
	else
	{
		if(-1 == (fdi = open("fifo_Cmd2toCmd3",O_RDONLY)) )
		{  perror("Eroare: apelul open in parinte a esuat. Cauza erorii");  exit(13);  }
	
		if(-1 == dup2(fdi,0) )
		{  perror("Eroare: redirectarea intrarii standard in parinte a esuat. Cauza erorii");  exit(14);  }

		execlp("sort","sort","-t:","-k","2,2","-n",NULL);
		perror("Eroare la execlp() in parinte. Cauza erorii");  exit(15);
	}

	return 0;  // Fluxul de execuție nu va ajunge niciodată aici!
}
