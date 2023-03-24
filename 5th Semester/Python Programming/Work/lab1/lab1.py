"""
1. Find The greatest common divisor of multiple numbers read from the console.
"""
def pb1():
    a = input('Choose a number')
    b = input('Choose a number again')

    print (computeGCD(a,b));

def computeGCD(x, y):
    if x > y:
        small = y
    else:
        small = x
    for i in range(1, small + 1):
        if((x % i == 0) and (y % i == 0)):
            gcd = i
             
    return gcd

"""
2. Write a script that calculates how many vowels are in a string.
"""
def pb2():
    inString = input("Please type a string")
    print(countvowels(inString))

def countvowels(string):
    num_vowels=0
    for char in string:
        if char in "aeiouAEIOU":
           num_vowels = num_vowels+1
    return num_vowels

"""
3. Write a script that receives two strings and prints the number of occurrences of the first string in the second.
"""
def pb3():
    inString1 = input("first string: ")
    inString2 = input("2nd string: ")
    print(inString2.count(inString1))

"""
4. Write a script that converts a string of characters written in UpperCamelCase into lowercase_with_underscores.
"""
def pb4():
    inString = input('provide a string: ')
    outString = change_case(inString)
    print(outString)

def change_case(str):
    res = [str[0].lower()]
    for c in str[1:]:
        if c in ('ABCDEFGHIJKLMNOPQRSTUVWXYZ'):
            res.append('_')
            res.append(c.lower())
        else:
            res.append(c)
     
    return ''.join(res)

"""
5. Given a square matrix of characters write a script that prints the string obtained by going 
through the matrix in spiral order (as in the example):
"""
def pb5():
    a = [[1, 2, 3, 4],
         [5, 6, 7, 8],
         [9, 10, 11, 12],
         [13, 14, 15, 16]]
 
    for x in spiralOrder(a):
        print(x, end=" ")


def spiralOrder(matrix):
    ans = []
 
    if (len(matrix) == 0):
        return ans
 
    m = len(matrix)
    n = len(matrix[0])
    seen = [[0 for i in range(n)] for j in range(m)]
    dr = [0, 1, 0, -1]
    dc = [1, 0, -1, 0]
    x = 0
    y = 0
    di = 0
 
    # Iterate from 0 to R * C - 1
    for i in range(m * n):
        ans.append(matrix[x][y])
        seen[x][y] = True
        cr = x + dr[di]
        cc = y + dc[di]
 
        if (0 <= cr and cr < m and 0 <= cc and cc < n and not(seen[cr][cc])):
            x = cr
            y = cc
        else:
            di = (di + 1) % 4
            x += dr[di]
            y += dc[di]
    return ans

"""
6. Write a function that validates if a number is a palindrome.
"""
def pb6():
    inString = input("input string: ")
    print(isPalindrome(inString))

def isPalindrome(s):
    return s == s[::-1]

"""
7. Write a function that extract a number from a text (for example if the text is "An apple is 123 USD",
 this function will return 123, or if the text is "abc123abc" the function will extract 123).
  The function will extract only the first number that is found.
"""
def pb7():
    inString = input('write a text containing numbers: ')
    res = [int(i) for i in inString.split() if i.isdigit()]
    print(res[0])

"""
8. Write a function that counts how many bits with value 1 a number has. 
For example for number 24, the binary format is 00011000, meaning 2 bits with value "1"
"""
def pb8():
    c = input("a number")
    
    print("Binary Form: " + bin(int(c)))
    print("There are " + str(bin(int(c)).count("1")) + " bits with value 1")

"""
9. Write a functions that determine the most common letter in a string. 
For example if the string is "an apple is not a tomato", 
then the most common character is "a" (4 times). 
Only letters (A-Z or a-z) are to be considered. 
Casing should not be considered "A" and "a" represent the same character.
"""
def pb9():
    inString = input('A string, please')
    fr = {}
    for i in inString.lower():
        if i in fr:
            fr[i]+=1
        else:
            fr[i] = 1

    res = max(fr, key = fr.get)
    print(res)

"""
10. Write a function that counts how many words exists in a text. 
A text is considered to be form out of words that are separated by only ONE space. 
For example: "I have Python exam" has 4 words.
"""
def pb10():
    inString = input(' one last string i need: ')
    result = len(inString.split(' '))
    print("There are " + str(result) + " words.")



"""
Main Function
"""

if __name__ == '__main__':
    
    # pb1()
    # pb2()
    # pb3()
    # pb4()
    # pb5()
    # pb6()
    # pb7()
    pb8()
    # pb9()
    # pb10()

