#This is a program used to calculate simple interest using a principal, number of years, and interest rate given by the user

#First, create variables for the principal (P), number of years (t), and interest rate (r)
P = float(input('What is the starting amount of money? \n'))
t = float(input('For how many years will the interest accrue? \n'))
r = float(input('What is the interest rate? \n'))

#Now perform a check to assure that the variables are equal to the input
print 'P = ', P, '\nt = ', t, '\nr = ', r

#Now that the variables are recorded correctly, input them into a formula to calculate the interest accrued
I = P*t*r/100
print 'The simple interest is: $',I
