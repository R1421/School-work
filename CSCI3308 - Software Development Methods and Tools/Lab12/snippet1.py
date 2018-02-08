#!/usr/bin/python

# Snippet 1 created for CSCI 3308 Lab 10 by: kaoudis@colorado.edu

# A simple state-change-powered directory event logger.
# for initial run:
#    $ chmod +x snippet1.py && ./snippet1.py
# As JSON files are added to the input directory (or wherever path points) output will change.
# It is assumed all inputs are proper JSON. If this is not the case, the code observing inputs should be changed.

from ast import literal_eval
from sys import exit
from os import listdir
import time

class o:
    i = 1; b = {}
    def __init__(self):
        self.p = "/home/user/path/to/input"
        self.b = dict([(j, None) for j in listdir(self.p)])
    def cp(self, new_p):
        self.p = new_p
    def ci(self, new_i):
        self.i = new_i
    def r(self):
        av = 0; d = 0; a = 0; i = 0
        sc = dict([(j, time.time()) for j in listdir(self.p)])
        new = [j for j in sc if not j in self.b]
        if new:
            st = time.time()
            f = open(self.path+'/'+new[0], 'r')
            sh = literal_eval(f.read())
            f.close()
            self.b[new[0]] = st
            if sh['Type'] == 'alarm':
                a = a + 1
            if sh['Type'] == 'Door':
                d = d + 1
            if sh['Type'] == 'img':
                i = i + 1
            fin = time.time()
            av = fin - st
        #print("DCnt: "+str(d)+" ICnt: "+str(i)+" ACnt: "+str(a)+" AvgPT: "+str( round(av, 5) ) )
        time.sleep(self.i)
    def s(self):
        exit(0)

if __name__ == '__main__':
    w = o()
    try:
        while True:
            w.r()
    except KeyboardInterrupt:
        w.s()

