#This program is used to convert a given amount of seconds to time in hours minutes and seconds

#First, prompt the user for an amount of seconds
sec = int(input('How many seconds would you like to convert to time?\n'))

#Then convert that into hours, minutes, and seconds
hrs = sec/3600
mins = (sec % 3600)/60
secs = ((sec % 3600) % 60)

#Now print the time
print 'The time is %d hours, %d minutes, and %d seconds' % (hrs, mins, secs)


#To make it interesting, display the actual time
#First, import the time module
import time
sec = time.time()

'''The Epoch is set to January 1, 1970 which is 44 years before now. Each day has 86,400 seconds
and every year has 365.25 days. By using these two values, one can discern the number of seconds
in the current year. There are 31557600 seconds in a year.'''
#Change sec from seconds since Epoch to seconds in year then to  seconds in the day
sec = sec % 31557600
sec = sec % 86400

#Then convert that into hours, minutes, and seconds. The Epoch time is 6 hours ahead of Mountain Standard Time
hrs = (sec / 3600) - 6
mins = (sec % 3600)/60
secs = ((sec % 3600) % 60)

#Now print the time
print 'The current time is %d hours, %d minutes, and %d seconds' % (hrs, mins, secs)
