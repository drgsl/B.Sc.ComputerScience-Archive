import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import pymc3 as pm
import arviz as az

model = pm.Model()

with model:
    cutremur = pm.Bernoulli('C', 0.0005)
    
    incendiu_p = pm.Deterministic('I_p',
    pm.math.switch(cutremur, 0.03, 0.01)
    )
    incendiu = pm.Bernoulli('I',
    p = incendiu_p)

    alarma_p = pm.Bernoulli('A_p', 
    pm.math.switch(incendiu,
    pm.math.switch(cutremur, 0.98, 0.95),
    pm.math.switch(cutremur, 0.02, 0.0001)
    )
    )

    alarma = pm.Bernoulli('A', p = alarma_p)
    trace = pm.sample(20000)

dictionary = {
              'alarma': trace['A'].tolist(),
              'cutremur': trace['C'].tolist()
              }
df = pd.DataFrame(dictionary)

p_alarma = df[(df['alarma'] == 1)].shape[0] / df.shape[0]
print(p_alarma)

az.plot_posterior(trace)
plt.show()