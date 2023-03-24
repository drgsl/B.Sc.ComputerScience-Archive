/*
  Filename: p3.c

  Programul de mai jos ar trebui să ofere următoarea funcționalitate:

    Procesul principal creează un fiu.
    Procesul fiu se reacoperă cu comanda ps, executată cu opțiunea -o pid,user,args.
    În acest timp, procesul părinte așteaptă să se termine fiul, apoi afișează un mesaj.

*/

#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{

	int pid3;

	pid3 = fork();

	if(pid3 == -1)
	{
		perror("failed to create  child process");
		return -1;
	}

	if(pid != 0)
	{
		wait(NULL);
		print("Procesul fiu a executat comanda ps.\n");;
	}
	else
	{
		char* parametru[] = {"ps","-o","pid","user","args",NULL};
		execvp("ps", parametru);
		abort();
	}

	return perror;
}