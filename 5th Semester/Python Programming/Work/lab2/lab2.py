"""
1. Write a function to return a list 
of the first n numbers in the Fibonacci string.
"""

from json.encoder import INFINITY


def pb1():
    n = input("insert a number: ")
    print(fib(int(n)))

def fib(n):
    if n == 0:
        return [0]
    elif n == 1:
        return [0, 1]
    else:
        lst = fib(n-1)
        lst.append(lst[-1] + lst[-2])
        return lst


"""
2. Write a function that receives a list of numbers
 and returns a list of the prime numbers found in it.
"""

def pb2():
    input_string = input('Enter elements of a list separated by space: ')
    user_list = input_string.split()
    print('list: ', user_list)

    print(getPrimeList(user_list))

def getPrimeList(list):
    primeList = []
    for i in range(len(list)):
        if(isPrime(int(list[i]))):
            primeList.append(int(list[i]))
    return primeList

def isPrime(n):
  for i in range(2,n):
    if (n%i) == 0:
      return False
  return True

"""
3. Write a function that receives as parameters two lists a and b
and returns: (a intersected with b,
a reunited with b, 
a - b, b - a)
"""

def pb3():
    a = [15, 9, 10, 56, 23, 78, 5, 4, 9]
    b = [9, 4, 5, 36, 47, 26, 10, 45, 87]

    a = set(a)
    b = set(b)

    print("a =", a)
    print("b =", b)

    print("a n b = ", a.intersection(b))
    
    print("a u b = ", a.union(b))

    print("a - b = ", a.difference(b))

    print("b - a = ", b.difference(a))

"""
4. Write a function that receives as a parameters
 a list of musical notes (strings), 
 a list of moves (integers) and a start position (integer).
The function will return the song composed by going though the musical notes 
beginning with the start position and following the moves given as parameter.
	Example : compose(["do", "re", "mi", "fa", "sol"], [1, -3, 4, 2], 2) 
    will return ["mi", "fa", "do", "sol", "re"] 
"""
def pb4():
    musicalNotes = ["do", "re", "mi", "fa", "sol"]
    moves = [1, -3, 4, 2]
    startingIdx = 2
    compose(musicalNotes, moves, startingIdx)

def compose(lst, steps, start):
    idx = start
    i=0
    print(lst[idx])
    for start in range(len(steps)):
        idx += steps[i]
        i+=1      
        if(idx > len(lst)):
            idx = idx - len(lst)
        print(lst[idx])  


"""
5. Write a function that receives as parameter
 a matrix and will return the matrix obtained
  by replacing all the elements under the main diagonal with 0 (zero).
"""
def pb5():
    arr=[[1,2,3],[4,5,6],[7,8,9]]
    
    print("initial matrix: ")
    for i in range(len(arr[0])):
        for j in range(len(arr)):
            print(arr[i][j], end = ' ')
        print()

    for i in range(len(arr[0])):
        for j in range(len(arr)):
            if(i>j):
                arr[i][j] = 0
    
    print("modified matrix: ")
    for i in range(len(arr[0])):
        for j in range(len(arr)):
            print(arr[i][j], end = ' ')
        print()

"""
6. Write a function that receives as a parameter
 a variable number of lists and a whole number x. 
 Return a list containing the items that appear 
 exactly x times in the incoming lists. 

Example: 
For the [1,2,3], [2,3,4],[4,5,6], [4,1, "test"] 
and x = 2 lists 
[1,2,3 ] # 
1 is in list 1 and 4, 
2 is in list 1 and 2, 
3 is in lists 1 and 2.
"""

def pb6():
    lst1 = [1,2,3]
    lst2 = [2,3,4]
    lst3 = [4,5,6]
    lst4 = [4,1]
    x = 2
    itemFrequency(x, lst1, lst2, lst3, lst4)

def itemFrequency(freq, *args):
    freqArr = [0] * 100
    print(freq, args)
    # print(len(args[0]))
    for i in range(len(args)):
        for j in range(len(args[i])):
            freqArr[int(args[i][j])] += 1

    for i in range(len(freqArr)):
        if(freqArr[i] == freq):
            print(i)


"""
7. Write a function that receives as parameter 
a list of numbers (integers) and will return a tuple with 2 elements.
 The first element of the tuple will be the number of palindrome numbers
  found in the list and the second element will be the greatest palindrome number.
"""

