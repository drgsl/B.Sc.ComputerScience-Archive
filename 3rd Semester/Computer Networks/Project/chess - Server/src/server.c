#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>


#include "chessBoard.c"

struct clients
{
    int connectedClients;
    int client;
    int client2;
} clients;


void recover_kids()
{ //recovers zombie processes
    while (waitpid(-1, NULL, WNOHANG) != 0)
        ;
}

int main(){
    /* ---------- Server Initialization ---------- */

    int errno;                 // will be used for display err numbers
    const int PORT = 5005;     // const because the port doesnt change during runtime
    struct sockaddr_in server; // struct used by server
    struct sockaddr_in from;
    char msg[100];          // message received from the client will be stored in this variable
    char msgrasp[100] = ""; //mesaj de raspuns pentru client
    int sd;                 // socket descriptor
    int fromPosition, toPosition;

    /* socket creation */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("[server]Eroare la socket().\n");
        return errno;
    }

    /* pregatirea structurilor de date */
    bzero(&server, sizeof(server));
    bzero(&from, sizeof(from));

    /* umplem structura folosita de server */
    /* stabilirea familiei de socket-uri */
    server.sin_family = AF_INET;
    /* acceptam orice adresa */
    //host to network long
    server.sin_addr.s_addr = htonl(INADDR_ANY); //se accepta requesturi de la orice interfata
    /* utilizam un port utilizator */
    //host to network short
    server.sin_port = htons(PORT);

    /* atasam socketul */
    if (bind(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
    {
        perror("[server]Eroare la bind().\n");
        return errno;
    }

    /* punem serverul sa asculte daca vin clienti sa se conecteze */
    if (listen(sd, 5) == -1)
    {
        perror("[server]Eroare la listen().\n");
        return errno;
    }

    if (signal(SIGCHLD, recover_kids) == SIG_ERR)
    {
        perror("[server]Eroare la atasarea semnalului.\n");
        return errno;
    }
    
    /* ---------- Client Connection ---------- */
    clients.connectedClients = 0;

    while(1)
    {
        printf("[Server] Waiting for connections \n");
        int length = sizeof(from);
        printf("[Server] Waiting for clients at %d port \n", PORT);
        fflush(stdout);
        /* acceptam un client (stare blocanta pana la realizarea conexiunii) */
        if (clients.connectedClients == 0)
        {
            clients.client = accept(sd, (struct sockaddr *)&from, &length);
            if (clients.client < 0)
            {
                perror("[server] [ERROR] Eroare la accept().\n");
                continue;
            }

            printf("[Server] Client Connected. \n");
            clients.connectedClients++;
            printf("Client count: %d /2 \n", clients.connectedClients);
        }
        else if (clients.connectedClients == 1)
        {
            clients.client2 = accept(sd, (struct sockaddr *)&from, &length);
            if (clients.client2 < 0)
            {
                perror("[server] [ERROR] Eroare la accept().\n");
                continue;
            }

            printf("[Server] Client Connected. \n");
            clients.connectedClients++;
            printf("Client count: %d/2 \n", clients.connectedClients);
        }
        if (clients.connectedClients == 2)
        {
            clients.connectedClients = 0;
            printf("[Server] Server will fork in order to supervise the game. \n");
            

            //send the order number to player1 
            strcat(msgrasp, "1");
            if (write(clients.client, msgrasp, 100) <= 0)
            {
                perror("[server] [ERROR] write() to client1 \n");
                continue; /* continuam sa ascultam */
            }
            memset(msgrasp, 0, strlen(msgrasp));

            //send the order number to player2
            memset(msgrasp, 0, strlen(msgrasp));
            strcat(msgrasp, "2");
            if (write(clients.client2, msgrasp, 100) <= 0)
            {
                perror("[server]Eroare la write() catre clientul 2 inainte de fork.\n");
                continue; /* continuam sa ascultam */
            }
            memset(msgrasp, 0, strlen(msgrasp));


                                /* ---------- Clients connected ---------- */
            int f = fork();
            if (f == -1) // Err
            {
                perror("[server]Eroare la crearea fork-ului().\n");
                close(clients.client); /* inchidem conexiunea cu clientul */
                close(clients.client2);
                continue; /* continuam sa ascultam */
            }
            else if (f == 0) // Fork Child
            {
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

                                    /* ---------- Start Game ---------- */
                printf("[Server] Starting Game... \n");
                while (1)
                {
                                        /* ---------- Player1 Turn ---------- */

                    printf("[Server] Player1's Turn...\n");
                    /* read initial square */
                    if (read(clients.client, &fromPosition, sizeof(fromPosition)) <= 0)
                    {
                        perror("[server] [ERROR] client-side read() error. \n");
                        continue; /* continue reading */
                    }
                    /* read new square */
                    if (read(clients.client, &toPosition, sizeof(toPosition)) <= 0)
                    {
                        perror("[server] [ERROR] client-side read() error. \n");
                        continue; /* continue reading */
                    }
                    printf("[Server] Received a move from Player1. \n");

                    /* ----- Move Validation ----- */
                    if(validateMove(board, fromPosition, toPosition) == 1){
                        /* ----- Update Board ----- */
                        updateBoard(board, fromPosition, toPosition);
                        /* ----- Show new Board ----- */
                        printBoard(board);
                    }
                    else if (validateMove(board, fromPosition, toPosition) == 0)
                    {
                        printf("[Server] Board has not been updated because of an invalid move. \n");
                    }
                    else if (validateMove(board, fromPosition, toPosition) == -1){
                        printf("[Server] One of the players left the game. \n");
                        printf("[Server] Exiting... \n");
                        close(clients.client);
                        close(clients.client2);
                        exit(0);
                        // break;
                    }

                    /* ----- Send move to Player2 ----- */
                    printf("[Server] Sync-ing the 2nd player... \n");
                    /* send initial square */
                    if (write(clients.client2, &fromPosition, sizeof(fromPosition)) <= 0)
                    {
                        perror("[server] [ERROR] client-side write() error. \n");
                        continue; /* continue reading */
                    }
                    /* send new square */
                    if (write(clients.client2, &toPosition, sizeof(toPosition)) <= 0)
                    {
                        perror("[server] [ERROR] client-side write() error. \n");
                        continue; /* continue reading */
                    }


                    if(checkMate(board) == 1){
                        printf("[Server] Game has ended. \n");
                        printf("[Server] Player1 has won. \n");
                        break;
                    }


                                        /* ---------- Player2 Turn ---------- */

                    printf("[Server] Player2's Turn...\n");
                    /* read initial square */
                    if (read(clients.client2, &fromPosition, sizeof(fromPosition)) <= 0)
                    {
                        perror("[server] [ERROR] client-side read() error. \n");
                        continue; /* continue reading */
                    }
                    /* read new square */
                    if (read(clients.client2, &toPosition, sizeof(toPosition)) <= 0)
                    {
                        perror("[server] [ERROR] client-side read() error. \n");
                        continue; /* continue reading */
                    }
                    printf("[Server] Received a move from Player2. \n");

                    /* ----- Move Validation ----- */
                    if(validateMove(board, fromPosition, toPosition) == 1){
                        /* ----- Update Board ----- */
                        updateBoard(board, fromPosition, toPosition);
                        /* ----- Show new Board ----- */
                        printBoard(board);
                    }
                    else if (validateMove(board, fromPosition, toPosition) == 0)
                    {
                        printf("[Server] Board has not been updated because of an invalid move. \n");
                    }
                    else if (validateMove(board, fromPosition, toPosition) == -1){
                        printf("[Server] One of the players left the game. \n");
                        printf("[Server] Exiting... \n");
                        close(clients.client);
                        close(clients.client2);
                        // exit(0);
                        break;
                    }

                    /* ----- Send move to Player1 ----- */
                    printf("[Server] Sync-ing the 1st player... \n");
                    /* send initial square */
                    if (write(clients.client, &fromPosition, sizeof(fromPosition)) <= 0)
                    {
                        perror("[server] [ERROR] client-side write() error. \n");
                        continue; /* continue reading */
                    }
                    if (write(clients.client, &toPosition, sizeof(toPosition)) <= 0)
                    {
                        perror("[server] [ERROR] client-side write() error. \n");
                        continue; /* continue reading */
                    }


                    if(checkMate(board) == 1){
                        printf("[Server] Game has ended. \n");
                        printf("[Server] Player2 has won. \n");
                        break;
                    }
                }
                exit(0);
            } /* Fork Child */
            else
            {
                clients.connectedClients = 0;
            }
        } /* if clients == 2 */
    } /* while */
    close(sd);
    exit(0);
} /* main */


