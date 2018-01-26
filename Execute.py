#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jan 15 13:38:16 2018

@author: ethanyoung
"""
import pause
import datetime
import os
from time import sleep
#while True:
#pause.days(1)
print("cd /home/pi/Desktop/PortfolioManager")
Command = 'cd /home/pi/Desktop/PortfolioManager'
os.system(Command)

print('python3 ExtractData.py')
Command = 'python3 ExtractData.py'
os.system(Command)

print('python3 FormatData.py')
Command = 'python3 FormatData.py'
os.system(Command)

print('python3 RunStockSelector.py')
Command = 'python3 RunStockSelector.py'
os.system(Command)

sleep(30)

print("python3 SendEmail.py -a 'Stocks to select today'")
Command = "python3 SendEmail.py -a 'Stocks to select today'"
os.system(Command)


    
