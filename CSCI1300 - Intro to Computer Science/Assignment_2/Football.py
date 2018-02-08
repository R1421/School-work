'''
This program is used to calculate a quarterback's passer rating based on:
    Pass Attempts
    Pass Completions
    Total Passing Yards
    Touchdowns
    Interceptions
'''

#First, cast variables and ask for inputs
loop = True
while (loop == True): #This loop will repeat until float values are given for each of the inputs
    list_1 = []
    att = input('How many pass attempts?\n')
    com = input('How many completions?\n') 
    yds = input('How many yards?\n')
    tdn = input('How many touchdowns?\n')
    itc = input('How many interceptions?\n')
    
    list_1 = [att, com, yds, tdn, itc] #Enters user values into a list for easier checking
    
    for i in list_1:
        try:
            i = float(i)
        except:
            print('One or more value(s) are invalid. Please enter valid values')
            break
        #print(i, type(i))
        loop = False

#Convert each of the values into ratios of attribute per attempt
#in order, list_2 has values for completions per, yards per, touchdowns per, and interceptions per attempt
list_2 = []

del list_1[0]
for i in list_1:
    x = float(float(i)/float(att))
    list_2 += [x]
   # print(list_2)

#Now for some calculations
C = float((list_2[0] - .3)*5)
Y = float((list_2[1] - 3)*.25)
T = float(list_2[2] * 20)
I = float(2.375 - (list_2[3] * 25))

list_3 = [C,Y,T,I]
for i in list_3:
    if i < 0:
        i = 0
    elif i > 2.375:
        i = 2.375
rating = (sum(list_3)/6 * 100)
#print(rating)

#Quarterback evaluation
if rating <= 85:
    print('This player has a poor rating of %g' % (rating))
elif rating > 85 and rating <= 90:
    print('This player has a mediocre rating of %g' % (rating))
elif rating > 90 and rating <= 95:
    print('This player has a good rating of %g' % (rating))
else:
    print('This player has a great rating of %g' % (rating))
