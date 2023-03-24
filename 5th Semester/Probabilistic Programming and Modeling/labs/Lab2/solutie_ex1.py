import random
import numpy as np
from scipy import stats

import matplotlib.pyplot as plt
import arviz as az

m1 = stats.expon.rvs(0,1/4, size=10000) # Distributie exponentiala a timpului de servire a primului mecanic
m2 = stats.expon.rvs(0,1/6, size=10000) # Distributie exponentiala a timpului de service a mecanicului 2
servit_m1 = stats.binom.rvs(1,0.4, size=10000) # Distributia sansei de a fi preluat de mecanicul 1 este reprezentata printr-o distributie binomiala cu probabilitatea de 40%

X = np.concatenate((m1[servit_m1 == 1],m2[servit_m1 == 0])) # X este concatenarea cazurilor cand clientul este preluat de mecanicul 1 (servit_m1 == 1), si cazurile cu mecanicul 2 (servit_m1 == 0)   

az.plot_posterior({'Mecanic 1':m1,'Mecanic 2':m2,'Servit de mecanic 1':servit_m1,'X':X}) # Afisarea aproximarii densitatii probabilitatilor, mediei, intervalului etc. a variabilelor
plt.show()


# Se poate rezolva, in multiple moduri, fara folosirea unei distributii binomiale prin iterarea sample-urilor din m1 si m2 cu un for si compunerea lor de mana
# Ex:
X = []
for i in range(10000):
    X.append(m1[i] if random.random() < 0.4 else m2[i])

# Combinarea m1 si m2 prin calcularea unei medii ponderate intre cele 2 va rezulta intr-o medie totala corecta dar distributia valorilor va fi gresita
# Ex:
m1 = stats.expon.rvs(0,1/4, size=10000)
m2 = stats.expon.rvs(0,1/6, size=10000)
X_incorrect = m1*0.4+m2*0.6

az.plot_posterior({'Incorrect X':X_incorrect, 'Correct X':X})
plt.show()

# O alta solutie, partial incorecta, ar fi de generat 4000 sample-uri pentru m1 si 6000 sample-uri pentru m2
# aceasta solutie are sa aiba media corecta si functia de densitate foarte apropiata dar elimina modelarea "sansei" sa fi servit de mecanicul 1
# desi *in medie* esti servit 40% din timp de mecanicul 1, asta nu inseamna mereu *exact* 40% din cazuri vei fi servit de m1
# Ex:
m1 = stats.expon.rvs(0,1/4, size=4000)
m2 = stats.expon.rvs(0,1/6, size=6000)
X = np.concatenate((m1,m2))
# Aceiasi problema o are si solutia de mai jos:
m1 = stats.expon.rvs(0,1/4, size=10000)
m2 = stats.expon.rvs(0,1/6, size=10000)
X = np.concatenate((m1[:4000],m2[4000:]))


