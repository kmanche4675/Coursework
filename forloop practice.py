import numpy as np
# -*- coding: utf-8 -*-
"""
Created on Tue Sep  3 09:47:09 2024

@author: kmanc
"""

arr = np.array([[[1,2,3], [4,5,6]],[[7,8,9,], [10,11,12]]])

for x in arr:
    for y in x:
        for z in y:
            print(z)
    print(arr)