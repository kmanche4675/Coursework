# -*- coding: utf-8 -*-
"""
Created on Thu Sep 26 09:28:33 2024

@author: kmanc
"""

import numpy as np
import matplotlib.pyplot as plt 

alpha1, alpha2 = 6, 5
def myweib(alpha, beta):
    e = 2.71828
    x = np.linspace(0, 6, 1000)  # Define a range for x
    f = (alpha / (beta ** alpha)) * (x ** (alpha - 1)) * (e ** -(x / beta) ** alpha)
    """
    Parameters
    ----------
    alpha : a variable to be used when calculating the weibull
    beta : a variable to be used when calculating the weibull

    Returns
    -------
    f : Weibull probability density function values for the formula.
    x : The line space for the given graph
    """
    return x, f  # Return x first, then f

#assining alpha and beta variables to myweib function
frst_alpha_6, frst_beta_1 = myweib(6, 1)
snd_alpha_6, frst_beta_2 = myweib(6, 2)
frst_alpha_5, snd_beta_1 = myweib(5, 1)
snd_alpha_5, snd_beta_2 = myweib(5, 2)

#Graphing assinged variables from myweib function

plt.figure()
plt.grid()
plt.title('Kendrick Manchester Fall 2024 CSC 2262')
plt.plot(frst_alpha_6, frst_beta_1, label='alpha=6, beta=1')
plt.plot(snd_alpha_6, frst_beta_2, label='alpha=6, beta=2')
plt.plot(frst_alpha_5, snd_beta_1, label='alpha=5, beta=1')
plt.plot(snd_alpha_5, snd_beta_2, label='alpha=5, beta=2')
plt.legend()
plt.show()


# Plots first histogram
x1 = np.random.weibull(alpha1, 3000)
plt.figure()
plt.title('alpha = 6 Kendrick Manchester Fall 2024 CSC 2262')
plt.hist(x1, bins=11, density=True, color='YellowGreen', edgecolor='black', alpha=0.7)
plt.legend(loc='upper right')
plt.grid()
plt.show()  

# Plots second histogram
x2 = np.random.weibull(alpha2, 3000)
plt.title('alpha = 5 Kendrick Manchester Fall 2024 CSC 2262')
plt.hist(x2, bins=11, density=True, alpha=0.6, color='DodgerBlue', edgecolor='black')
plt.legend(loc='upper right')
plt.grid()
plt.show()

# A difference I can see between the two histograms is that one that has alpha as
#5 is more distributed to the right while the one that has alpha as 6 is more normal
print(myweib.__doc__)