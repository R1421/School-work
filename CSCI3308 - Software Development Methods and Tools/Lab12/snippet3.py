#!/usr/bin/python

# Snippet 3 created for CSCI 3308 Lab 10 by: kaoudis@colorado.edu

# A simple state-change-powered directory event logger.
# for initial run:
#    $ chmod +x snippet3.py && ./snippet3.py
# As JSON files are added to the input directory (or wherever path points) output will change.
# It is assumed all inputs are proper JSON. If this is not the case, the code observing inputs should be changed.

from ast import literal_eval
from sys import exit
from os import listdir
import time

class observer:
    interval = 1 #sleep 1 second between checks
    before = {}

    def __init__(self):
        self.path = "/home/kelly/Development/Git/coding_exercise/input"
        self.before = dict([(json, None) for json in listdir(self.path)])
        print("Watching "+self.path+" for JSON alerts...")

    def change_path(self, new_path):
        self.path = new_path

    def change_interval(self, new_interval):
        self.interval = new_interval

    def run(self):
        avg = 0; door = 0; alarm = 0; img = 0

        #check for new things in the directory <path>
        state_change = dict([(json, time.time()) for json in listdir(self.path)])
        new = [json for json in state_change if not json in self.before]

        if new:
            start = time.time()

            f = open(self.path+'/'+new[0], 'r')
            showme = literal_eval(f.read())
            f.close()
            self.before[new[0]] = start # new state is now current state

            #check alarm type
            if showme['Type'] == 'alarm':
                alarm = alarm + 1
            if showme['Type'] == 'Door':
                door = door + 1
            if showme['Type'] == 'img':
                img = img + 1

            finish = time.time()

            #according to the directions avg should be for the time interval (one second) not for total processing
            avg = finish - start

        print("DoorCnt: "+str(door)+" ImgCnt: "+str(img)+" AlarmCnt: "+str(alarm)+" AvgProcessingTime: "+str( round(avg, 5) ) )
        time.sleep(self.interval)

    def stop(self):
        print(" ")
        print("Finished watching for alerts!")
        exit(0)


if __name__ == '__main__':
    watch = observer()

    try:
        while True:
            watch.run()
    except KeyboardInterrupt:
        watch.stop()

