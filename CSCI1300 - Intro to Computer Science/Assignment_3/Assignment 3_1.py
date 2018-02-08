#Raymond Duncan
#Sina Aghli

#This program serves as a dynamic study tool for french vocabulary
import csv, random, os, time

#First, define a function to check all any values that need checking

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

'''
checkValue('i', 'please enter an interger\n')
checkValue('s', 'please enter a string\n')
checkValue('f', 'please enter an float\n')
'''

#Now create a function to ask for multiple choice answer

def multiChoice(options, string): #This function takes a list of possible answers and inputs them into a dictionary
    clearScreen()
    inpt = 1  #First input for the dictionary
    answers = {}
    display = []    #This list has all the values that will be displayed before choosing an answer
    for i in options:
        answers[str(inpt)] = i
        display += [inpt]
        display += [i]
        inpt += 1
    print('%s) %s  '*int((len(display)/2)) %tuple(display)) #Displays options available
    x = int
    while True:
        answer = str(checkValue('i',string))
        if answer in answers:
            x = answers[answer]
            break
        else:
            print('That is not a valid entry. Please try again.')
    return x
    
'''   
options = ['one','two','three','four','five']
print(multiChoice(options))
'''

def Flashcards(): #This is the most important function of the program
    vocab = open('frenchVocab2.csv', 'r')
    vocabDict = {}
    vocabIndex = {}
    for line in vocab: #Creates a dictionary for the words for easier parsing
        datalist = line.split(',')
        vocabIndex[datalist[0]] = datalist[1] #Used to access random nunbers keys for vocabDict later in the program
        vocabDict[datalist[1]] = datalist[2]
    #print(vocabDict)
    end = len(vocabDict)-1 
    limit = int(checkValue('i', '\nHow many flashcards would you like to do?'))
    limit2 = limit  #This is used in the end of the function to calculate the percent of correct answers
    correct_count = 0
    incorrect_count = 0
    while limit > 0:
        options = []
        for i in range(1,5): #Takes values from the word dictionary and makes them options to be used in multiChoice
            inpt = random.randint(1,end)
            key = vocabIndex[str(inpt)] #Acceses the key for the vocabDict
            options.append(key)
        correct = vocabDict[random.choice(options)]
        answer = multiChoice(options, 'What is the meaning of %s'% str(correct))#Checks to see if the user inputs the correct value
        if vocabDict[answer] == correct:
            print('Correct!\n')
            correct_count += 1
        else:
            print('Incorrect\n')
            incorrect_count += 1
        limit -= 1
    answer_ratio = '%g/%g' %(correct_count,incorrect_count) #The next three lines give the user feedback on their performance
    percent_correct = float((correct_count/limit2)*100)
    percent_correct = round(percent_correct, 1)
    print('Your ratio of correct answers to incorrect answers is %s' %answer_ratio)
    print('You got %g%c correct' %(percent_correct,'%'))
    return
    #print(limit, type(limit)) 
    
       
#Flashcards()

def Exit():
    while True:
        answer = checkValue('s','Are you sure you want to exit?\nYes/No?')
        if answer.lower() == 'yes':
            print('\nGoodbye.')
            quit()
        elif answer.lower() == 'no':
            return
        else:            
            print('That is an invalid entry. Please enter a valid value.\n')
    
            
#Exit()

def clearScreen():  #This function is used to clear the screen of all history after a second has passed
    time.sleep(1)
    os.system('cls' if os.name == 'nt' else 'clear')    
    return

'''
for i in range(0,10):
    print(i)    
clearScreen()
'''    

def main(): #Main function
    choices = {'Flashcards':Flashcards, 'Exit':Exit}    #Assigns a string to each function
    menu = ['Flashcards','Exit']
    while True: #Puts the program in an endless loop, which can only be exited using the Exit() function
        choice = multiChoice(menu, 'What would you like to do?')
        choices[choice]()
    
main()
