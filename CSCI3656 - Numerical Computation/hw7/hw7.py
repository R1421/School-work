#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt

v_0 = 300
c_d = 0.2
r = 0.05

c = -np.pi/2 * c_d * r**2

def find_v(v_x,v_y):
    return np.sqrt(v_x**2 + v_y**2)

def ode_euler(v_0, theta, m, tfinal, h=0.1):
    A = np.array([0,0,v_0*np.cos(theta),v_0*np.sin(theta)])
    t = 0
    thist = [0]
    Ahist = [A]
    while t < tfinal:
        h = min(h, tfinal-t)
        v = find_v(A[0], A[1])
        A[0] += h * A[2]
        A[1] += h * A[3]
        A[2] += h * (c*v*A[2]/m)
        A[3] += h * (c*v*A[3]/m - 9.8)
        t += h
        thist.append(t)
        Ahist.append(A.copy())
        if((A[0] > 2978 and (A[0] > 3000 or A[1] < 980))):
            break
    return thist, Ahist

for i in reversed(range(30,50)):
    thist, Ahist = ode_euler(v_0, i*np.pi/180, 8, 60, 0.001)
    plt.plot(thist, Ahist)


print("The code calculates potential angles of 30 to 50 degrees. The upper lines are the x-positions, the middle lines are the y-position, and the bottom two sets of lines are the x- and y-velocities. There is no such angle where the projectile hits the slope in the desired range since the projectile doesn't get near enough to 2978 (approximate nearest x value) while even staying above y = 0")

plt.show()
