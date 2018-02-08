#This is a program used to estimate the U.S. population after one year
#The current population is 307,357,870
p = 307357870

#First, calculate the birth rate; br = seconds per birth
br = 7
bps = (1/7)
print("bps %f" % bps)

#Calculate the death rate; dr = seconds per death
dr = 13
dps = float(13**-1)

#Calculate the immigration rate ir = seconds per immigrant
ir = 35
pps = float(35**-1)

#Calculate the amount of seconds per year
spy = 365*24*3600

#Now calculate the number of people in the U.S. after one year
P = int(p + spy*(bps + pps - dps))
print 'The population will be ', P, 'people.'

