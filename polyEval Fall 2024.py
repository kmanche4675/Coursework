# -*- coding: utf-8 -*-
"""
Created on Mon Oct  7 22:49:37 2024

\]


@author: Sheryl LaFleur
"""

import numpy as np
#import math

#Print the polynomial
polynomial = np.poly1d([3,-2,2])

#polynomial = np.poly1d([1, 0 , 0 ,  0, 4, 3, -7])
print( polynomial)

#Evaluate the polynomial and at specific value
# at x = some give value
x = 4
trueValue = np.polyval(polynomial,x)
print('True Value ===>', trueValue, 'at x =', x)

#Evaluate the Zero Order of the Taylor Series
x=1
h=1
zeroOrder = np.polyval(polynomial,x)
print('Zero Order ===>', zeroOrder, 'at x =', x)

#Evaluate the First Order of the Taylor Series
####
#Find the first derivate
firstDev = polynomial.deriv(1)
firstOrder = np.polyval(firstDev,x)
firstOrder = zeroOrder + firstOrder * h
print('First Order ===>', firstOrder, 'at x =', x)

#Evaluate the Second Order of the Taylor Series
####
#Find the Second derivate
secondDev = polynomial.deriv(2)
secondOrder = np.polyval(secondDev,x)
#secondOrder = zeroOrder + firstOrder + (secondOrder/math.factorical)
print('Second Order ===>', secondOrder, 'at x =', x)


#Evaluate the Third Order of the Taylor Series
####
#Find the Third derivate
thirdDev = polynomial.deriv(3)
thirdOrder = np.polyval(thirdDev,x)
print('Third Order ===>', thirdOrder, 'at x =', x)


