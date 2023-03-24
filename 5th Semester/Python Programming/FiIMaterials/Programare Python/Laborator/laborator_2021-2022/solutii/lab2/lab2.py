def function1(n):

    if not n:
        return [0]
    if n == 1:
        return [0, 1]
    list_of_fib = [0, 1]
    for i in range(2, n):
        list_of_fib.append(list_of_fib[i-1] + list_of_fib[i-2])

    return list_of_fib


def function1_get_n_elem(n):

    from math import sqrt
    return ((1 + sqrt(5)) ** n - (1 - sqrt(5)) ** n) / (2 ** n * sqrt(5))


def function2(list_of_nr):
    return [x for x in list_of_nr if len([d for d in range(2, (x//2 + 1)) if x % d == 0]) == 0]


def function3(list1, list2):

    list_intersect = []
    list_first_minus_second = []
    list_second_minus_first = []
    list_reunion = []
    for item1 in list1:
            if item1 in list2 and item1 not in list_intersect:
                list_intersect.append(item1)
    for item1 in list1:
        if item1 not in list2:
            list_first_minus_second.append(item1)
    for item2 in list2:
        if item2 not in list1:
            list_second_minus_first.append(item2)
    for item1 in list1:
        if item1 not in list_reunion:
            list_reunion.append(item1)
    for item2 in list2:
        if item2 not in list_reunion:
            list_reunion.append(item2)

    return list_intersect, list_reunion, list_first_minus_second, list_second_minus_first


def function4(musical_notes, list_of_moves, start_position):

    new_list = [musical_notes[start_position]]

    for move in list_of_moves:
        if move < 0:
            start_position -= (move + 1)
            start_position = start_position % len(musical_notes)
        else:
            start_position = start_position + move
            start_position = start_position % len(musical_notes)
        new_list.append(musical_notes[start_position])
    return new_list


def function5(matrix):

    for l in range(len(matrix)):
        for c in range(l):
            matrix[l][c] = 0
    return matrix


def function6(*lists, count):

    all_lists = []
    return_list = []
    for lst in lists:
        all_lists+=lst
    for item in all_lists:
        if all_lists.count(item) == count and item not in return_list:
            return_list.append(item)

    return return_list


def function7(lst_of_numbers):

    list_of_palindroms = [el for el in lst_of_numbers if str(el) == str(el)[::-1]]
    return tuple((len(list_of_palindroms), max(list_of_palindroms)))


def function8(*list_of_strings, x=1, flag=True):

    return_list = []
    for string in list_of_strings:
        if flag:
            return_list.append([ch for ch in string if ord(ch) % x == 0])
        else:
            return_list.append([ch for ch in string if ord(ch) % x != 0])

    return return_list


def function9(matrix):

    list_of_positions = []
    matrix_transpose = list(zip(*matrix))

    for c in range(len(matrix_transpose)):
        for l in range(1, len(matrix_transpose[0])):
            if matrix_transpose[c][l] <= max(matrix_transpose[c][:l]):
                list_of_positions.append(tuple((l, c)))
    return list_of_positions


def function10(*lists):

    max_nr_of_elements = max([len(x) for x in lists])
    new_lists = [l+[None for i in range(len(l), max_nr_of_elements)] for l in lists]

    return list(zip(*new_lists))


def function11(lists):

    if len([l for l in lists if len(l) < 2]) != 0:
        print("Not valid list")
        return
    return sorted(lists, key=lambda i: i[1][2])


if __name__ == '__main__':
    print(function4(["do", "re", "mi", "fa", "sol"], [1, -3, 4, 2], 2))
    print(function5([[1, 2, 3], [4, 5, 6], [7, 8, 9]]))
    print(function7([12321, 23432, 123, 4567654]))
    print(function9([[1, 2, 3, 2, 1, 1], [2, 4, 4, 3, 7, 2], [5, 5, 2, 5, 6, 4], [6, 6, 7, 6, 7, 5]]))
