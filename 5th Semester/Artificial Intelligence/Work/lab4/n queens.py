"""
Board/Matrix Functions
"""
def printMatrix(matrix):
    for i in range(len(matrix)):
        for j in range (len(matrix[0])):
            print(matrix[i][j], end = ' ')
        print()

def generateMatrix(w, h):
    return [['.' for x in range(w)] for y in range(h)]
    
def generateChessBoard(size):
    return generateMatrix(size, size)


"""
Square Writing
"""
def block(board, idx, jdx):
    board[idx][jdx] = '/'
  
def isBlocked(board, idx, jdx):
    return board[idx][jdx] == '/'

def queen(board, idx, jdx):
    if board[idx][jdx] != '/':
        board[idx][jdx] = 'Q'

def clear(board, idx, jdx):
    board[idx][jdx] = '.'
"""
Queen Functions
"""
def isSafe(board, row, col):
  
    # Check this row on left side
    for i in range(col):
        if board[row][i] == 'Q':
            return False
  
    for i in range(row):
        if board[i][col] == 'Q':
            return False

    # Check upper diagonal on left side
    for i, j in zip(range(row, -1, -1), 
                    range(col, -1, -1)):
        if board[i][j] == 'Q':
            return False
  
    # Check lower diagonal on left side
    for i, j in zip(range(row, len(board), 1), 
                    range(col, -1, -1)):
        if board[i][j] == 'Q':
            return False
  
    return True

def checkForValidSquares(board):
    for i in range(len(board)):
        for j in range(len(board[0])):
            if(isSafe(board, i, j)):
                return True
    return False


def getLeastSafeCol(board):
    colsSafety = []
    for i in range(len(board)):
        for j in range(len(board[0])):
            safeSquares = 0
            if(isSafe(board, i, j)):
                safeSquares += 1
        colsSafety.append(safeSquares)

    return min(colsSafety)

"""
Solving Functions
"""
def check(board, col):
      
    # base case: If all queens are placed
    # then return true
    if col >= len(board):
        return True
  
    # Consider this column and try placing
    # this queen in all rows one by one
    for i in range(len(board)):
  
        if isSafe(board, i, col) and not isBlocked(board, i, col):
              

            # Place this queen in board[i][col]
            # board[i][col] = 1
            queen(board, i, col)

            #Forward checking
            if(checkForValidSquares(board) == False):
                return False


            nextCol = getLeastSafeCol(board) 
            # recur to place rest of the queens
            if check(board, col + 1) == True:
                return True
  
            # If placing queen in board[i][col
            # doesn't lead to a solution, then
            # remove queen from board[i][col]
            # board[i][col] = 0
            clear(board, i, col)

  
    # if the queen can not be placed in any row in
    # this column col then return false
    return False

def solve(board):
  
    if check(board, 0) == False:
        print ("Solution does not exist")
        return False
  
    return True


"""
Obtain Problem Specifics
"""
def getBoardFromKeyboard():
    print("Enter the ChessBoard size (Also the number of queens to be placed)")
    print("n = ", end = "")
    n = int(input())

    board = generateChessBoard(n)

    blockedSquares = []

    print("Enter the indeces of the blocked squares")
    print("example:")
    print("0 0")
    print("0 1")
    print("1 0")
    
    inp = input()

    while inp:
        splitted = inp.split(' ')
        print(splitted)
        block(board, int(splitted[0]), int(splitted[1]))

        inp = input()
    return board

def getBoardHardCoded():
    n = 4
    board = generateChessBoard(n)

    block(board, 0,0)
    block(board, 1,1)
    block(board, 3,2)

    return board

if __name__ == "__main__":
    

    # board = getBoardFromKeyboard()
    board = getBoardHardCoded()

    printMatrix(board)
    print()

    solve(board)

    printMatrix(board)
    # solve(board, n)