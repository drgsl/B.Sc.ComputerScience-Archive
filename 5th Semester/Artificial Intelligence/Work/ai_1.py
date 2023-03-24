# Laborator 2 & 3
import sys
from collections import deque
sys.setrecursionlimit(5000)

# O stare o sa fie de forma [a,b]
# a -> cantitatea de apa din primul borcan
# b -> cantitatea de apa din al doilea borcan
def initState(m,n,k):
    return [0,0]

# Verificam daca in unul din cele doua borcane am ramas cu k litri
def isFinale(stare,k):
    if stare[0] == k or stare[1] == k:
        return True
    else:
        return False

# Verificam daca borcanul x e gol
def isEmpty(x):
    if x == 0:
        return True
    else:
        return False

# Verificam daca borcanul x e plin
def isFull(m,a):
   if a == m:
       return True
   else:
       return False

#Verificam daca putem muta din borcanul x
def canMove(stare, m, n, x):
    if x == 1:
        if stare[0]==0 or stare[1]==n:
            return False
        else:
            return True
    if x == 2:
        if stare[0]==m or stare[1]==0:
            return False
        else:
            return True

# Golim un borcan
def empty(stare, x):
    if isEmpty(stare[x]) == True:
        return stare
    else:
        stare[x] = 0
        return stare

#Umplem un borcan
def fill(stare,m,n,x):
    if x == 0:
        if isFull(m,stare[0])==True:
            return stare
        else:
            stare[0]=m
            return stare
    if x == 1:
        if isFull(n,stare[1])==True:
            return stare
        else:
            stare[1]=n
            return stare

#Mutam dintr-un borcan in altul
def move(stare,m,n,x):
    if canMove(stare,m,n,x) == True:
        s = stare[0]+stare[1]
        a=stare[0]
        b=stare[1]
        if x==0:
            if s<=n:
                stare[1]=s
                stare[0]=0
            else:
                stare[1]=n
                stare[0]=stare[0]-n+stare[1]
        if x==1:
            if s<=m:
                stare[0]=s
                stare[1]=0
            else:
                stare[0]=m
                stare[1]=stare[1]-m+stare[0]
        return stare

def gcd(m,n):
    if n == 0:
        return m
    return gcd(n, m%n)

def isSolvable(m,n,k):
    if m + n < k:
        return False
    if m == 0 & n == 0:
        if k == 0:
            return True
        else:
            return False

    if k % gcd(m, n) == 0:
        return True
    else:
        return False

def bonus(m,n,k):
    if isSolvable(m,n,k) == True:
        print("Pentru instanta data PUTEM gasi o solutie!")
    else:
        print("Pentru instanta data NU PUTEM gasi o solutie!")

"""
#Backtracking
#def back(m,n,k):
    #if isSolvable(m,n,k) == True:
    # Tinem minte intr-un map starile si daca le am vizitat sau nu
        map={}
        stare = initState(m,n,k)
    # In coada tin minte starile pe care nu le vizitez
        q = deque()
        map[(stare[0],stare[1])]=1
        path = deque()
        bkt(stare,m,n,k)
"""

map = {}
q = deque()
path =  deque()

def back(m, n, k):
    if isSolvable(m, n, k) == False:
        print("Nu exista solutie")
    else:
        print("1")
        stare = initState(m, n, k)
        path.append(stare)
        map[(stare[0], stare[1])] = 1
        q.append(stare)

        print("2")
        stare1=stare
        while(len(q)>0):
            map[(stare[0], stare[1])] = 1
            path.append(stare)
            if isFinale(stare, k):
                print("Am gasit solutia: ")
                print(path)
            print("3")
            if isEmpty(stare[0]) == False:
                stare1 = empty(stare, 0)
                if (stare1[0], stare1[1]) not in map:
                    q.append(stare1)
            if isEmpty(stare[1]) == False:
                stare1 = empty(stare, 1)
                if (stare1[0], stare1[1]) not in map:
                    q.append(stare1)
            if isFull(m, stare[0]) == False:
                stare1 = fill(stare, m, n, 0)
                if (stare1[0], stare1[1]) not in map:
                    q.append(stare1)
            if isFull(n, stare[1]) == False:
                stare1 = fill(stare, m, n, 1)
                if (stare1[0], stare1[1]) not in map:
                    q.append(stare1)
            if canMove(stare, m, n, 0) == True:
                stare1 = move(stare, m, n, 0)
                if (stare1[0], stare1[1]) not in map:
                    q.append(stare1)
            if canMove(stare, m, n, 1) == True:
                stare1 = move(stare, m, n, 1)
                if (stare1[0], stare1[1]) not in map:
                    q.append(stare1)
            if stare1 == stare:
                stare1 = q.pop()
       # bkt(stare, m, n, k)



def bkt(stare, m, n, k):
    # Daca ajung la starea finala ma opresc
    if isFinale(stare, k):
        print("Am gasit solutia: ")
        print(path)
    else:
        # Caut o stare noua la care sa merg din starea curenta
        map[(stare[0],stare[1])]=1
        stare1 = stare
        path.append(stare)
        if isEmpty(stare[0]) == False:
            stare1 = empty(stare, 0)
            if (stare1[0], stare1[1]) not in map:
                q.append(stare1)
        if isEmpty(stare[1]) == False:
            stare1 = empty(stare, 1)
            if (stare1[0], stare1[1]) not in map:
                q.append(stare1)
        if isFull(m, stare[0]) == False:
            stare1 = fill(stare,m,n,0)
            if (stare1[0], stare1[1]) not in map:
                q.append(stare1)
        if isFull(n, stare[1]) == False:
            stare1 = fill(stare,m,n,1)
            if (stare1[0], stare1[1]) not in map:
                q.append(stare1)
        if canMove(stare,m,n,0) == True:
            stare1 = move(stare,m,n,0)
            if (stare1[0], stare1[1]) not in map:
                q.append(stare1)
        if canMove(stare,m,n,1) == True:
            stare1 = move(stare,m,n,1)
            if (stare1[0], stare1[1]) not in map:
                q.append(stare1)
        # Daca nu gasesc o stare noua, merg la ultima nevizitata din q
        if stare1==stare:
            stare1=q.pop()
            bkt(stare1,m,n,k)
        else:
            bkt(stare1,m,n,k)


back(4,3,2)



