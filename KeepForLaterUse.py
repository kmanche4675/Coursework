# -*- coding: utf-8 -*-
"""
Created on Tue Sep 17 09:20:45 2024

@author: kmanc
"""


import numpy as np
import matplotlib.pylab as plt

time,x,y = np.loadtxt('ExampleData.txt',unpack =True)

plt.plot(time, x, c='r')
plt.twinx()  # share the x axis with the y axis y wont changee but x will

plt.plot(time,y,c='y',ls='--')
plt.grid()
timecvs, xcvs, ycvs = np.loadtxt('ExampleData.csv', unpack=True, delimiter=',')
np.savetxt('DemoFileSave.txt', np.array([timecvs,xcvs,ycvs]).transpose(), fmt=['%10d', '%10.5f', '%5.5f'])

print('time=', timecvs,'x =', xcvs, 'y=', ycvs)

time, x, y = np.loadtxt('ExampleData.csv', unpack=True, delimiter=',')
X = np.array([time, x, y]).transpose()
np.save('Xdata.npy', X)
x2 = np.load('Xdata.npy')
print(x2)