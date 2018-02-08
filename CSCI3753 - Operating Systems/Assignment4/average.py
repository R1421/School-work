#!/usr/bin/python3

import subprocess
import time
import sys

filename = "test-predict"
runs = 25

print("Starting Analysis with {} runs...".format(runs))

ls = []

for i in range(runs):
    t = float(subprocess.check_output(["bash","-c","./"+filename+" 2> >(tr = '\n' | tail -n1)"]))
    ls.append(t)
    print(i, end=" ")
    sys.stdout.flush()
    time.sleep(.5)

big = max(ls)
mean = sum(ls)/runs
sml = min(ls)

class colors:
    END = '\033[0m'
    BAD = '\033[91m'
    MED = '\033[93m'
    GOOD = '\033[92m'

if(big > 0.16):
    bcolor = colors.BAD
elif(big > 0.02):
    bcolor = colors.MED
else:
    bcolor = colors.GOOD

if(mean > 0.16):
    mcolor = colors.BAD
elif(mean > 0.02):
    mcolor = colors.MED
else:
    mcolor = colors.GOOD

if(sml > 0.16):
    scolor = colors.BAD
elif(sml > 0.02):
    scolor = colors.MED
else:
    scolor = colors.GOOD


print("")
print(scolor + "Worst Time:\t{}".format(max(ls)) + colors.END)
print(mcolor + "Average Time:\t{}".format(sum(ls)/runs) + colors.END)
print(bcolor + "Best Time:\t{}".format(min(ls)) + colors.END)
