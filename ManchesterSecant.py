# -*- coding: utf-8 -*-
"""
Created on Thu Oct 31 09:35:43 2024

@author: kmanc
"""

def ManchesterSecant(f, x0, x1, Ea=1.e-7, maxit=30):
    """
    Function to solve the root of f(x) using the secant method

    Parameters
    ----------
    f : function
        The function f(x).
    x0 : float
        Initial guess.
    x1 : float
        Initial guess.
    Ea : float, optional
        Relative error criterion. The default is 1.e-7.
    maxit : int, optional
        Maximum number of iterations. The default is 30.

    Returns
    -------
    x2 : float
        Solution estimate for x.
    fx : float
        Function value at the solution estimate.
    ea : float
        Relative error achieved.
    i+1 : int
        Number of iterations taken.
    """
    for i in range(maxit):
        x2 = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0))
        ea = abs((x2 - x1) / x2)
        if ea < Ea:
            break
        x0 = x1
        x1 = x2
        
    return x2, f(x2), ea, i + 1

def f(x):
    return x**3 - 6*x**2 + 11*x - 6.1

x0 = 2.5
x1 = 3.5
(xsoln, fxsoln, ea, n) = ManchesterSecant(f, x0, x1)
print('Solution = {0:8.5g}'.format(xsoln))
print('Solution value at solution = {0:8.5e}'.format(fxsoln))
print('Relative error = {0:8.5e}'.format(ea))
print('Number of iterations = {0:5d}'.format(n))