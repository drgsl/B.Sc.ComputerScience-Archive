
import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats
import pymc3 as pm
import arviz as az

# A. 

# distributia pentru numarul de oameni care viziteaza o anume cafenea in intervalul de timp folosind numpy

model_oameni = stats.poisson(10)
oameni = model_oameni.rvs(1000)
plt.hist(oameni, bins=20)
plt.show()

# generare de eşantion aleator şi vizualizare cu ajutorul Matplotlib

esantion_oameni = np.random.poisson(10, 1000)
plt.hist(esantion_oameni, bins=20)
plt.show()

# distributia pentru greutatea cainilor adulti in kilograme folosind numpy

model_caini = stats.uniform(10, 50)
caini = model_caini.rvs(1000)
plt.hist(caini, bins=20)
plt.show()

# generare de eşantion aleator caini şi vizualizare cu ajutorul Matplotlib

esantion_caini = np.random.uniform(10, 50, 1000)
plt.hist(esantion_caini, bins=20)
plt.show()

# distributia pentru greutatea elefantilor adulti in kilograme folosind numpy

model_elefanti = stats.norm(1000, 100)
elefanti = model_elefanti.rvs(1000)
plt.hist(elefanti, bins=20)
plt.show()

# generare de eşantion aleator elefanti şi vizualizare cu ajutorul Matplotlib

esantion_elefanti = np.random.normal(1000, 100, 1000)
plt.hist(esantion_elefanti, bins=20)
plt.show()

# distributia pentru greutatea oamenilor adulti in kilograme folosind numpy

model_oameni = stats.skewnorm(10, 100, 100)
oameni = model_oameni.rvs(1000)
plt.hist(oameni, bins=20)
plt.show()

# generare de eşantion aleator oameni şi vizualizare cu ajutorul Matplotlib

esantion_oameni = np.random.skewnorm(10, 100, 100, 1000)
plt.hist(esantion_oameni, bins=20)
plt.show()

# B.

# 1.

with pm.Model() as model:
    n = pm.Poisson('n', 10)
    theta = pm.Beta('theta', 1, 1)
    y = pm.Binomial('y', n, theta, observed=10)
    trace = pm.sample(1000, tune=1000, chains=2)

az.plot_posterior(trace, var_names=['n', 'theta'])

# 2.

# Efectul lui Y asupra distribuţiei a posteriori este că dacă Y este mai mare, atunci distribuţia a posteriori
# va fi mai mare, iar dacă Y este mai mic, atunci distribuţia a posteriori va fi mai mică.

# Efectul lui θ asupra distribuţiei a posteriori este că dacă θ este mai mare, atunci distribuţia a posteriori  
# va fi mai mare, iar dacă θ este mai mic, atunci distribuţia a posteriori va fi mai mică.

# D

# simuare folosind formula y = 9 + 3x + N (0, 5) cu x generat de np.linspace(-20,10,100)

x = np.linspace(-20, 10, 100)
y = 9 + 3 * x + np.random.normal(0, 5, 100)

# calibrare model liniar de forma α + βx + ε

with pm.Model() as model:
    alpha = pm.Normal('alpha', 0, 10)
    beta = pm.Normal('beta', 0, 10)
    verosimilitate = pm.Normal('verosimilitate', 0, 10)
    sigma = pm.HalfStudentT('sigma', 3, 0, 10)
    epsilon = pm.HalfStudentT('epsilon', 3, 0, 10)
    y_pred = alpha + beta * x + verosimilitate * epsilon
    y_obs = pm.Normal('y_obs', mu=y_pred, sigma=sigma, observed=y)
    trace = pm.sample(1000, tune=1000, chains=2)

# verificare rezultate şi recuperare parametrii folosind plot_posterior

az.plot_posterior(trace, var_names=['alpha', 'beta', 'verosimilitate', 'sigma', 'epsilon'])

# verificare rezultate şi recuperare parametrii folosind plot_forest

az.plot_forest(trace, var_names=['alpha', 'beta', 'verosimilitate', 'sigma', 'epsilon'])