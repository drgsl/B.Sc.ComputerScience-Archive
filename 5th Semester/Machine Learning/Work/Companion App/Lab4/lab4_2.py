import pandas as pd
from sklearn import tree
import matplotlib.pyplot as plt

X = pd.DataFrame({'A': [1, 1, 0, 0],
                  'B': [1, 0, 1, 0],
                  'C': [0, 1, 1, 1]})
Y = pd.Series([0, 1, 1, 0])

dt = tree.DecisionTreeClassifier(criterion="entropy").fit(X,Y)

fig, ax = plt.subplots(figsize = (7,8))
f = tree.plot_tree(dt, ax=ax,fontsize = 10)
plt.show()