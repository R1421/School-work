#These functions are practice for the second midterm
import sys


#First, is a function that displays the max value of the two inputted integers
def getMax(int1, int2):
    if int1 > int2:
        return int1
    elif int1 == int2:
        return 'The two values are the same'
    else:
        return int2
        
#Second, is a function that performs the getMax function with a list of values
def getMaxList(myList):
    maxValue = int()
    for item in myList:
        try:
            if item > maxValue:
                maxValue = item
        except:
            maxValue = item
    return maxValue
            
#Third is a function which takes a list of superheroes and returns a list of superheroes with one word as their names
def getHeroFirstNames(superheroes):
    for item in superheroes:
        if ' ' in item:
            superheroes.remove(item)
    return superheroes
    
#Fourth is a function which prints the keys and corresponding values for a dictionary
def printDictionary(dictionary):
    for x in dictionary:
        print x, dictionary[x]

#Fifth is a function that takes a firstname and a lastname and returns a string with the first character of the first name and the first three characters of the last mane
#This function should chech to make sure that the last name is three letters and if not it uses the entire last name
def getUserName(firstname, lastname):
    first = firstname[0]
    if len(lastname) >= 3:
        last = lastname[:3]
    else:
        last = lastname
    username = first+last
    return username
    
#The last function before the main takes a dictionary name, a key, and a new value for the key
#The function should return the updated dictionary, and return 'Key not found' if the key doesn't exist
def updateDictionary(dictionary,key,value):
    if key in dictionary:
        dictionary[key] = value
    else:
        print 'Key not found'
    return dictionary
        
#This function is an add in, from a previous assignment, which checks the value type of the inputted values
def checkValue(varType, string = ' '):#varType is the type of variable the function checks for
    var = input('%s\n'%string)
    if varType == 's':#checks if the variable is a string
        return var
    elif varType == 'i':#checks if the variable is an int
        try:
            var = int(var)
            return var
        except:
            print('The value you entered is not an int')
            var = checkValue('i', string)
    elif varType == 'f':#checks if the variable is a float
        try:
            var = float(var)
            return var
        except:
            print('The value you entered is not a float')
            var = checkValue('f', string)
    
    return var
    #print(var,type(var))
        
def main():
    #Call getMax
    int1 = sys.argv[1]
    int2 = sys.argv[2]
    try:
        int1 = int(int1)
    except:
        int1 = checkValue('i', 'The value you entered for integer 1 is not an integer')
    try:
        int2 = int(int2)
    except:
        int2 = checkValue('i', 'The value you entered for integer 2 is not an integer')
    print getMax(int(int1), (int2))
    
    #Call getMaxList
    myList = [1,2,5,8,3,46,91,55,2]
    print getMaxList(myList)
    
    #call getHeroFirstName
    superheroes = ['Superman', 'Wonder woman', 'Green lantern', 'Spiderman', 'Batman', 'Ironman', 'Black Panther']
    print getHeroFirstNames(superheroes)
    
    #call printDictionary
    dictionary = {'First':1, 'Second':2, 'Third':3, 'Fourth':4, 'Fifth':5}
    printDictionary(dictionary)
    
    #call getUsername
    firstname = 'Raymond'
    lastname = 'Duncan'
    print firstname, lastname
    print getUserName(firstname, lastname)
    
    
    #call update Dictionary
    updateDictionary(dictionary, 'First', 'uno')
    printDictionary(dictionary)
    
main()
