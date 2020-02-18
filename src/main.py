import matplotlib.pyplot as plt
from numpy import *
A=array([700,20])
B=array([700,20])
P1=array([10,1000])
P2=array([700,770])
M=lambda t,A,B,C,D:(1-t)**3*A + 3*(1 - t)**2*t*B + 3*(1 - t)*t**2*C + t**3*D
X=[i*0.01 for i in range(100)]

Y=[M(t,A,P1,P2,B) for t in X ]

import pyautogui as pt
from time import sleep
while 1:
	for i,j in Y:
		pt.moveTo(i,j)
		sleep(0.0012)

