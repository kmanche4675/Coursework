# -*- coding: utf-8 -*-
"""
Created on Thu Oct 31 09:03:31 2024

@author: kmanc
"""
import numpy as np
def ManchesterNewtraph(f, fp, x0, Ea=1.e-7, maxit=30):
    """
    Parameters
    ----------
    f : function
        The function f(x).
    fp : function
        The derivative f'(x).
    x0 : float
        Initial guess for x.
    Ea : float, optional
        Relative error threshold. The default is 1.e-7.
    maxit : int, optional
        Maximum number of iterations. The default is 30.
    
    Returns
    -------
    x1 : float
        Solution estimate.
    fx : float
        Equation error at solution estimate.
    ea : float
        Relative error.
    i+1 : int
        Number of iterations.
    """
    for i in range(maxit):
        x1 = x0 - f(x0) / fp(x0)
        ea = abs((x1 - x0) / x1)
        if ea < Ea:
            break
        x0 = x1
    return x1, f(x1), ea, i+1

def f(x):
    return x**3 - 6*x**2 + 11*x - 6.1

def fp(x):
    return 3*x**2 - 12*x + 11

x0 = 3.5
(xsoln, fxsoln, ea, n) = ManchesterNewtraph(f, fp, x0, Ea=1.e-5)
print('Solution = {0:8.5g}'.format(xsoln))
print('Solution value at solution = {0:8.5e}'.format(fxsoln))
print('Relative error = {0:8.5e}'.format(ea))
print('Number of iterations = {0:5d}'.format(n))

coeff = [1,-6,11,-6.1]
print('True Root Values', np.roots(coeff))