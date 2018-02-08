#!/usr/bin/env python3

model = open('model.txt', "r")
pred = open('pred.txt', "r")

STATES = ['AL','AK','AZ','AR','CA','CO','CT','DE','DC','FL','GA','HI','ID','IL','IN','IA','KS','KY','LA','ME','MD','MA','MI','MN','MS','MO','MT','NE','NV','NH','NJ','NM','NY','NC','ND','OH','OK','OR','PA','RI','SC','SD','TN','TX','UT','VT','VA','WA','WV','WI','WY']
modlst = []
predlst = []
for line in model:
    a,b = line.split()
    if(a in STATES):
        modlst.append(float(b))

for line in pred:
    a,b = line.split()
    if(a in STATES):
        predlst.append(float(b))

model.close()
pred.close()

print(sum((modlst[i]-predlst[i])**2 for i in range(0,50))/50)
