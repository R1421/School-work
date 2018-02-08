#!/usr/bin/env python3
import math
import numpy

acc = 1e-8

def initEquations():
    equations = {
            "Cubic":('x**3','3*x**2','6*x'),
            "Quadratic":('x**2','2*x','2'),
            "Linear":('2*x+2','2','0'),
            "Exponential":('math.exp(x)','math.exp(x)','math.exp(x)'),
            "Arctan":('math.atan(x)','1/(x**2+1)','-2*x/(x**2+1)**2'),
            "Log":('math.log(x)','1/x','-1/x**2'),
            "Cube Root":('abs(x)**(1/3)*numpy.sign(x)','x/(3*abs(x)**(5/3))','2*x**2/(9*abs(x)**(11/3))'),
            "XCOSX":('(x-1)*math.cos(x-1)','(x-1)*math.sin(1-x)+math.cos(1-x)','2*math.sin(1-x)-(x-1)*math.cos(1-x)'),
            "XCOSX2":('x*math.cos(x)+1','math.cos(x)-x*math.sin(x)','-2*math.sin(x)-x*math.cos(x)')
            }
    return equations

def newtonStep(f,ff,x):
    try:
        fx = eval(f)
    except ZeroDivisionError:
        fx = math.inf
    try:
        ffx = eval(ff)
    except ZeroDivisionError:
        ffx = math.inf
    if(ffx == 0 or fx == math.inf or ffx == math.inf): return
    return x-fx/ffx

def newton(eqn,x):
    n = eqn[0]
    f = eqn[1][0]
    ff = eqn[1][1]
    x0 = x
    i = 0
    resid = abs(eval(f))
    print('%s\t%d\t%f\t%f' % (n,i,x,resid))
    while(resid > acc):
        x = newtonStep(f,ff,x)
        if(x is None): break
        resid = abs(eval(f))
        i += 1
        print('%s\t%d\t%f\t%f' % (n,i,x,resid))

def newtonStepls(f,ff,x):
    try:
        fx = eval(f)
    except ZeroDivisionError:
        fx = math.inf
    try:
        ffx = eval(ff)
    except ZeroDivisionError:
        ffx = math.inf
    if(ffx == 0 or fx == math.inf or ffx == math.inf): return
    scales = [8,4,2,1,0.5,0.25,0.125]
    resids = []
    xs = []
    x0 = x
    for s in scales:
        x = x0-s*fx/ffx
        xs.append(x)
        resids.append(abs(eval(f)))
    i = resids.index(min(resids))
    return xs[i]

def newtonls(eqn,x):
    n = eqn[0]
    f = eqn[1][0]
    ff = eqn[1][1]
    i = 0
    resid = abs(eval(f))
    print('%s\t%d\t%f\t%f' % (n,i,x,resid))
    while(resid>acc):
        x = newtonStepls(f,ff,x)
        if(x is None): break
        resid = abs(eval(f))
        i += 1
        print('%s\t%d\t%f\t%f' % (n,i,x,resid))

def quadraticMinus(a,b,c):
    return (-b-math.sqrt(b**2-2*a*c))/a

def quadraticPlus(a,b,c):
    return (-b+math.sqrt(b**2-2*a*c))/a

def cubicStep(f,ff,fff,x):
    try:
        fx = eval(f)
    except ZeroDivisionError:
        fx = math.inf
    try:
        ffx = eval(ff)
    except ZeroDivisionError:
        ffx = math.inf
    try:
        fffx = eval(fff)
    except ZeroDivisionError:
        fffx = math.inf
    if(fffx==0 or 2*fx*fffx>ffx**2): return
    if(fx == math.inf or ffx == math.inf or fffx == math.inf): print('Case 2'); return

    #Return the left and right approximation
    return (x+quadraticPlus(fffx,ffx,fx),x+quadraticMinus(fffx,ffx,fx))


def cubic(eqn,x):
    n = eqn[0]
    f = eqn[1][0]
    ff = eqn[1][1]
    fff = eqn[1][2]
    x0 = x
    i = -1

    xs = [x0]
    for xCurr in xs:
        xPlus = cubicStep(f,ff,fff,xCurr)
        if(xPlus is None):
            xPlus = newtonStepls(f,ff,xCurr)
            if(xPlus is None): break
            xs.append(xPlus)
        else:
            xs.append(xPlus[0])
#            xs.append(xPlus[1])
        x = xCurr
        resid = abs(eval(f))
        i += 1
        print('%s\t%d\t%f\t%f' % (n,i,x,resid))
        if(resid <= acc): break
        if(i == 1000): break
#    print('%s\t%d\t%f\t%f' % (n,i,x,resid))


print("Imported functions.py")
