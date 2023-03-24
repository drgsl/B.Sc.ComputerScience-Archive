/*
*   Program: executarea a trei comenzi simple în paralel și înlănțuite!
*
*   Ierarhia celor 3 procese necesare: un părinte cu doi fii.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
	pid_t pid1, pid2;
	int pipe_Cmd1toCmd2[2], pipe_Cmd2toCmd3[2];

	if(-1 == pipe(pipe_Cmd1toCmd2) )
	{  fprintf(stderr, "Eroare: nu pot crea primul canal anonim, errno=%d\n",errno);  perror("Cauza erorii");  exit(1);  }

	if(-1 == pipe(pipe_Cmd2toCmd3) )
	{  fprintf(stderr, "Eroare: nu pot crea al doilea canal anonim, errno=%d\n",errno);  perror("Cauza erorii");  exit(2);  }

	if(-1 == (pid1=fork()) )
	{  perror("Eroare: nu am putut crea primul fiu. Cauza erorii");  exit(3);  }

	if(pid1 == 0)
	{ // Secțiune de cod executată doar de către primul fiu al procesului inițial.
		if(-1 == dup2(pipe_Cmd1toCmd2[1],1) )
		{  perror("Eroare: redirectarea iesirii standard in al doilea proces fiu a esuat. Cauza erorii");  exit(4);  }

		execlp("grep","grep","/bin/bash","/etc/passwd",NULL);
		perror("Eroare la execlp() in al doilea proces fiu. Cauza erorii");  exit(5);
	}
	else
	{ // Secțiune de cod executată doar de către părinte (i.e., procesul inițial).
		if(-1 == (pid2=fork()) )
		{  perror("Eroare: nu am putut crea al doilea proces fiu. Cauza erorii");  exit(6);  }

		if(pid2 == 0)
		{ // Secțiune de cod executată doar de către primul fiu al procesului inițial.
			close(pipe_Cmd1toCmd2[1]); // E necesar acest apel close, pentru ca să se termine execuția comenzii cut (prin "citirea" EOF din canalul pipe_Cmd1toCmd2).
	
			if(-1 == dup2(pipe_Cmd1toCmd2[0],0) )
			{  perror("Eroare: redirectarea intrarii standard in primul fiu a esuat. Cauza erorii"); exit(7);  }

			if(-1 == dup2(pipe_Cmd2toCmd3[1],1) )
			{  perror("Eroare: redirectarea iesirii standard in primul fiu a esuat. Cauza erorii");  exit(8);  }
	
			execlp("cut","cut","-d:","-f1,3-5",NULL);
			perror("Eroare la execlp() in primul fiu. Cauza erorii");  exit(9);
		}
		else
		{ // Secțiune de cod executată doar de către părinte (i.e., procesul inițial).
			close(pipe_Cmd2toCmd3[1]); // E necesar acest apel close, pentru ca să se termine execuția comenzii sort (prin "citirea" EOF din canalul pipe_Cmd2toCmd3).
			close(pipe_Cmd1toCmd2[1]); // E necesar acest apel close, pentru ca să se termine execuția comenzii cut (prin "citirea" EOF din canalul pipe_Cmd1toCmd2).

			if(-1 == dup2(pipe_Cmd2toCmd3[0],0) )
			{  perror("Eroare: redirectarea intrarii standard in parinte a esuat. Cauza erorii");  exit(10);  }

			execlp("sort","sort","-t:","-k","2,2","-n",NULL);
			perror("Eroare la execlp() in parinte. Cauza erorii");  exit(11);
		}
	}

	return 0;  // Fluxul de execuție nu va ajunge niciodată aici!
}
