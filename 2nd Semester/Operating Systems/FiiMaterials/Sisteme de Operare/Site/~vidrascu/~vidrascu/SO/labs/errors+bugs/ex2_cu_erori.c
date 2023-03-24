/*
  Filename: p2.c

  Programul de mai jos ar trebui să ofere următoarea funcționalitate:

    Procesul principal creează un fiu.
    Procesul fiu se reacoperă cu comanda stat, executată cu opțiunea de a afisa tipul fișierului pentru fișierul "p2.c"
    și cu redirectarea output-ului către fișierul "fisier.txt".
    În acest timp, procesul părinte așteaptă să se termine fiul, apoi citește din "fisier.txt" primele 10 caractere și le afișează.

*/  

#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	int pid1;

	pid1 = fork();

	if(pid1 == -1)
	{
		perror(failed to create child process);
		return -1;
	}

	if(pid1==0)
	{
		int fd = open("fisier.txt", O_WRONLY|O_CREAT, 0600);
		dup2(fd, 1);
		close(fd);
		execlp("stat","stat","p2.c","--printf","%F" ,NULL);
		return 0;
	}
	else
	{
		wait(NULL);
		int fd = open("fisier.txt", O_RDONLY);
		char a;
		read(fd, &a, siezof(char));
		close(fd);
		print("Primele 10 caractere din fisier.txt sunt: %c\n", a);
	}

	return 0;
}
