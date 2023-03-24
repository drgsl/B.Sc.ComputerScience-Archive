print("How many numbers?")
how_many = int(input())
print("Give me %(numbers)d numbers" % {"numbers": how_many})
n1 = int(input())
cmmdc = n1
for i in range(1, how_many):
    n2 = int(input())
    while n2 != cmmdc:
        if n2 > cmmdc:
            n2 = n2 - cmmdc
        else:
            cmmdc -= n2
print(cmmdc)

