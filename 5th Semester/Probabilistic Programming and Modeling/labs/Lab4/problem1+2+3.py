import matplotlib.pyplot as plt
import numpy as np
from scipy import stats
import pandas as pd
import pymc3 as pm
import arviz as az


# problem 1
model = pm.Model()
with model:
    alpha = 4.66
    clients_per_hour = pm.Poisson('clients_per_hour' ,alpha)
    waiting_time = pm.Normal('waiting_time', mu=1, sigma=1/2)
    avg_order = pm.Exponential('avg_order_time', 1/alpha)
    trace = pm.sample(20000)

dictionary = {
              'preparation_time': trace['avg_order_time'].tolist(),
              'waiting_time': trace['waiting_time'].tolist(),
              }
df = pd.DataFrame(dictionary)

# problem 2
waiting_time_under_15_mins = df[(df['waiting_time'] + df['preparation_time'] <= 15)]

sample_size =  df.shape[0]

waiting_time_under_15_mins_percentage = waiting_time_under_15_mins.shape[0] / sample_size
print("Waiting time under 15 minutes percentage", waiting_time_under_15_mins_percentage)

# problem 3
customer_waiting_time = list(sum(x) for x in zip(df['waiting_time'], df['preparation_time']))
average_customer_waiting_time = sum(customer_waiting_time) / sample_size

print("Average customer waiting time:", average_customer_waiting_time)
