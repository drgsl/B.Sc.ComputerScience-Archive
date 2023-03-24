import sys

if len(sys.argv) < 2:
    print("there are no parameters given")
    exit()
uppercase_string = sys.argv[1]

new_string = ""
for i in range(len(uppercase_string)):
    if uppercase_string[i].isupper():
        if i == 0:
            new_string += uppercase_string[i].lower()
        else:
            new_string += "_" + uppercase_string[i].lower()
    else:
        new_string += uppercase_string[i]

print(new_string)