def pb7():
    lst = [123321, 456654, 123, 1001, 223]
    palindromeCount = 0
    biggestPalindrome = -INFINITY
    for i in range(len(lst)):
        if(isPalindrome(lst[i])):
            palindromeCount += 1
            if(lst[i] > biggestPalindrome):
                biggestPalindrome = lst[i]

    answrLst = []
    answrLst.append(palindromeCount)
    answrLst.append(biggestPalindrome)

    print(tuple(answrLst))

def isPalindrome(input):
    return str(input) == str(input)[::-1]


"""
 8. Write a function that receives a number x,
  default value equal to 1, 
  a list of strings, and a boolean flag set to True. 
  For each string, generate a list containing the characters 
  that have the ASCII code divisible by x if the flag is set to True, 
  otherwise it should contain characters that have the ASCII code not divisible by x.

   Example: x = 2, ["test", "hello", "lab002"], 
   flag = False will return (["e", "s"], 
   ["e" . Note: The function must return list of lists.
"""

def pb8():
    x = 2
    inStrings = ["test", "hello", "lab002"]
    flag = False

    print(asciiDivisibleBy(x, inStrings, flag))


def asciiDivisibleBy(x = 1, inStrings = [], flag = True):
    outerList = []
    for string in inStrings:
        innerList = []
        for char in string:
            if(flag):
                if(ord(char) % x == 0):
                    innerList.append(char)
                    # innerList.append(ord(char))
            else:
                if(ord(char) % x != 0):
                    innerList.append(char)
                    # innerList.append(ord(char))
        outerList.append(innerList)
    return outerList

"""
9. Write a function that receives as paramer 
a matrix which represents the heights of the spectators 
in a stadium and will return a list of tuples (line, column) 
each one representing a seat of a spectator which can't see the game. 
A spectator can't see the game if there is at least one taller spectator 
standing in front of him. All the seats are occupied. All the seats are at the same level.
 Row and column indexing starts from 0, beginning with the closest row from the field.
"""

def pb9():
    heights = [[1, 2, 3, 2, 1, 1],
               [2, 4, 4, 3, 7, 2],
               [5, 5, 2, 5, 6, 4],
               [6, 6, 7, 6, 7, 5]]
    
    print(getShortPPL(heights))

def getShortPPL(matrix):
    solution = []
    for j in range(len(matrix[0])):
        max = -INFINITY
        for i in range(len(matrix)):
            if(matrix[i][j] > max):
                max = matrix[i][j]
            else:
                solution.append(tuple([i, j]))
                # print(matrix[i][j], " ", i, " ", j)

    return solution
"""
10. Write a function that receives a variable number of lists 
and returns a list of tuples as follows: the first tuple contains 
the first items in the lists, the second element contains the items 
on the position 2 in the lists, etc. 

Ex: for lists [1,2,3], [5,6,7], ["a", "b", "c"] 
return: [(1, 5, "a ") ,(2, 6, "b"), (3,7, "c")]. 
Note: If input lists do not have the same number of items,
missing items will be replaced with None to be able to generate 
max ([len(x) for x in input_lists]) tuples.
"""

def pb10():
    lst1 = [1,2,3, 8]
    lst2 = [5,6,7]
    lst3 = ['a', 'b', 'c']

    result = zip(lst1, lst2, lst3)
    print(list(result))

"""
11. Write a function that will order a list of string 
tuples based on the 3rd character of the 2nd element in the tuple.

 Example: ('abc', 'bcd'), ('abc', 'zza')] ==> [('abc', 'zza'), ('abc', 'bcd')]
"""

"""
12. Write a function that will receive a list of words  as parameter 
and will return a list of lists of words, 
grouped by rhyme. 
Two words rhyme if both of them end with the same 2 letters.

Example:
group_by_rhyme(['ana', 'banana', 'carte', 'arme', 'parte']) 
will return [['ana', 'banana'], ['carte', 'parte'], ['arme']] 
"""

if __name__ == '__main__':
    
    # pb1()
    # pb2()
    # pb3()
    # pb4()
    # pb5()
    # pb6()
    # pb7()
    # pb8()
    # pb9()
    pb10()