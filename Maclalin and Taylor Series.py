# -*- coding: utf-8 -*-
"""
Created on Tue Sep 24 09:43:52 2024

@author: kmanc
"""

#itermath pg. 89 

import math 
def itermeth(x, es = 1e-4, maxit = 50):
    """
    Maclaurin series expansion of teh exponential function
    requires math module

    Parameters
    ----------
    x : value at which the series is evaluated 
        
    es : stopping criteron (default = 1e-4)
        
    maxit : maximum number of iterations(default = 50)
        D

    Returns
    -------
    output: 
        fx = estimated function value
        ea = approximate relative error(%)
        iteration = number of iterations
    """
    
#initizlize 
    iter = 1; sol = 1; ea = 100; 
    # iteration 
    while True:
        solold = sol
        sol = sol + x**iter / math.factorial((iter))
        iter = iter + 1
        if sol != 0: ea = abs ((sol-solold)/sol)*100  #pg.87
        if ea < es or iter == maxit : break
    
    
    fx = sol
    return fx, ea, iter
approxval, ea, iter = itermeth(1, 1e-6, 100)
print('Estimated Function Value = ', approxval, 'Approximate Relative Error', ea, 'Number of Iterations =', iter)

print('True Value of e(1)',math.exp(1))