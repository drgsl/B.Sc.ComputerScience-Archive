import matplotlib.pyplot as plt
import numpy as np
from sklearn import datasets, linear_model
import pandas as pd
import pymc3 as pm

# Preluare date din fisierul csv
df = pd.read_csv("C:\\Users\\mihne\\Desktop\\PMP2022\\data.csv")

Y = df['momage']
X = df['ppvt']

X=X.values.reshape(len(X),1)
Y=Y.values.reshape(len(Y),1)

# Plot 
plt.scatter(X, Y,  color='black')
plt.title('Test Data')
plt.xlabel('Mother Age')
plt.ylabel('IQ')
plt.xticks(())
plt.yticks(())

#Afisare grafic
plt.show()

# 2.

with pm.Model() as model_g:
    α = pm.Normal('α', mu=0, sd=50)
    β = pm.Normal('β', mu=0, sd=10)
    ε = pm.HalfCauchy('ε', 5)
    μ = pm.Deterministic('μ', α + β * X)
    y_pred = pm.Normal('y_pred', mu=μ, sd=ε, observed=Y)
    
    idata_g = pm.sample(2000, tune=2000, return_inferencedata=True)


# 3.
posterior_g = idata_g.posterior.stack(samples={"educ_cat", "ppvt"})

# Afisare dreapta de regresie
print(posterior_g)

# 4.

Y = df['educ_cat']
X = df['ppvt']

X=X.values.reshape(len(X),1)
Y=Y.values.reshape(len(Y),1)

# Plot 
plt.scatter(X, Y,  color='black')
plt.title('Test Data')
plt.xlabel('Education Level')
plt.ylabel('IQ')
plt.xticks(())
plt.yticks(())

#Afisare grafic
plt.show()

#Modelul Bayesian de regresie liniara

with pm.Model() as model_g:
    α = pm.Normal('α', mu=0, sd=50)
    β = pm.Normal('β', mu=0, sd=10)
    ε = pm.HalfCauchy('ε', 5)
    μ = pm.Deterministic('μ', α + β * X)
    y_pred = pm.Normal('y_pred', mu=μ, sd=ε, observed=Y)
    
    idata_g = pm.sample(2000, tune=2000, return_inferencedata=True)

# Afisare dreapta de regresie
print(posterior_g)
