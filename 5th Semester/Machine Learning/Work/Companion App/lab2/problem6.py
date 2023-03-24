from scipy.stats import binom
from scipy.stats import geom
import matplotlib.pyplot as plt
import numpy as np
import random

prob = binom.pmf(12, 16, 0.5)

print(prob)
print(prob*100, "%")
