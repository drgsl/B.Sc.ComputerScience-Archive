import sys
from collections import defaultdict
import os

def read_game(filePath):
    game_values = []
    moves_name = []
    players_name = []
    index = 0
    with open(filePath) as f:
        lines = f.readlines()
        for line in lines:
            if line == '\n':
                continue
            values = list(l[:-1] if l[len(l) - 1] == '\n' else l for l in line.split(" ") if len(l) > 0)
            game_value_line = []
            if values[0][0].isdigit() or values[0][0] == "-" or values[0][0] == "+":
                for value in values:
                    numbers = value.split("/")
                    game_value_line.append((int(numbers[0]), int(numbers[1])))
                game_values.append(game_value_line)
            else:
                players_name.append(values.pop(0))
                moves_name.append(values)

    return players_name, moves_name, game_values


def print_matrix(move_values):
    for line in move_values:
        print(line)


def dominant_strategy(player, move_values):
    if player != 1 and player != 2:
        print("player nr != 1 or 2\n")
        return None
    if player == 1:
        move_values = list(zip(*move_values))
    max_value = -1 * sys.maxsize
    player_move_position = player - 1
    line_best_move = []
    player_maximums = []
    for i in range(len(move_values)):
        max_value = -1 * sys.maxsize
        for j in range(len(move_values[i])):
            move = move_values[i][j]
            if max_value < move[player_move_position]:
                max_value = move[player_move_position]
                line_best_move = [j]
            elif max_value == move[player_move_position]:
                line_best_move.append(j)
        player_maximums.append(line_best_move)
    dictionary = defaultdict(int)
    for line in player_maximums:
        for move in line:
            dictionary[move] += 1
    for move in dictionary:
        number_of_occurences = dictionary[move]
        if number_of_occurences == len(move_values):
            return move
    return None


def nash_equilibrium(move_values):
    move_values_zipped = list(zip(*move_values))
    equilibriums = []
    for i in range(len(move_values)):
        player1_maximum = -1 * sys.maxsize
        player2_maximum = -1 * sys.maxsize
        player1_maximum_position = ()
        player2_maximum_position = ()
        for j in range(len(move_values[i])):
            player1_move_value = move_values_zipped[i][j][0]
            player2_move_value = move_values[i][j][1]
            if player1_maximum < player1_move_value:
                player1_maximum = player1_move_value
                player1_maximum_position = (i, j)
            if player2_maximum < player2_move_value:
                player2_maximum = player2_move_value
                player2_maximum_position = (i, j)
        if player1_maximum_position == player2_maximum_position:
            equilibriums.append(player2_maximum_position)
    return equilibriums


def main():
    players_name, moves_name, move_values = read_game('laba5.txt')
    print(players_name)
    print(moves_name)
    print("\n")
    print_matrix(move_values)
    print("\n")

    print(move_values[0][0])
    player = 1
    best_move = dominant_strategy(player, move_values)
    if best_move is not None:
        print(f"Best move for player {players_name[player - 1]} is : \n", moves_name[player - 1][best_move])
    else:
        print(f"There is no dominant strategy for player {players_name[player - 1]} \n")

    player = 2
    best_move = dominant_strategy(player, move_values)
    if best_move is not None:
        print(f"Best move for player {players_name[player - 1]} is : \n", moves_name[player - 1][best_move])
    else:
        print(f"There is no dominant strategy for player {players_name[player - 1]} \n")

    nash = nash_equilibrium(move_values)
    if len(nash):
        for move in nash:
            print(f"The move {moves_name[0][move[0]]},{moves_name[1][move[1]]} is a nash equilibrium")
    else:
        print("There are no nash equilibriums")

main()