#include <stdio.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <string.h>
    #include <fcntl.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>

    

    int main()
    {
        char cmd[256],msg[256];
        int size, fd1,fd2;

        printf("Login\n");
        printf("Get-logged-users\n");
        printf("Get-proc-info\n");
        printf("Logout\n");
        printf("Quit\n");
        printf("\n");
        printf("Alegeti o comanda\n");

        mknod("fifo2", S_IFIFO | 0666, 0);
        fd1 = open("fifo1", O_WRONLY);
        fd2= open("fifo2", O_RDONLY);
        
        int lungime;
        while (gets(cmd), !feof(stdin)) {
            if ((write(fd1, cmd, strlen(cmd))) == -1)
                perror("Problema la scriere in FIFO1!");
            else if (strcmp(cmd,"quit")==0) exit(1);
            else{
                
                
                if ((size = read(fd2, msg, 256)) == -1)
                    perror("Eroare la citirea din FIFO2!");
                
                else 
                { 
                    lungime=strlen(msg);
                    msg[size]='\0';
                    printf("%d %s\n",lungime,msg); 
                    
                }
            } 

        }
    }