#!/usr/bin/env python3

import numpy as np

tests = []

@tests.append
class f_exp:
    name = "Exponential"
    def F(x):
        return np.exp(2*x) - 2*x
    def f(x):
        return 2 * np.exp(2*x) - 2

@tests.append
class f_quadratic:
    name = "Quadratic"
    def F(x):
        return x**3/3 - x**2 + 3*x - 1
    def f(x):
        return x**2 - 2*x + 3

@tests.append
class f_tanh:
    name = "H - Tangent"
    def F(x):
        return np.tanh(x)
    def f(x):
        return np.cosh(x)**(-2)

@tests.append
class f_logx2:
    name = "LogX Squared"
    def F(x):
        return np.log(x**2)
    def f(x):
        return 1/x**2 * 2*x



def fint_trapezoid(f, a, b, n=20):
    h = (b-a)/(n-1)
    x = np.linspace(a,b,n)
    fx = f(x)
    fx[[0,-1]] *= .5
    return np.sum(fx)*h

def richardson(I_h, I_2h):
    return I_h + (I_h - I_2h) / 3

def fint_richardson_rec1(f, a, b, r, n=10):
    def recurse(r, n, n2):
        if (r == 0):
            return n, n2
        return recurse(r-1, n2, n2*2-1)
    n1, n2 = recurse(r, n, n*2-1)
    I_h = fint_trapezoid(f, a, b, n2)
    I_2h = fint_trapezoid(f, a, b, n1)
    return richardson(I_h, I_2h)

def fint_richardson_rec2(f, a, b, r, n=10):
    def recurse(r, I_h, I_2h):
        if(r == 0):
            return I_h
        return recurse(r-1, richardson(I_h, I_2h), I_h)
    I_h = fint_trapezoid(f, a, b, n*2-1)
    I_2h = fint_trapezoid(f, a, b, n)
    return recurse(r, I_h, I_2h)

def vander_legendre(x, n=None):
    if n is None:
        n = len(x)
    P = np.ones((len(x), n))
    if n > 1:
        P[:,1] = x
    for k in range(1,n-1):
        P[:,k+1] = ((2*k+1) * x * P[:,k] - k * P[:,k-1]) / (k + 1)
    return P

'''
def legendre_eval(x, n):
    #Compute the nth legendre polynomial and it's derivatives at the points x
    h = 1e-8
    L = vander_legendre(x-h,n)
    R = vander_legendre(x+h,n)
    D = (L-R)/(2*h)
    return sum(D[:,i] for i in range(0, len(x)))
'''
def legendre_eval(x, n):
    #Compute the nth Legendre polynomial and its derivatives at the points x
    eps = 1e-10
    funcs = []
    derivs = []
    for i in range(0,len(x)):
        poly = [1,x[i]]
        poly_l = [1,x[i]-eps]
        poly_r = [1,x[i]+eps]
        for j in range(1,n):
            poly.append(((2*j + 1)*x[i]*poly[j] - j*poly[j-1])/(j+1))
            poly_l.append(((2*j + 1)*(x[i]-eps)*poly_l[j] - j*poly_l[j-1])/(j+1))
            poly_r.append(((2*j + 1)*(x[i]+eps)*poly_r[j] - j*poly_r[j-1])/(j+1))
        #funcs.append(sum(poly))
        #derivs.append(sum(poly_l[jj]-poly_r[jj] for jj in range(0,len(poly_l))))
        funcs.append(poly[-1])
        derivs.append(poly_l[-1]-poly_r[-1])
    return funcs, derivs

def legendre_roots(n):
    #Compute the roots of the nth Legendre polynomial using the initial guess of
    #cos(linspace(.5/(n-1), 1-.5/(n-1), n) * pi)
    xs = np.cos(np.linspace(.5/(n-1), 1-.5/(n-1), n) * np.pi)
    #print(xs)
    fxs, fpxs = legendre_eval(xs,n)
    #print(fxs)
    #print(fpxs)
    
    step = 1e-8
    timeout = 100
    while True:
        print(xs)
        print(fxs)
        print(fpxs)
        converged = True
        for i in range(0, len(fxs)):
            if abs(fxs[i]) > 1e-16:
                converged = False
            if fpxs[i] != 0:
                xs -= step*fxs[i]/fpxs[i]
        if converged or all(i == 0 for i in fpxs): break
        timeout -= 1
        if timeout == 0: 
            print("TIMEOUT: MAX LOOPS REACHED")
            break
        fxs, fpxs = legendre_eval(xs,n)
        print()
    return xs




#for t in tests:
#    for r in [1,3,5,10,20]:
#        print(fint_richardson_rec1(t.f, 0, 5, r))
        
#print(legendre_eval(np.linspace(0,5,5),10))
#print(legendre_roots(5))

a=-1
b=1
for t in tests:
    for n in [10,20,30,50]:
        print("%s\tRichardson\t%d\t%f" % (t.name, n, fint_richardson_rec1(t.f,a,b,10,n) - (t.F(b)-t.F(a))))
