import matplotlib.pyplot as plt
import numpy as np
from scipy import stats
import pandas as pd
import pymc3 as pm
import arviz as az

model = pm.Model()

alpha = 6

with model:
    trafic = pm.Poisson('T', 1/3)
    plata = pm.Normal("p", mu = 1, sigma = 10)
    gatit = pm.Exponential('g', alpha)
    statieGatit = np.exp('SG', alpha)
