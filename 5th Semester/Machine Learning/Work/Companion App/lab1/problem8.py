from tools.stats import probability
from itertools import product

from random import sample


coin = {'H', 'T'}
omega = set(product(coin, coin))

A = set (i for i in omega if i[0] == 'H')
B = set (i for i in omega if i[1] == 'H')
C = set (i for i in omega if (i[1] == i[0]))

print("omega:", omega)
print("A:", A)
print("B:",B)

print("Proving that events A and B are independent using the useful properties:")

print("Probability of P(AnB)= ", probability(A.intersection(B), omega))
print("Probability of P(A)P(B)= ", probability(A, omega) * probability(B, omega))


print("Proving that events A and C are independent using the useful properties:")

print("Probability of P(AnC)= ", probability(A.intersection(C), omega))
print("Probability of P(A)P(C)= ", probability(A, omega) * probability(C, omega))

