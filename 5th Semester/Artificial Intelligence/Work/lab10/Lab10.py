from rdflib import Graph
import pprint
from nltk.corpus import wordnet as wn

import nltk

g = Graph()
g.parse("food.rdf")

print(len(g))
# prints: 2

# for stmt in g:
    # pprint.pprint(stmt)

print(wn.synsets('dog'))
