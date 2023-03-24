import re
import struct

# ==== 1 ====
a = {i ^ j: i ** j for i in range(1, 4) for j in range(1, 4)}
l = sorted([i[1] for i in a.items()])
print(l)

# ==== 2 ====
a = [5, 4, 3, 2, 1]
a[1:-3] = [1, 2, 3]
print(a)

# ==== 3 ====
print([x + y for x in range(1, 5) for y in range(1, 5) if x % y == 0])

# ==== 4 ====
y = [1, *([0] * 3), 2]
print(y)

# ==== 5 ====
s = ""
for i in struct.pack("@bhbib", 3, 1, 2, 4, 5)[:10]:
    s += hex(i) + " "
print(s)

# ==== 6 ====
l = list(sorted([1, 25, 73, 17], key=lambda x: x % 5))
print(l)

# ==== 7 ====
x = 100
while x > 0:
    x = x // 2
    if x == 6: continue;
    print(x)
else:
    print("0")

# ==== 8 ====
print(len(re.split("\s\w{4,6}\s", " We have a python reexamination today at FII ")[2]))

# ==== 9 ====
print("PythonExaminationToday"[2:-2:4])

# ==== 10 ====
print((len((str("123") * 3)[1:-1])) / 3)
