# -*- coding: utf-8 -*-
"""
Created on Thu Oct  3 10:04:42 2024

@author: kmanc
"""

import numpy as np
import matplotlib.pyplot as plt

import math 
from mat import pi

def taylor_cosine_appx(x, maxit =  20, es=00.5e-1):
    """
    

    Parameters
    ----------
    x : is the value at which the series or function is evaluated the angle in radians being evaluated.
        The Taylor Series Expression for cos(x)
        DESCRIPTION.
    maxit : maximum number of iterations (need to find a good approximation (the number of terms needed))
    
    es : an accepted value of the percetn realtive error (a stopping criterion)
        DESCRIPTION. The default is 00.5e-1.
    ES = (0.5x1-^2-n)%
    Returns
    -------
    None.

    """