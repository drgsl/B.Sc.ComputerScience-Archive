import arviz as az
import matplotlib.pyplot as plt

import numpy as np
import pymc3 as pm
import pandas as pd

if __name__ == "__main__":
    data = pd.read_csv('Admission.csv')

    gre = data['GRE'].values
    gpa = data['GPA'].values
    y_0 = pd.Categorical(data['Admission']).codes

    print(data.shape[0])
    admission_model = pm.Model()
    with admission_model:
        b0 = pm.Normal('b0', mu=0, sd=10)
        b1 = pm.Normal('b1', mu=0, sd=10)
        b2 = pm.Normal('b2', mu=0, sd=10)

        μ = b0+pm.math.dot(b1, gre)+pm.math.dot(b2, gpa)
        θ = pm.Deterministic('θ', pm.math.sigmoid(μ))
        #bd = pm.Deterministic('bd', -α / β)
        p = pm.Bernoulli('p', p=θ, observed=y_0)


        trace = pm.sample(20000, tune=20000, cores=4)
        trace = pm.sample(return_inferencedata=True)

    result = pm.sample_posterior_predictive(trace, samples=500, model=admission_model)

    az.plot_posterior(result, hdi_prob=0.94)
