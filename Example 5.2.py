# -*- coding: utf-8 -*-
"""
Example 5.2
Function for trail-and-error method
"""

import numpy as np
def vtest(mtest):
    cd = 0.25 ; g = 9.81; t = 4
    return np.sqrt(mtest*g/cd)*np.tanh(np.sqrt(cd*g/mtest)*t)

