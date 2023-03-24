#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <errno.h>
#include <fcntl.h>


int main(int argc, char* argv[]){
    int fd;
    char receivedMessage[100];
    fd = open("pipe", O_RDONLY);

    read(fd, &receivedMessage, sizeof(receivedMessage));
      int lookForUsername = 1;
        while(lookForUsername)
        {
        char thisPassword[100];
        FILE *usersFile = fopen("users.txt", "r"); 
        fgets(thisPassword, strlen(receivedMessage)+1, usersFile);
        printf("this password: %s", thisPassword);

        printf("comparing <%s> with <%s>", receivedMessage, thisPassword);
        if(!strcmp(receivedMessage,thisPassword))
        {
            printf("v ati logat cu user ul %s", receivedMessage);
            lookForUsername = 0;
        }
        else{
            printf("user invalid");
        }

        if(usersFile == EOF){
        printf("closing file : %d", fd);
        close(fd);
        exit(1);
        }
    close(fd);
    printf("user ul s a logat cu %s", receivedMessage);

    return 0;
}