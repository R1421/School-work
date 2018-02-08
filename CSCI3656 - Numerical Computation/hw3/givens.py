#!/usr/bin/env python3

import numpy as np

def givens_rot(theta,v,x):
    m,n = x.shape
    G_theta = np.matrix([np.cos(theta),np.sin(theta)],[-np.sin(theta),np.cos(theta)])
    norm_v = (sum((i)**2 for i in v))**.5
    Ut = np.matrix([[1]+[0 for i in range(m-1)],[0]+[x/norm_v for x in v]])
    return Ut.T(G_theta * Ut.dot(x) - Ut.dot(x))

def givens_rot2(theta,X):
    m,n = X.shape
    G_theta = np.matrix([[np.cos(theta),np.sin(theta)],[-np.sin(theta),np.cos(theta)]])
    R = X.copy()
    for i in range(n-1):
        U = np.eye(m-i,2)
        U[i+1:,i] = R[i+1:,i].ravel()
        R[i:,i:] = (np.eye(m-i,m-i) + U*(G_theta-np.eye(2,2))*U.T)*R[i:,i:]
    return R

def givens_rot3(X):
    m,n = X.shape
    R = X.copy()
    for i in range(n-1):
        x = R[i:,i]
        v = x[1:,0]
        U = np.eye(m-i,2)
        U[1:,1] = v.ravel()/np.linalg.norm(v)
        theta = np.arctan2(np.linalg.norm(v),x[0])
        G = np.matrix([[np.cos(theta),np.sin(theta)],[-np.sin(theta),np.cos(theta)]])
        R[i:,i:] = (np.eye(m-i,m-i) + U*(G-np.eye(2,2))*U.T)*R[i:,i:]
    return R

def givens_Q_times(V,x):
    y = x.copy()
    for i in reversed(range(len(V))):
        G = np.matrix([[np.cos(V[i][1]),np.sin(V[i][1])],[-np.sin(V[i][1]),np.cos(V[i][1])]])
        U = np.eye(len(V[i][0])+1,2)
        U[1:,1] = V[i][0].ravel()
        y[i:] = (np.eye(len(V[i][0])+1) + U*(G.T-np.eye(2,2))*U.T).dot(y[i:])
    return y

def givens_qr(A):
    m,n = A.shape
    R = A.copy()
    V = []
    for i in range(n-1):
        x = R[i:,i]
        v = x[1:]/np.linalg.norm(x[1:])
        U = np.eye(m-i,2)
        U[1:,1] = v.ravel()
        theta = np.arctan2(np.linalg.norm(x[1:]),np.linalg.norm(x[0]))
        G = np.matrix([[np.cos(theta),np.sin(theta)],[-np.sin(theta),np.cos(theta)]])
        R[i:,i:] = (np.eye(m-i,m-i) + U*(G-np.eye(2,2))*U.T)*R[i:,i:]
        V.append((v,theta))
    return givens_Q_times(V,np.eye(m,n)),R

def userPrompt():
    while(True):
        ans = input("Enter y or n:  ")
        if(ans == 'y' or ans == 'n'): break
        print("Invalid input")
    if(ans == 'y'): return True
    else: return False


def calculateError(m):
    print("Error calculations for Vandermonde matrix with m=%d" % m)
    x = np.linspace(-1,1,m)
    A = np.vander(x)
    nQ,nR = np.linalg.qr(A)
    print("Numpy's implementation of qr factorization gets the following values:")
    print("--- NumpyQ ---")
    print(nQ)
    print("\n--- NumpyR ---")
    print(nR)

    Q,R = givens_qr(A)
    print("My implementation fo qr factorization gets these values:")
    print("--- MyQ ---")
    print(Q)
    print("\n--- MyR ---")
    print(R)

    print("\nThe errors in my implementation are:")
    print("--- Error in Q ---")
    eQ = nQ-Q
    print(eQ)
    print("\n--- Error in R ---")
    eR = nR-R
    print(nR-R)
    print("\n\n")

def calculateError2(m):
    x = np.linspace(-1,1,m)
    A = np.vander(x)
    Q,R = givens_qr(A)
    print("Error calculations for Vandermonde matrix with m=%d" % m)
    print("Error in QR = A")
    errorQRA = A-Q.dot(R)
    normQRA = np.linalg.norm(errorQRA)
    print("The norm of the error matrix is %f\nWould you like to see the error matrix?" % normQRA)
    if(userPrompt()): print(errorQRA)

    print("\n\nError in Q.T * Q = I")
    errorQQI = np.eye(Q.shape[0]) - Q.T.dot(Q)
    normQQI = np.linalg.norm(errorQQI)
    print("The norm of the error matrix is %f\nWould you like to see the error matrix?" % normQQI)
    if(userPrompt()): print(errorQQI)
    print("\n\n")



calculateError2(10)
calculateError2(20)
