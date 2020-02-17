import matplotlib.pyplot as plt
from numpy import *
A=array([0,0])
B=array([10,0])
P1=array([2,4])
P2=array([4,4])
M=lambda t,A,B,C,D:(1-t)**3*A + 3*(1 - t)**2*t*B + 3*(1 - t)*t**2*C + t**3*D
X=[i*0.01 for i in range(100)]

Y=[M(t,A,P1,P2,B) for t in X ]
a=[x[0] for x in Y ]

b=[x[1] for x in Y ]
plt.plot(a,b)
plt.show()