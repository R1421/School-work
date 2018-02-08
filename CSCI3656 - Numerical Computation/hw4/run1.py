#!/usr/bin/env python3

def vander_piecewise(x,n=None):
    #Returns a vandermonde matrix with the slopes of the linear piecewise function
    if n is None:
    n = len(x)
    T = numpy.ones((len(x), n))
    if n > 1:
        T[:,1] = x
    for k in range(1,n-1):
        #Make this find the slope between two points
        T[:,k+1] = 2* x * T[:,k] - T[:,k-1]
    return T

def piecewise_linear_interp_and_eval(x,xx):
    #Returns a matrix mapping the values of a function at the points x to the values of the interpolating function at xx
    A = vander_piecewise(x)
    B = vander_piecewise(xx, len(x))
    return B.dot(numpy.linalg.inv(A))

piecewise_linear_interp_and_eval(1,2)
