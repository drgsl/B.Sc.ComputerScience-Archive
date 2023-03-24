import pandas as pd
from sklearn import tree
import matplotlib.pyplot as plt
exoplanets = pd.DataFrame([
  (205, 0),
  (205, 0),
  (260, 1),
  (380, 1),
  (205, 0),
  (260, 1),
  (260, 1),
  (380, 0),
  (380, 0)
],
columns=['Temperature', 'Habitable'])
print(exoplanets)

#1
x = exoplanets[['Temperature']]
y = exoplanets['Habitable']

#print(X)
#print(y)
dt = tree.DecisionTreeClassifier(criterion='entropy').fit(x,y)
fig, ax = plt.subplots(figsize=(7, 8))
f = tree.plot_tree(dt, ax=ax, fontsize=10, feature_names=X.columns)
plt.show()

print(dt.score(X, y))

#2
import numpy as np
temps = exoplanets.filter(items=['Temperature'])
vals,count = np.unique(temps,return_counts=True)
vals = sorted(vals)
split_points = []
for i in range(len(vals)-1):
  split_points.append((vals[i]+vals[i+1])/2)
print(split_points)

#3
print(entropy([4/9,5/9], base=2))
print()