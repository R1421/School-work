#!/usr/bin/env
#Raymond Duncan
#Sina Aghli
#Assignment 6

#Import the sys and geopy modules
import sys
from geopy.geocoders import OpenMapQuest
from geopy.distance import vincenty

geolocator = OpenMapQuest()

#Assign variable name for terminal argument
#locations = 'cityList.txt'
locations = sys.argv[1]

def Greedy_Search(locations):
    fo = open(locations,'r') #Open the file and read each line as a different location
    locationList = []
    for line in fo:
        line = line.strip('\n')
        line = line.strip('\r')
        locationList += [line]
    fo.close()  
     
    #print locationList
    
    startLocation = locationList[0] #Remove start from list after creating related variable
    del locationList[0]
    
    #Create list for ordered locations, and ordered distances. Then variable for current location
    locationsOrdered = [startLocation]
    distancesOrdered = []
    currentLocation = startLocation
    
    while True: #Order locations by distance
        if len(locationList) == 0:
            address2, (lat2,long2) = geolocator.geocode(startLocation)
            dist = vincenty((lat1, long1), (lat2, long2)).miles
            locationsOrdered += [startLocation]
            distancesOrdered += [dist]
            break
        address1, (lat1,long1) = geolocator.geocode(currentLocation)
        minDist = []
        #print currentLocation
        for i in locationList:
            #print i
            address2, (lat2,long2) = geolocator.geocode(i)
            dist = vincenty((lat1, long1), (lat2, long2)).miles #Measures distance
            #print dist
            try:        #If there is no distance established, it will establish a distance. Otherwise, it will compare distances
                if dist < minDist[1]:
                    minDist = [i,dist]
            except:
                minDist = [i,dist]
            #print maxDist 
        currentLocation = minDist[0] #Resets the current location
        locationsOrdered += [minDist[0]]
        distancesOrdered += [minDist[1]]
        locationList.remove(minDist[0])
        #print locationsOrdered
        #print distancesOrdered
    print locationsOrdered
    #print distancesOrdered
    print sum(distancesOrdered)    
    

        
def main(locations):
    Greedy_Search(locations)
        
main(locations)
