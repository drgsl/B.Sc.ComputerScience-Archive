/*
*   Program: executarea a două comenzi simple în paralel și înlănțuite!
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	pid_t pid;
	int pipe_Cmd1toCmd2[2];

	if(-1 == pipe(pipe_Cmd1toCmd2) )
	{  perror("Eroare: nu am putut crea un canal anonim. Cauza erorii");  exit(1);  }

	if(-1 == (pid=fork()) )
	{  perror("Eroare: nu am putut crea un fiu. Cauza erorii");  exit(2);  }

	if(pid == 0)
	{
		if(-1 == dup2(pipe_Cmd1toCmd2[1],1) )
		{  perror("Eroare: redirectarea iesirii standard in fiu a esuat. Cauza erorii");  exit(3);	}

		execlp("grep","grep","/bin/bash","/etc/passwd",NULL);
		perror("Eroare la execlp() in fiu. Cauza erorii");  exit(4);
	}
	else
	{
		close(pipe_Cmd1toCmd2[1]); // E necesar acest close pentru ca să se termine execuția comenzii cut (prin "citirea" EOF din canal).

		if(-1 == dup2(pipe_Cmd1toCmd2[0],0) )
		{  perror("Eroare: redirectarea intrarii standard in parinte a esuat. Cauza erorii");  exit(5);  }

		execlp("cut","cut","-d:","-f1,3-5",NULL);
		perror("Eroare la execlp() in parinte. Cauza erorii");  exit(6);
	}

	return 0;  // Fluxul de execuție nu va ajunge niciodată aici!
}
