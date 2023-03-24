#include <stdbool.h>

struct ChessPosition{
    int file;
    int rank;
};

struct ChessPosition getChessPosition(int position){
    struct ChessPosition chessPosition;
    chessPosition.file = position / 10;
    chessPosition.rank = position % 10;
    return chessPosition;
}

void printBoard(int board[8][8]){
    printf("[ChessEngine] The board looks like this: \n");
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){\
        if(board[i][j] >= 0)
            printf(" ");

            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

void updateBoard(int board[8][8], int from, int to){
    printf("[ChessEngine] Updating the board... \n");
    struct ChessPosition fromPosition = getChessPosition(from);
    struct ChessPosition toPosition = getChessPosition(to);

    board[toPosition.file][toPosition.rank] = board[fromPosition.file][fromPosition.rank];
    board[fromPosition.file][fromPosition.rank] = 0;
    printf("[ChessEngine] Finished updating the board... \n");

}

int validateMove(int board[8][8], int from, int to){


    /* ----- Game Abandonment ----- */
    if (from == 99 || to == 99)
    {
        return -1;
    }

    printf("[ChessEngine] Validating the move... \n");
    struct ChessPosition fromPosition = getChessPosition(from);
    struct ChessPosition toPosition = getChessPosition(to);

    if (board[fromPosition.file][fromPosition.rank] == 0){
        printf("[ChessEngine] MoveInvalid - The piece the client is trying to move is empty. \n");
        return 0;
    }

    // Trying to move the rook
    if(board[fromPosition.file][fromPosition.rank] == 5){
        if(fromPosition.file == toPosition.file){
            printf("[ChessEngine] The rook is moving horizontally. \n");
            if(fromPosition.rank < toPosition.rank){
                printf("[ChessEngine] The rook is moving to the right. \n");
                for(int i = fromPosition.rank + 1; i < toPosition.rank; i++){
                    if(board[fromPosition.file][i] != 0){
                        printf("[ChessEngine] MoveInvalid - The rook is trying to jump over a piece. \n");
                        return 0;
                    }
                }
                return 1;
            }
            if(fromPosition.rank > toPosition.rank){
                printf("[ChessEngine] The rook is moving to the left. \n");
                for(int i = fromPosition.rank - 1; i > toPosition.rank; i--){
                    if(board[fromPosition.file][i] != 0){
                        printf("[ChessEngine] MoveInvalid - The rook is trying to jump over a piece. \n");
                        return 0;
                    }
                }
                return 1;
            }
        }

        if(fromPosition.rank == toPosition.rank){
            printf("[ChessEngine] The rook is moving vertically. \n");
            if(fromPosition.file < toPosition.file){
                printf("[ChessEngine] The rook is moving up. \n");
                for(int i = fromPosition.file + 1; i < toPosition.file; i++){
                    if(board[i][fromPosition.rank] != 0){
                        printf("[ChessEngine] MoveInvalid - The rook is trying to jump over a piece. \n");
                        return 0;
                    }
                }
                return 1;
            }
            if(fromPosition.file > toPosition.file){
                printf("[ChessEngine] The rook is moving down. \n");
                for(int i = fromPosition.file - 1; i > toPosition.file; i--){
                    if(board[i][fromPosition.rank] != 0){
                        printf("[ChessEngine] MoveInvalid - The rook is trying to jump over a piece. \n");
                        return 0;
                    }
                }
                return 1;
            }
        }
    }

    // Trying to move the knight
    if(board[fromPosition.file][fromPosition.rank] == 3){
        if(abs(fromPosition.file - toPosition.file) == 2 && abs(fromPosition.rank - toPosition.rank) == 1){
            printf("[ChessEngine] The knight is moving in an L shape. \n");
            return 1;
        }
        else if(abs(fromPosition.file - toPosition.file) == 1 && abs(fromPosition.rank - toPosition.rank) == 2){
            printf("[ChessEngine] The knight is moving in an L shape. \n");
            return 1;
        }
        else{
            printf("[ChessEngine] MoveInvalid - The knight is not moving in an L shape. \n");
            return 0;
        }
    }

    // Trying to move the bishop
    if(board[fromPosition.file][fromPosition.rank] == 4){
        if(abs(fromPosition.file - toPosition.file) == abs(fromPosition.rank - toPosition.rank)){
            printf("[ChessEngine] The bishop is moving diagonally. \n");
            if(fromPosition.file < toPosition.file && fromPosition.rank < toPosition.rank){
                printf("[ChessEngine] The bishop is moving up and to the right. \n");
                for(int i = 1; i < abs(fromPosition.file - toPosition.file); i++){
                    if(board[fromPosition.file + i][fromPosition.rank + i] != 0){
                        printf("[ChessEngine] MoveInvalid - The bishop is trying to jump over a piece. \n");
                        return 0;
                    }
                }
                                return 1;
            }
            if(fromPosition.file < toPosition.file && fromPosition.rank > toPosition.rank){
                printf("[ChessEngine] The bishop is moving up and to the left. \n");
                for(int i = 1; i < abs(fromPosition.file - toPosition.file); i++){
                    if(board[fromPosition.file + i][fromPosition.rank - i] != 0){
                        printf("[ChessEngine] MoveInvalid - The bishop is trying to jump over a piece. \n");
                        return 0;
                    }
                }
                                return 1;

            }
            if(fromPosition.file > toPosition.file && fromPosition.rank < toPosition.rank){
                printf("[ChessEngine] The bishop is moving down and to the right. \n");
                for(int i = 1; i < abs(fromPosition.file - toPosition.file); i++){
                    if(board[fromPosition.file - i][fromPosition.rank + i] != 0){
                        printf("[ChessEngine] MoveInvalid - The bishop is trying to jump over a piece. \n");
                        return 0;
                    }
                }
                                return 1;

            }
            if(fromPosition.file > toPosition.file && fromPosition.rank > toPosition.rank){
                printf("[ChessEngine] The bishop is moving down and to the left. \n");
                for(int i = 1; i < abs(fromPosition.file - toPosition.file); i++){
                    if(board[fromPosition.file - i][fromPosition.rank - i] != 0){
                        printf("[ChessEngine] MoveInvalid - The bishop is trying to jump over a piece. \n");
                        return 0;
                    }
                }
                                return 1;

            }
        }
        else{
            printf("[ChessEngine] MoveInvalid - The bishop is not moving diagonally. \n");
            return 0;
        }

    }

    // Trying to move the queen
    if(board[fromPosition.file][fromPosition.rank] == 9){
        if(fromPosition.file == toPosition.file){
            printf("[ChessEngine] The queen is moving horizontally. \n");
            if(fromPosition.rank < toPosition.rank){
                printf("[ChessEngine] The queen is moving to the right. \n");
                for(int i = fromPosition.rank + 1; i < toPosition.rank; i++){
                    if(board[fromPosition.file][i] != 0){
                        printf("[ChessEngine] MoveInvalid - The queen is trying to jump over a piece. \n");
                        return 0;
                    }
                }
                                return 1;

            }
            if(fromPosition.rank > toPosition.rank){
                printf("[ChessEngine] The queen is moving to the left. \n");
                for(int i = fromPosition.rank - 1; i > toPosition.rank; i--){
                    if(board[fromPosition.file][i] != 0){
                        printf("[ChessEngine] MoveInvalid - The queen is trying to jump over a piece. \n");
                        return 0;
                    }
                }
                                return 1;

            }
        }

        if(fromPosition.rank == toPosition.rank){
            printf("[ChessEngine] The queen is moving vertically. \n");
            if(fromPosition.file < toPosition.file){
                printf("[ChessEngine] The queen is moving up. \n");
                for(int i = fromPosition.file + 1; i < toPosition.file; i++){
                    if(board[i][fromPosition.rank] != 0){
                        printf("[ChessEngine] MoveInvalid - The queen is trying to jump over a piece. \n");
                        return 0;
                    }
                }
                                return 1;

            }
            if(fromPosition.file > toPosition.file){
                printf("[ChessEngine] The queen is moving down. \n");
                for(int i = fromPosition.file - 1; i > toPosition.file; i--){
                    if(board[i][fromPosition.rank] != 0){
                        printf("[ChessEngine] MoveInvalid - The queen is trying to jump over a piece. \n");
                        return 0;
                    }
                }
                                return 1;

            }
        }

        if(abs(fromPosition.file - toPosition.file) == abs(fromPosition.rank - toPosition.rank)){
            printf("[ChessEngine] The queen is moving diagonally. \n");
            if(fromPosition.file < toPosition.file && fromPosition.rank < toPosition.rank){
                printf("[ChessEngine] The queen is moving up and to the right. \n");
                for(int i = 1; i < abs(fromPosition.file - toPosition.file); i++){
                    if(board[fromPosition.file + i][fromPosition.rank + i] != 0){
                        printf("[ChessEngine] MoveInvalid - The queen is trying to jump over a piece. \n");
                        return 0;
                    }
                }
                                return 1;

            }
            if(fromPosition.file < toPosition.file && fromPosition.rank > toPosition.rank){
                printf("[ChessEngine] The queen is moving up and to the left. \n");
                for(int i = 1; i < abs(fromPosition.file - toPosition.file); i++){
                    if(board[fromPosition.file + i][fromPosition.rank - i] != 0){
                        printf("[ChessEngine] MoveInvalid - The queen is trying to jump over a piece. \n");
                        return 0;
                    }
                }
                                return 1;

            }
            if(fromPosition.file > toPosition.file && fromPosition.rank < toPosition.rank){
                printf("[ChessEngine] The queen is moving down and to the right. \n");
                for(int i = 1; i < abs(fromPosition.file - toPosition.file); i++){
                    if(board[fromPosition.file - i][fromPosition.rank + i] != 0){
                        printf("[ChessEngine] MoveInvalid - The queen is trying to jump over a piece. \n");
                        return 0;
                    }
                }
                                return 1;

            }
            if(fromPosition.file > toPosition.file && fromPosition.rank > toPosition.rank){
                printf("[ChessEngine] The queen is moving down and to the left. \n");
                for(int i = 1; i < abs(fromPosition.file - toPosition.file); i++){
                    if(board[fromPosition.file - i][fromPosition.rank - i] != 0){
                        printf("[ChessEngine] MoveInvalid - The queen is trying to jump over a piece. \n");
                        return 0;
                    }
                }
                                return 1;

            }
        }

    }

    // Trying to move the king
    if(board[fromPosition.file][fromPosition.rank] == 7){
        if(abs(fromPosition.file - toPosition.file) == 1 && abs(fromPosition.rank - toPosition.rank) == 1){
            printf("[ChessEngine] The king is moving diagonally. \n");
                            return 1;

        }
        else if(abs(fromPosition.file - toPosition.file) == 1 && abs(fromPosition.rank - toPosition.rank) == 0){
            printf("[ChessEngine] The king is moving horizontally. \n");
                            return 1;

        }
        else if(abs(fromPosition.file - toPosition.file) == 0 && abs(fromPosition.rank - toPosition.rank) == 1){
            printf("[ChessEngine] The king is moving vertically. \n");
                            return 1;

        }
        else{
            printf("[ChessEngine] MoveInvalid - The king is not moving diagonally or horizontally. \n");
            return 0;
        }
    }

    printf("[ChessEngine] The move is valid. \n");
    return 1;
}

int whiteKingExists(int board[8][8]){
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(board[i][j] == 7){
                return 1;
            }
        }
    }
    printf("[ChessEngine] GameOver - The white king has been captured. \n");
    return 0;
}

int blkKingExists(int board[8][8]){
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(board[i][j] == -7){
                return 1;
            }
        }
    }
    printf("[ChessEngine] GameOver - The black king has been captured. \n");
    return 0;
}

int checkMate(int board[8][8]){
    return !(whiteKingExists(board) && blkKingExists(board));
}