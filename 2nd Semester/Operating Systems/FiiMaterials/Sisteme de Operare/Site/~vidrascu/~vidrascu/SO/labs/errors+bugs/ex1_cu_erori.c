/*
*  Program: rezolvarea din [Exec command #1: ls], puțin modificată
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	int cod_term;
	char* dirname;

	dirname = (argc < 2) ? "." : argv[1]

	/* Creez un proces fiu, care va rula comanda ls prin exec. */
	if( pid=fork() == -1 )
	{
		perror("Eroare la fork"); exit(1);
	}

	if (pid == 0)
	{
		/* În procesul fiu apelez exec pentru a executa comanda dorită. */
		execlp("ls","-l","-A",dirname);
 
		perror("Eroare la exec");
		exit(10); // Aici folosesc un numar mai mare, e.g. 10, și nu 1,2,... căci aceste valori mici ar putea fi returnate și de către comanda ls !
	}

	/* (Doar în procesul părinte) Acum cercetez cum s-a terminat procesul fiu. */
	wait(&cod_term);
	if(cod_term >> 8 == 10)
		printf("Comanda ls nu a putut fi executata... (apelul exec a esuat).\n");
	else
	{
		printf("Comanda ls a fost executata...");
		if(cod_term == 0)
			printf(" cu succes!\n");
		else
			if( WIFEXITED(cod_term) )
				printf(", dar a esuat, terminandu-se cu codul de terminare: %d.\n", WEXITSTATUS(cod_term) );
			else
				printf(", dar a fost terminata fortat de catre semnalul: %d.\n", WTERMSIG(cod_term) );
	}
	return 0;
}
