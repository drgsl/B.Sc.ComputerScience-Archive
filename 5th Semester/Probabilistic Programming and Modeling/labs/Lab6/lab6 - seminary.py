import statistics

import pandas as pd
import math
import numpy as np
from pprint import pprint
import matplotlib.pyplot as plt
from pgmpy.models import BayesianNetwork
from pgmpy.inference import VariableElimination
from pgmpy.factors.discrete import TabularCPD
from scipy.stats import stats
import pymc3 as pm
import arviz as az

children_dataset = pd.read_csv("data.csv")

ppvt=list(children_dataset["ppvt"])
educ_cat=list(children_dataset["educ_cat"])
mom_age=list(children_dataset["momage"])

#ex. 1
coef = np.polyfit(np.array(mom_age),np.array(ppvt),1)
poly1d_fn = np.poly1d(coef)
# poly1d_fn is now a function which takes in x and returns an estimate for y

plt.plot(np.array(mom_age),np.array(ppvt), 'yo', np.array(mom_age), poly1d_fn(np.array(mom_age)), '-')
plt.show()

#ex. 2
mom_age_std=[]
for i in range(len(mom_age)):
    mom_age_std.append(((mom_age[i]-statistics.mean(mom_age))/np.std(mom_age)))

ppvt_std=[]
for i in range(len(ppvt)):
    ppvt_std.append(((ppvt[i]-statistics.mean(ppvt))/np.std(ppvt)))

print(mom_age)
print(ppvt_std)
with pm.Model() as model_g:
    alfa = pm.Normal('alfa', mu=statistics.mean(mom_age), sd=np.std(mom_age))
    beta = pm.Normal('beta', mu=statistics.mean(ppvt), sd=np.std(ppvt))
    epsilon = pm.HalfCauchy('epsilon', 5)
    miu = pm.Deterministic('miu', alfa + beta * mom_age_std)
    y_pred = pm.Normal('y_pred', mu=miu, sd=epsilon, observed=ppvt_std)

    idata_g = pm.sample(2000, tune=2000, return_inferencedata=True)


az.plot_trace(idata_g, var_names=['alfa', 'beta', 'epsilon'])