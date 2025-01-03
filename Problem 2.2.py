# -*- coding: utf-8 -*-
"""
Created on Sun Sep 22 17:34:05 2024

@author: kmanc
"""
import math 
import numpy as np
import matplotlib.pyplot as plt

t1 = np.linspace(0.1,0.25,10)

def f1(t):
    return ((6*t**3)-3*t-4)/(8 * np.sin(5*t))

y = np.vectorize(f1)

plt.plot(t1,y(t1))
plt.show()