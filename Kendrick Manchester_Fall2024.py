# -*- coding: utf-8 -*-
"""
Created on Thu Sep 26 10:13:24 2024

@author: kmanc
"""


import numpy as np
import matplotlib.pylab as plt

def myhelp ():
    """
This program reads data from the given text files 
and makes a pie chart from the info 
since one of them are not the same size 
as the others were going to append the word purple to it
    """

print(myhelp.__doc__)
moneyWellSpent = np.loadtxt('moneyWellSpent.txt',unpack =True) 
myParisCost = 'myParisCost.txt'
with open(myParisCost, 'r') as file:
    myParisCost = file.read().splitlines()
    
myParisColors = 'myParisColors.txt'
with open(myParisColors, 'r') as file:
    myParisColors  = file.read().splitlines()
myParisColors.append('purple')
plt.title(' Paris 2024 Palaiseau Kendrick ManchesterFall2024 CSC 2262')
plt.pie(moneyWellSpent, colors=myParisColors, labels=myParisCost)

plt.legend()
plt.show()
