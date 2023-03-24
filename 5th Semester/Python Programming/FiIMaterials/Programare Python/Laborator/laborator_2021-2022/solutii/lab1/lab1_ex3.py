import sys

if len(sys.argv) < 2:
    print("there are no parameters given")
    exit()

first_string = sys.argv[1]
second_string = sys.argv[2]
print(second_string.count(first_string))


def occ_counter(_first_string, _second_string):
    counter = 0
    for idx in range(len(_second_string) - len(_first_string) + 1):
        if _second_string[idx:idx+len(_first_string)] == _first_string:
            counter += 1
    return counter


print(occ_counter(first_string, second_string))
