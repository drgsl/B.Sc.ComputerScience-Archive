/*
*   Programul #1: lant-3cmds_cmd1--restul-lantului.c
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
	pid_t pid;
	int p[2];

	if(-1 == pipe(p) )
	{
		fprintf(stderr, "Eroare: nu pot crea un canal anonim, errno=%d\n",errno);  perror("Cauza erorii");  exit(1);
	}

	if(-1 == (pid=fork()) )
	{
		perror("Eroare: nu am putut crea un fiu. Cauza erorii");  exit(2);
	}

	if(pid == 0)
	{
		if(-1 == dup2(p[1],1) )
		{
			perror("Eroare: redirectarea iesirii standard in fiu a esuat. Cauza erorii");  exit(3);
		}

		execlp("grep", "grep", "/bin/bash", "/etc/passwd", NULL);
		perror("Eroare la execlp() in fiu. Cauza erorii");  exit(4);
	}
	else
	{
		close(p[1]); // E necesar acest close pentru ca să se termine execuția comenzii cut (prin "citirea" EOF din canal)

		if(-1 == dup2(p[0],0) )
		{
			perror("Eroare: redirectarea intrarii standard in parinte a esuat. Cauza erorii");  exit(5);
		}

		execl("lant-3cmds_cmd2--cmd3.exe", "lant-3cmds_cmd2--cmd3", NULL);
		perror("Eroare la execl() in parinte. Cauza erorii");  exit(6);
	}

	return 0;  // Fluxul de execuție nu va ajunge niciodată aici!
}