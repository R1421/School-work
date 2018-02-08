#Raymond Duncan
#Sina Aghli
#CSCI 1300-100
#Python 2.7

#First import needed modules
import sys
firstname = sys.argv[1]
lastname = sys.argv[2] #These take the firstname and lastname given in the terminal to be used in main

def main(firstname, lastname):
    print "Midterm 2 for %s %s" %(firstname, lastname)
    myList = [1,2,5,8,4,3,6]
    print 'The original list is:\n', myList
    print 'The new list is:\n', swapItems(myList, 1, 5)
    number = int(raw_input("\nPlease enter a number to factor.\n"))
    print commonDivisors(number)
    
    


'''The first function is called swapItems and it takes three arguments.
One item is a list, the other two items are words to search for in the list.
If the items are in the list, swap the position of the two items and return the new list.
'''


def swapItems(myList, item1, item2):

    if item1 and item2 in myList:
        myListNew = []
        for i in myList:
            if i == item1:
                myListNew += [item2]
            elif i == item2:
                myListNew += [item1]
            else:
                myListNew += [i]
        
    return myListNew

        
'''The second function is called common Divisors and it takes a number and returns a list of factors greater than one.
The function does not need to handle error checking.'''
def commonDivisors(number):
    factorList = []
    for i in range(2,number-1):
        if number % i == 0:
            factorList += [i]
    if len(factorList) > 0:
        return factorList
    else:
        return 'Number is prime'
        
main(firstname, lastname)
        
        

