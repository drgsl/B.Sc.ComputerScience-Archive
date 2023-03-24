import numpy as np
from scipy import stats

import matplotlib.pyplot as plt
import arviz as az

np.random.seed(1)

def prod_pdf(x,pdfs):
    prod=np.ones(np.array(pdfs)[0].shape)
    for pdf in pdfs:
        print(prod)
        for c,y in enumerate(pdf):
            prod[c]=prod[c]*y
        print('final:', prod)
    return prod

def conflate_pdf(x,dists,lb,ub):
    denom = quad(prod_pdf, lb, ub, args=(dists))[0]
    print('Denom: ',denom)
    print('product pdf: ', prod_pdf(x,dists))
    conflated_pdf=prod_pdf(x,dists)/denom
    print(conflated_pdf)
    return conflated_pdf

lambda1 = 4
lambda2 = 6

m1 = stats.expon.rvs(0, 1/lambda1, size=10000)
# Distributie normala cu media 0 si deviatie standard 1,
# 1000 samples

m2 = stats.expon.rvs(0, 1/lambda2, size=10000)
#  Distributie uniforma intre -1 si 1, 1000 samples .
#  Primul parametru fiind limita inferioara a intervalului,
#  al doilea parametru fiind "marimea" intervalului,
#  aka [-1,-1+2] = [-1,1] 

# result = stats.ultivariate_normal.pdf(m1, m2)
# Compunerea prin insumare a celor 2 distributii

dists=[m1,m2]
lb=-10
ub=10
domain=np.arange(lb,ub,.01)
graph=conflate_pdf(domain, dists,lb,ub)

az.plot_posterior({'Mecanic 1':m1,'Mecanic 2':m2,'Sum':graph}) # Afisarea aproximarii densitatii probabilitatilor, mediei, intervalului etc. variabilelor x,y,z
plt.show() 