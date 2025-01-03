# -*- coding: utf-8 -*-
"""
Created on Thu Oct 24 10:02:22 2024

@author: kmanc
"""

import numpy as np
import pylab
cd = .25 ; g = 9.81; v = 36; t = 4.
mp = np.linspace(50.,200.)
fp = np.sqrt(mp*g/cd)*np.tanh(np.sqrt(cd*g/mp)*t)-v
pylab.plot(mp,fp,c='k',lw=0.5)
pylab.grid()
pylab.xlabel('mass - kg')
pylab.ylabel('f(m) - m/s')