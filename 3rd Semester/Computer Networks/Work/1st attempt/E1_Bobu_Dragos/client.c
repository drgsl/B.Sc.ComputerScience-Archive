#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <errno.h>
#include <fcntl.h>


int main(){
    char usernameInput[50] = "";
    scanf("%s", usernameInput);
    printf("username input: %s", usernameInput);

    int fd = open("pipe", O_RDONLY);
    char sentMessage[100];
    strcpy(sentMessage, usernameInput);
    printf("sent message: %s", sentMessage);
    write(fd, &sentMessage, sizeof(sentMessage));
}