#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jan 15 13:38:16 2018

@author: ethanyoung
"""

from alpha_vantage.timeseries import TimeSeries
import sys
import csv
import os
from time import sleep

#Got rid of ctxs, NWSA
stocks = ['MMM','ABT','ABBV','ACN','ATVI','AYI','ADBE','AAP','AES','AET','AMG','AFL','A','APD','AKAM','ALK','ALB',
'ALXN','ALLE','AGN','ADS','LNT','ALL','GOOGL','GOOG','MO','AMZN','AEE','AAL','AEP','AXP','AIG','AMT','AWK','AMP','ABC','AME',
'AMGN','APH','APC','ADI','ANTM','AON','APA','AIV','AAPL','AMAT','ADM','ARNC','AJG','AIZ','T','ADSK','ADP','AN','AZO','AVB','AVY','BHI','BLL','BAC','BCR','BAX',
'BBT','BDX','BBBY','BRK.B','BBY','BIIB','BLK','HRB','BA','BWA','BXP','BSX','BMY','AVGO','CHRW','CA','COG',
'CPB','COF','CAH','KMX','CCL','CAT','CBOE','CBG','CBS','CELG','CNC','CNP','CTL','CERN','CF','SCHW','CHTR','CHK','CVX','CMG','CB','CHD','CI','XEC',
'CINF','CTAS','CSCO','C','CFG','CME','CMS','COH','KO','CTSH','CL','CMCSA','CMA','CAG','CXO','COP','ED','STZ','GLW','COST',
'COTY','CCI','CSRA','CSX','CMI','CVS','DHI','DHR','DRI','DVA','DE','DLPH','DAL','XRAY','DVN','DLR','DFS','DISCA','DISCK','DG',
'DLTR','D','DOV','DOW','DPS','DTE','DD','DUK','DNB','ETFC','EMN','ETN','EBAY','ECL','EIX','EW','EA','EMR','ETR','EVHC','EOG',
'EQT','EFX','EQIX','EQR','ESS','EL','ES','EXC','EXPE','EXPD','ESRX','EXR','XOM','FFIV','FB','FAST','FRT','FDX','FIS','FITB','FSLR',
'FE','FISV','FLIR','FLS','FLR','FMC','FTI','FL','F','FTV','FBHS','BEN','FCX','FTR','GPS','GRMN','GD','GE','GGP','GIS',
'GM','GPC','GILD','GPN','GS','GT','GWW','HAL','HBI','HOG','HAR','HRS','HIG','HAS','HCA',
'HCP','HP','HSIC','HES','HPE','HOLX','HD','HON','HRL',
'HST','HPQ','HUM','HBAN','IDXX','ITW','ILMN','INCY','IR','INTC','ICE','IBM','IP','IPG','IFF','INTU','ISRG','IVZ','IRM','JBHT','JEC',
'SJM','JNJ','JCI','JPM','JNPR','KSU','K','KEY','KMB','KIM','KMI','KLAC','KSS','KHC','KR','LB','LLL','LH','LRCX','LEG','LEN','LUK','LVLT','LLY',
'LNC',
'LKQ','LMT','L','LOW','LYB','MTB','MAC','M','MNK','MRO','MPC','MAR','MMC','MLM','MAS','MA','MAT','MKC','MCD',
'MCK','MJN','MDT','MRK','MET','MTD','KORS', 'MCHP','MU','MSFT','MAA','MHK','TAP','MDLZ','MON','MNST','MCO','MS','MSI','MUR','MYL',
'NDAQ','NOV','NAVI','NTAP','NFLX','NWL','NFX','NEM','NWS','NEE','NLSN','NKE','NI',
'NBL','JWN','NSC','NTRS','NOC',
'NRG','NUE','NVDA','ORLY','OXY','OMC','OKE','ORCL','PCAR','PH','PDCO','PAYX','PYPL','PNR','PBCT','PEP','PKI','PRGO','PFE','PCG','PM',
'PSX','PNW','PXD','PNC','RL','PPG','PPL','PX','PCLN','PFG','PG','PGR','PLD','PRU','PEG','PSA','PHM','PVH','QRVO','QCOM','PWR',
'DGX','RRC','RTN','O','RHT','REG','REGN','RF','RSG','RAI','RHI','ROK','COL','ROP','ROST','RCL','R','SPGI','CRM','SCG','SLB',
'SNI','STX','SEE','SRE','SHW','SIG','SPG','SWKS','SLG','SNA','SO','LUV','SWN','SWK','SPLS','SBUX','STT','SRCL','SYK','STI','SYMC',
'SYF','SYY','TROW','TGT','TEL','TGNA','TDC','TSO','TXN','TXT','BK','CLX','COO','HSY','MOS','TRV','DIS','TMO','TIF','TWX','TJX',
'TMK','TSS','TSCO','TDG','RIG','TRIP','FOXA','FOX','TSN','USB','UDR','ULTA','UA','UAA','UNP','UAL','UNH','UPS','URI','UTX','UHS',
'UNM','URBN','VFC','VLO','VAR','VTR','VRSN','VRSK','VZ','VRTX','VIAB','V','VNO','VMC','WMT','WBA','WM','WAT','WEC','WFC','HCN','WDC','WU','WRK',
'WY','WHR','WFM','WMB','WLTW','WYN','WYNN','XEL','XRX','XLNX','XL''XYL','YHOO','YUM','ZBH','ZION','ZTS']

i = 1
skipped = list()
for stock in stocks:
    tryAgain = True
    while tryAgain == True:
        print("Testing stock: " + stock + " (Number " + str(i) + " of " + str(len(stocks)) + ")")
        try:    
            ts = TimeSeries(key='9SROQY0F727KPEXL', output_format='pandas')
            data, meta_data = ts.get_daily_adjusted(symbol=stock, outputsize='compact')
            try:
                os.remove('StockData/' + stock + '.csv')
            except OSError:
                pass
            data.to_csv('StockData/' + stock + '.csv')
            tryAgain = False
            i = i + 1
        except ValueError as e:
            print("Error with " + stock + ": " + str(e))
            tryAgain = False
            if (str(e) != "Please consider optimizing your API call frequency.\n"):
                tryAgain = True
        except:
            print ("Error with " + stock + ": " + str(sys.exc_info()[0]))

#print("Skipped stocks")
#for skip in skipped:
#    print(skip + " ")

filename = 'StockDataCurrent.csv'
try:
    os.remove(filename)
except OSError:
    pass
first = True
for stock in stocks:
    
    try:
        csvfile = open('StockData/%s.csv' % stock, 'r')
    except:
        print('Skipped: ' + stock)
        continue
    
   
    reader = csv.DictReader(csvfile)

    all_lines = list(reader)

    with open(filename, 'a') as csvfile:
         filewriter = csv.writer(csvfile, delimiter=',',
                                quotechar='|', quoting=csv.QUOTE_MINIMAL)
         
         if (first):
             first = False
             dates = []
             dates.append('Name')
             dates.append('Type')
             
             #Write the headers
             for i in range(len(all_lines)):
                 Day = int(i)
                 x = all_lines[Day]['date'].split("-")
                 date = x[1] + "/" + x[2] + "/" + x[0]
                 dates.append(date)
             filewriter.writerow(dates)
         #sizeDiff = len(dates) - len(all_lines) - 2
         #Write the ClosePrice
         closePrice = []
         closePrice.append(stock)
         closePrice.append('open')
         
#         for d in range(sizeDiff):
#             closePrice.append(" ")
#             
         for i in range(len(all_lines)):
             Day = int(i)
             closePrice.append(all_lines[Day]['1. open'])
         filewriter.writerow(closePrice)
         
         #Write the HighPrice
         openPrice = []
         openPrice.append(stock)
         openPrice.append('high')
         
#         for d in range(sizeDiff):
#             openPrice.append(" ")
             
         for i in range(len(all_lines)):
             Day = int(i)
             openPrice.append(all_lines[Day]['2. high'])
         filewriter.writerow(openPrice)
            
         
         #Write the LowPrice
         highPrice = []
         highPrice.append(stock)
         highPrice.append('low')
         
#         for d in range(sizeDiff):
#             highPrice.append(" ")
             
         for i in range(len(all_lines)):
             Day = int(i)
             highPrice.append(all_lines[Day]['3. low'])
         filewriter.writerow(highPrice)

         
         #Write the LowPrice
         lowPrice = []
         lowPrice.append(stock)
         lowPrice.append('close')
         
#         for d in range(sizeDiff): lowPrice.append(" ")
             
         for i in range(len(all_lines)):
             Day = int(i)
             lowPrice.append(all_lines[Day]['4. close'])
         filewriter.writerow(lowPrice)
         
         #Write the LowPrice
         volume = []
         volume.append(stock)
         volume.append('Volume')
         
#         for d in range(sizeDiff):
#             volume.append(" ")
             
         for i in range(len(all_lines)):
             Day = int(i)
             volume.append(all_lines[Day]['6. volume'])
         filewriter.writerow(volume)
         
with open(filename, 'rb+') as f:
    f.seek(0,2)                 # end of file
    size=f.tell()               # the size...
    f.truncate(size-1)

outFile = "CurrentPicks.txt"
file = open(outFile, "r")
prev = {}
for line in file:
    line = line.split(",")
    if len(line) == 1:
        continue
    value = line[1]
    prev[line[0]] = value[:-1]
    
print('CDing')
Command = 'cd /home/pi/Desktop/PortfolioManager/'
os.system(Command)
print('Making')
Command = 'make'
os.system(Command)
print('Executing')
Command = './PortfolioManager'
os.system(Command)
print('Sleeping')
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
for st in prev:
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
        file.write("Buy " + curr[st] + " of " + st + "\n")
        
file.close()
sleep(20)
os.system('python SendEmail.py')
