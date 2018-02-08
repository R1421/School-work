#This is a program that calculates the approximate depth that the water from the Great Lakes would be if it were spread over the contiguous U.S.
#First, the value amount of water in the Great Lakes and the area of the contiguous U.S. should be defined

V = float(22810) # in kilometers cubed
A = float(8080464.3) # in km squared

#Now to convert the values for Volume and Area to meters cubed and squared respectively
V = V * 1000**3
A = A * 1000**2

#Then calculate depth
D = round(V/A, 2)
print 'The depth of the water would be', D
