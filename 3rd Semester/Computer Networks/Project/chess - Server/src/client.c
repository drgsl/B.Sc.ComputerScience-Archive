#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>


#include "chessBoard.c"


int main(int argc, char *argv[])
{
    int errno;
    int PORT;                  // portul de conectare la server
    int sd;                    // socket descriptor
    struct sockaddr_in client; // struct used for connecting
    char msg[100];             // send message
    int fromPosition, toPosition;

    /* exista toate argumentele in linia de comanda? */
    if (argc != 3)
    {
        printf("Sintax: %s <server_addr> <PORT>\n", argv[0]);
        return -1;
    }

    /* stabilim PORTul */
    PORT = atoi(argv[2]);

    /* cream socketul */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Eroare la socket().\n");
        return errno;
    }

    /* umplem structura folosita pentru realizarea conexiunii cu serverul */
    /* familia socket-ului */
    client.sin_family = AF_INET;
    /* adresa IP a serverului */
    client.sin_addr.s_addr = inet_addr(argv[1]);
    /* PORTul de conectare */
    client.sin_port = htons(PORT);


    /* Connect to server */
    if (connect(sd, (struct sockaddr *)&client, sizeof(struct sockaddr)) == -1)
    {
        perror("[client] [ERROR] Eroare la connect().\n");
        return errno;
    }
    
    printf("Waiting for the other player(s) to connect... \n");

    if (read(sd, msg, 100) < 0)
    {
        perror("[client] [ERROR] Eroare la read() de la server.\n");
        return errno;
    }
    /* What player are we? */
    printf("[Client]I am Player %s\n", msg);


    /* ---------- Generate Chess Board ---------- */
                int board[8][8] = {
                    {5, 3, 4, 9, 7, 4, 3, 5},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {-5, -3, -4, -9, -7, -4, -3, -5}};
        
    while(1){
        printBoard(board);

        /* ----- Player1 ----- */
        if(strcmp( msg, "1" ) == 0)
        {
            printf("[Client] It's your turn. \n");
                                        /* ----- Player1's Turn ----- */
            printf("[Client] Write the position of the piece you want to move: \n");
            scanf ("%d", &fromPosition);
            printf("[Client] Write the position of the empty square to move the piece to: \n");
            scanf ("%d", &toPosition);

            /* ----- Move Validation ----- */
            int engineResponse = validateMove(board, fromPosition, toPosition);
            if (engineResponse == 0)
            {
                printf("[Client] Invalid move. Try again. \n");
                continue;
            }

            if(engineResponse == 1){
                /* ----- Update Board ----- */
                updateBoard(board, fromPosition, toPosition);
                /* ----- Show new Board ----- */
                printBoard(board);
            }
            
            if (write(sd, &fromPosition, sizeof(fromPosition)) <= 0)
    	    {	
        	perror("[client] [ERROR] client-side write() error.\n");
        	return errno;
    	    }
            if (write(sd, &toPosition, sizeof(toPosition)) <= 0)
    	    {	
        	perror("[client] [ERROR] client-side write() error.\n");
        	return errno;
    	    }
            if(fromPosition == 99 || toPosition == 99){
                printf("[Client] Leaving... \n");
                break;
            }

                                /* ----- Receive the 2nd Player's move ----- */
            if (read(sd, &fromPosition, sizeof(fromPosition)) < 0)
            {
        	perror("[client] [ERROR] client-side read() error.\n");
            return errno;
            }
            if (read(sd, &toPosition, sizeof(toPosition)) < 0)
            {
        	perror("[client] [ERROR] client-side read() error.\n");
            return errno;
            }
            printf("[Client] Received a move from Player2. \n");
            if(fromPosition == 99 || toPosition == 99){
                break;
            }
            /* ----- Update Board ----- */
            updateBoard(board, fromPosition, toPosition);
            /* ----- Show new Board ----- */
            printBoard(board);
        }
        /* ----- Player2 ----- */
        else if (strcmp( msg, "2" ) == 0)
        {
                                /* ----- Receive the 1st Player's move ----- */
            if (read(sd, &fromPosition, sizeof(fromPosition)) < 0)
            {
        	perror("[client] [ERROR] client-side read() error.\n");
            return errno;
            }
            if (read(sd, &toPosition, sizeof(toPosition)) < 0)
            {
        	perror("[client] [ERROR] client-side read() error.\n");
            return errno;
            }
            if(fromPosition == 99 || toPosition == 99){
                break;
            }
            printf("[Client] Received a move from Player1. \n");
            
            if(fromPosition == 99 || toPosition == 99){
                printf("[Client] Leaving... \n");
                break;
            }
            /* ----- Update Board ----- */
            updateBoard(board, fromPosition, toPosition);
            /* ----- Show new Board ----- */
            printBoard(board);


            printf("[Client] It's your turn. \n ");
                                        /* ----- Player1's Turn ----- */
            printf("[Client] Write the position of the piece you want to move: \n");
            scanf ("%d", &fromPosition);
            printf("[Client] Write the position of the empty square to move the piece to: \n");
            scanf ("%d", &toPosition);

            /* ----- Move Validation ----- */
            int engineResponse = validateMove(board, fromPosition, toPosition);
            if (engineResponse == 0)
            {
                printf("[Client] Invalid move. Try again. \n");
                // continue;
            }

            if(engineResponse == 1){
                /* ----- Update Board ----- */
                updateBoard(board, fromPosition, toPosition);
                /* ----- Show new Board ----- */
                printBoard(board);
            }

            if(fromPosition == 99 || toPosition == 99){
                printf("[Client] Leaving... \n");
                break;
            }

            if (write(sd, &fromPosition, sizeof(fromPosition)) <= 0)
    	    {	
        	perror("[client] [ERROR] client-side write() error.\n");
        	return errno;
    	    }
            if (write(sd, &toPosition, sizeof(toPosition)) <= 0)
    	    {	
        	perror("[client] [ERROR] client-side write() error.\n");
        	return errno;
    	    }
        }

    }
    close(sd);
    exit(0);
}

