#!/usr/bin/python

# Snippet 2 created for CSCI 3308 Lab 10 by: kaoudis@colorado.edu

# A simple state-change-powered directory event logger.
# for initial run:
#    $ chmod +x snippet2.py && ./snippet2.py
# As JSON files are added to the input directory (or wherever path points) output will change.
# It is assumed all inputs are proper JSON. If this is not the case, the code observing inputs should be changed.

from ast import literal_eval
from sys import exit
from os import listdir
import time

class observer:
    interval = 1
    before = {}

    def __init__(self):
        # where should our path variable lead to? todo: figure it out
        self.before = dict([(json, None) for json in listdir(self.path)])
        print("Watching "+self.path+" for JSON alerts...")

    def run(self):
        avg = 0; door = 0; alarm = 0; img = 0

        #check for new things in the directory <path>
        state_change = dict([(json, time.time()) for json in listdir(self.path) if json])
        new = [json for json in state_change if not json in self.before or state_change]

        if new:
            f = open(self.path+'/'+new[0], 'r')
            showme = literal_eval(f.read())

            self.before[new[0]] = start # new state is now current state

            start = time.time() # what am I timing? where should this go?

            #check alarm type
            if showme['Type'] == 'alarm':
                alarm = alarm + 1
            if showme['Type'] == 'Door':
                door = door + 1
            if showme['Type'] == 'img':
                img = img + 1

            finish = time.time()
            avg = finish - start

        print("DoorCnt: "+str(door)+" ImgCnt: "+str(img)+" AlarmCnt: "+str(alarm)+" AvgProcessingTime: "+str( round(avg, 5) ) )
        #time.sleep(self.interval) todo: look up the sleep function?

## the below runs this stuff, I know there's a way to do this nicely but I forgot ##
watch = observer()

while True:
    watch.run()

