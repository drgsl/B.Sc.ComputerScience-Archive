
import arviz as az
import matplotlib.pyplot as plt
import pandas as pd
import pymc3 as pm

if __name__ == '__main__':

    # Ex1

    # az.plot_trace(az.load_arviz_data("centered_eight"))
    # az.plot_trace(az.load_arviz_data("non_centered_eight"))

    print(az.ess(az.load_arviz_data("centered_eight")))
    print("-----------------------------------------------------------")
    print(az.ess(az.load_arviz_data("non_centered_eight")))
    # Marimea esantionului: 8 pentru ambele;

    # Distributia a posteriori
    az.plot_posterior(az.load_arviz_data("centered_eight"))
    az.plot_posterior(az.load_arviz_data("non_centered_eight"))
    plt.show()


    data = az.load_arviz_data("centered_eight")
    trace = data["posterior"]

    #Numarul de lanturi
    num_chains = len(trace)
    print(f"Number of chains: {num_chains}")


    data = az.load_arviz_data("non_centered_eight")
    trace = data["posterior"]

    #Numarul de lanturi
    num_chains_non = len(trace)
    print(f"Number of chains: {num_chains_non}")



    # Ex2
    # (Rhat)
    summaries = pd.concat([az.summary(az.load_arviz_data("centered_eight"), var_names=['mu', 'tau']),
                           az.summary(az.load_arviz_data("non_centered_eight"), var_names=['mu', 'tau'])])
    summaries.index = ['mu', 'tau', 'mu', 'tau']
    print((summaries))

    # autocorelatie
    az.plot_autocorr(az.load_arviz_data("centered_eight"))
    az.plot_autocorr(az.load_arviz_data("non_centered_eight"))

    plt.show()

    # Ex3

    with pm.Model() as centered_model:
        a = pm.HalfNormal('a', 10)
        b = pm.Normal('b', 0, a, shape=10)
        idata_cm = pm.sample(2000, target_accept=0.9, return_inferencedata=True, chains=2)

    with pm.Model() as non_centered_model:
        a = pm.HalfNormal('a', 10)
        b_offset = pm.Normal('b_offset', mu=0, sd=1, shape=10)
        b = pm.Deterministic('b', 0 + b_offset * a)
        idata_ncm = pm.sample(2000, target_accept=0.9, return_inferencedata=True, chains=2)

        centered_model.diverging.sum()
        non_centered_model.diverging.sum()

        _, ax = plt.subplots(1, 2, sharey=True, sharex=True, figsize=(10, 5), constrained_layout=True)

        for idx, tr in enumerate([az.load_arviz_data("centered_eight"), az.load_arviz_data("non_centered_eight")]):
            az.plot_pair(tr, var_names=['b', 'a'], coords={'b_dim_0': [0]}, kind='scatter',
                         divergences=True, divergences_kwargs={'color': 'C1'},
                         ax=ax[idx])

            ax[idx].set_title(['centered', 'non-centered'][idx])