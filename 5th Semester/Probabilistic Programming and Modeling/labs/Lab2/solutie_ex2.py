import numpy as np
from scipy import stats

import matplotlib.pyplot as plt
import arviz as az

s1 = stats.gamma.rvs(4,0, 1/3, size=10000)
s2 = stats.gamma.rvs(4,0, 1/2, size=10000)
s3 = stats.gamma.rvs(5,0, 1/2, size=10000)
s4 = stats.gamma.rvs(5,0, 1/3, size=10000)
client_server_latency = stats.expon.rvs(0,1/4, size=10000)
alegere_server = stats.multinomial.rvs(1,[0.25,0.25,0.3,0.2], size=10000) # Alternativ se poate folosi "rv_discrete"

# Formam o matrice 4x10000, si indexam cu matricea 4x10000 care este in format one-hot, adunam la sfarsit latenta care este prezenta in toate cazurile
X = np.stack((s1,s2,s3,s4),axis=1)[alegere_server==1] + client_server_latency

# Numarul de sample-uri unde timpu >3, impartit la totalul de sample-uri
prob_3ms = len(X[X>3])/len(X)
print(prob_3ms)

az.plot_posterior(
    {'Server 1':s1,
     'Server 2':s2,
     'Server 3':s3,
     'Server 4':s4,
     'Latenta client-server':client_server_latency,
     'Alegere server':np.argmax(alegere_server,axis=1), # Transformam din one-hot in categorii
     'X':X})
plt.show()

# Similar cu solutia ex. 1, se putea obtine acelasi rezultat prin iterarea prin sample-uri cu un for si compunerea distributiei X in diferite moduri