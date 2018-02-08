#!/usr/bin/env	python3
#Raymond Duncan 
#Sina Aghli
#Assignment 4

def CreateDictionary():
    fo = open('textToEnglish2014.csv','r')
   
    myDict = {}
    for line in fo:
        #print(line)
        line = line.strip('\n')
        #print(line)
        
        datalist = line.split(',')
        myDict[datalist[0]] = datalist[1]
    return myDict
        
    #print(myDict)
    
#CreateDictionary()

def main():
    loop = True
    while loop == True:
        myDict = CreateDictionary()
        search = str(input('Please enter a set of words to search, separated by a space.\nEnter \'q\' to quit\n'))
        searchList = search.split(' ')
        for word in searchList:
            if word in myDict:
                print('%s translates to: %s' %(word,myDict[word]))
            elif word == 'q':
                loop = False
            else:
                print('%s translates to: NF')
    
main()        
