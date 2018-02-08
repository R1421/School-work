#Raymond Duncan
#Sina Aghli
#Recitation Section 108

#This first function 'futureValue()' calculates the future value of a savings account that compounds interest monthly
#This function takes three arguments from the user:
#P = the present value of the account
#T = the number of months
#Interest = the interest rate

#This function checkValue is from a previous assignment that I submitted.
#This function runs a check to see if the inputted value is the correct type
def checkValue(varType, string):#varType is the type of variable the function checks for
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

def futureValue():
    P = checkValue('f','Enter a value for the principal amount')
    t = checkValue('f', 'Enter the number of months that the account will be open')
    Interest = checkValue('f','Enter the interest rate associated with the account as a percentage\nOnly enter the number associated with the percentage')
    Interest = float(Interest/100) #This takes the percentage and converts it into a decimal
    
    #Now calculate the interest (F)
    F = P*(1+Interest)**t
    print('The future value of the account is $%g' %round(F,2))
    
#futureValue()


#This next function called 'findName()' takes the index of a name and the number of lines on a page as arguments and returns the page and line number where the mane is found in the phonebook
#The arguments are as follows
#N_name = Nth Name
#NPP = Names per page

def findName():
    N_name = checkValue('i','What is the index of the name you are searching?')
    NPP = checkValue('i','How many names are there on each page?')
    
    #Now to calculate which page and line the name is on
    Page = int(N_name/NPP)
    Line = int(N_name % NPP)#The modulus operator gives the remainder of lines after dividing it by lines per page
    
    #Now to print the answer
    print('The name is on line %d of page %d' %(Line,Page))

#findName()

#The third and final function 'majorHurricanesYears()' takes a file 'HurricaneData_Fall2014.csv' and returns the years when there were more than five major hurricanes
#There are no user inputs needed

def majorHurricanesYears():
    fo = open('HurricaneData_Fall2014.csv','r')
    print('There were more than five major hurricanes in the years:')
    for line in fo:
        line = line.strip('\n') #strips off the line break
        line = line.split(',') #splits the lines
        try:   #First line has strings only, this deals with that         
            if int(line[3]) > 5: #value comparison
                print('%s had %s major hurricanes' % (line[0],line[3]))
        except:
            continue

#majorHurricanesYears()

def main():
    print('Here is the first function, \'futureValue()\'\n')
    futureValue()
    print('\n\nHere is the second function, \'findName()\'\n')
    findName()
    print('\n\nHere is the third function, \'majorHurricanesYears()\'\n')
    majorHurricanesYears()
    print('\nThats all.\n\nThanks!')
    
main()
    
