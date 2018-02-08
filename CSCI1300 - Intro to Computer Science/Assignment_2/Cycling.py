#This program calculates the amount of power (measured in watts) required when riding a bike
loop = True
while (loop == True): #This loop will repeat until float values are given for each of the inputs
    list_1 = []
    M = input('What is the mass of the rider in kg?\n')
    Mb = input('What is the mass of the bike in kg?\n') 
    v = input('With what velocity is the biker traveling in meters per second?\n')
    #Cd = input('What is the drafting coefficient?\n')
    d = input('For what distance did the biker ride in kilometers?\n')
    
    
    list_1 = [M, Mb, v, d] #Enters user values into a list for easier type checking
                            #The value for Cd was deleted in the list
    for i in list_1:
        try:
            i = float(i)
        except:
            print('One or more value(s) are invalid. Please enter valid values')
            break
        #print(i, type(i))
        loop = False
    
#These are some constant values for gravity, rider position coeficient, and rolling friction
g = 9.8#meters per second squared
k = .18
Cr = .001

#Re-establish input variables as floats
M = float(list_1[0])
Mb = float(list_1[1])
v = float(list_1[2])
#Cd = float(list_1[3])
d = float(list_1[3])

import random


#Here is the calculation for time needed to travel the inputed distance at a constant velocity, and the calculation of total energy required
secs = (d * 1000)/v# in seconds
#Convert time into minutes
mins = int(secs/60)
#print(mins)

E_list = [] #List of energy outputs per minute

for i in range(0,mins):
    #Set a value for the drag coefficient
    Cd = random.uniform(.5,1.0)
    #print(Cd)
    #Now calculate the power from drag, rolling friction, and total friction respectively
    P_air = k * Cd * v**3
    P_roll = Cr * g * (M + Mb) * v
    P_minute = P_air + P_roll
    
    E_minute = round((P_minute * 60)/1000, 0)
    E_list += [E_minute]
    E_total = sum(E_list)
    print('The total energy at %d minutes is %d kJ' %(i+1, E_total))
    
E_avg = int(E_total/mins)
print('The average energy is approximately %d kJ' %(E_avg))

#print('''The total power required is: %g Watts
#The total energy required to travel %g kilometers is %g Joules''' %(P_total, d, E_total))
