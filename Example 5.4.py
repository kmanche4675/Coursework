# -*- coding: utf-8 -*-
"""
Created on Sun Oct 27 20:56:03 2024

@author: kmanc
"""

import numpy as np

def incsearch(func,xmin,xmax,ns=50):
    """
    incsearch
    Parameters
    ----------
    func : TYPE
        DESCRIPTION.
    xmin : TYPE
        DESCRIPTION.
    xmax : TYPE
        DESCRIPTION.
    ns : TYPE, optional
        DESCRIPTION. The default is 50.

    Returns
    -------
    None.

    """
    x = np.linspace(xmin,xmax,ns) #create array of x values
    f = [] #build array of correspoinding functino values 
    for k in range(ns-1):
        f.append(func(x[k]))
    nb = 0
    xb = []
    for k in range(ns-2): #check adjacen pairs of function values
        if func(x[k])*func(x[k+1])<0: # for sign change
            nb = nb + 1 # increment the brakcet counter
            xb.append((x[k],x[k+1])) # save the bracketing pair
    if nb == 0:
       return 'no brackets found' 
    else:
        return nb,xb