#Raymond Duncan
#Sina Aghli
#This program counts the number of lines in every python file in the current directory, not including this file

import glob
file_list = []
file_list = glob.glob('*.py')
#print(file_list)

file_list.remove('parse.py')
print('These are the python files in the current directory:')
print('%s\n'*len(file_list) %tuple(file_list))

for i in file_list:
    print('')
    line_count = 0
    #char = str
    f = open(i,'r')
    for line in f:
        for character in line:
            if character == '#':
                break
            elif character.lower() in 'abcdefghijklmnopqrstuvwxyz':
                #char = character
                line_count += 1
                break
        #print(char)
    print('There are %d lines in %s' %(line_count,i))
        
        
