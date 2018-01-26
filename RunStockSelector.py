#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jan 15 13:38:16 2018

@author: ethanyoung
"""

import sys
import os
from time import sleep

outFile = "CurrentPicks.txt"
file = open(outFile, "r")
prev = {}
for line in file:
    line = line.split(",")
    if len(line) == 1:
        continue
    value = line[1]
    prev[line[0]] = value[:-1]
    

Command = 'cd /home/pi/Desktop/PortfolioManager/'
os.system(Command)

Command = 'make'
os.system(Command)

Command = './PortfolioManager -nextDay 4000 .15 .025 15'
os.system(Command)

sleep(20)

file = open(outFile, "r")
curr = {}
for line in file:
    line = line.split(",")
    if len(line) == 1:
        continue
    value = line[1]
    curr[line[0]] = value[:-1]

file = open(outFile, "a+")
file.write("\n")

tested = []
for st in prev:
    tested.append(st)
    try:
        print(str(st) + ": " + str(curr[st].strip()) + " - " + str(prev[st].strip()))
        #Today - yesterday
        diff = float(curr[st].strip()) - float(prev[st].strip())
        print("Diff: " + str(diff))
        if (diff > 0):
            file.write("Buy " + str(diff) + " of " + st + "\n")
        elif (diff < 0):
            file.write("Sell " + str(-1 * diff) + " of " + st + "\n")
        else: file.write("No Change for stock " + str(st) + "\n")
    except:
        print(str(sys.exc_info()[0]))
       # file.write("Buy " + curr[st] + " of " + st + "\n")
        
        try:
            float(curr[st].strip())
        except:
            file.write("Sell all of " + str(st) + "\n")

for st in curr:
    if st not in tested:
        file.write("Buy " + str(curr[st].strip()) + " of " + st + "\n")
file.close()
