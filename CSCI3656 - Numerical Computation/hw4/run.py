#!/usr/bin/env python3

import numpy as np

def piecewise_linear_interp_and_eval(x, xx):
    n = len(x) - 1
    def s_interp(y):
        perm = np.argsort(x)
        xs = x[perm]
        ys = y[perm]
        delta = xs[1:] - xs[:-1]
        Delta = ys[1:] - ys[:-1]
        
        # Assemble tridiagonal system (this can be optimized)
        S = np.zeros((n, 3))    # Matrix to hold splines as [xs,b,a]
        S[:,0] = xs[:-1]                                  # Sorted interval left ends
        S[:,2] = ys[:-1]                                  # Interpolation property
        S[:,1] = Delta/delta
        return S
    def s_eval(S, xx):
        left = S[:,0].searchsorted(xx) - 1
        left[left<0] = 0 # Use the leftmost interval even if xx<=x
        f = np.zeros_like(xx)
        for i,t in enumerate(xx):
            f[i] = np.polyval(S[left[i],1:], xx[i] - S[left[i],0])
        return f
    
    # Build an explicit matrix for the spline fit evaluated at xx
    A = np.zeros((len(xx), len(x)))
    for i,e in enumerate(np.eye(len(x), len(x))):
        S = s_interp(e)
        A[:,i] = s_eval(S, xx)
    return A

def cosspace(a, b, n=50):
    return (a + b)/2 + (b - a)/2 * (np.cos(np.linspace(0, np.pi, n)))

def vander_chebyshev(x, n=None):
    if n is None:
        n = len(x)
    T = np.ones((len(x), n))
    if n > 1:
        T[:,1] = x
    for k in range(1,n-1):
        T[:,k+1] = 2* x * T[:,k] - T[:,k-1]
    return T

def chebyshev_interp_and_eval(x, xx):
    """Matrix mapping from values at points x to values
    of Chebyshev interpolating polynomial at points xx"""
    A = vander_chebyshev(x)
    B = vander_chebyshev(xx, len(x))
    return B.dot(np.linalg.inv(A))

def nth_error(interp_and_eval, f, xspace, interval, eps):
    n = 2
    xx = np.linspace(-1,1,100)
    while(True):
        x = xspace(*interval,n)
        A = interp_and_eval(x, xx)
        err = np.linalg.norm(A.dot(f(x)) - f(xx), np.inf)
        if(err <= eps): break
        n += 1
        if(n > 100):
            n = -1
            break
    return n, err
            
def func1(x):
    return np.exp(-16*x**2)

def func2(x):
    return np.abs(x)
    

x1 = np.linspace(-1,1,20)
x2 = cosspace(-1,1,20)
xx = np.linspace(-1,1,100)
f = piecewise_linear_interp_and_eval
print("piecewise_linear linspace -> linspace: norm=%e" % (np.linalg.norm(f(x1,xx))))
print("piecewise_linear cosspace -> linspace: norm=%e" % (np.linalg.norm(f(x2,xx))))

f = chebyshev_interp_and_eval
print("chebyshev linspace -> linspace: norm=%e" % (np.linalg.norm(f(x1,xx))))
print("chebyshev cosspace -> linspace: norm=%e" % (np.linalg.norm(f(x2,xx))))


n,e = nth_error(piecewise_linear_interp_and_eval, func1, np.linspace, (-1,1), 1e-4)
print("piecewise_linear f() linspace -> linspace: n=%d max_error=%e" % (n,e))
n,e = nth_error(piecewise_linear_interp_and_eval, func1, cosspace, (-1,1), 1e-4)
print("piecewise_linear f() cosspace -> linspace: n=%d max_error=%e" % (n,e))

n,e = nth_error(piecewise_linear_interp_and_eval, func2, np.linspace, (-1,1), 1e-2)
print("piecewise_linear g() linspace -> linspace: n=%d max_error=%e" % (n,e))
n,e = nth_error(piecewise_linear_interp_and_eval, func2, cosspace, (-1,1), 1e-2)
print("piecewise_linear g() cosspace -> linspace: n=%d max_error=%e" % (n,e))
