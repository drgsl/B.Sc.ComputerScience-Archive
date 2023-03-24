import sys

if len(sys.argv) < 2:
    print("there are no parameters given")
    exit()
string = sys.argv[1]
vowels = "aeiou"
string = string.lower()
count = 0
for v in vowels:
    c_v = string.count(v)
    if c_v:
        count += c_v
print(count)
# print(len([ch for ch in string if ch.lower() in "aeiou"]))
