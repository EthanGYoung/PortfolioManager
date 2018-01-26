import sys
import os
import csv

stocks = []
#Initializes Stock list
with open("Stocks.txt", "r") as file:
    for line in file:
        st = line.split(",")
        for stock in st:
            stocks.append(stock.rstrip())
            
filename = 'StockDataCurrent.csv'
print(stocks)

#Removes current file
try:
    os.remove(filename)
except OSError:
    pass

first = True

#Formats data in the files correctly for the Portfolio Manager
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

         #Write the ClosePrice
         closePrice = []
         closePrice.append(stock)
         closePrice.append('open')
             
         for i in range(len(all_lines)):
             Day = int(i)
             closePrice.append(all_lines[Day]['1. open'])
         filewriter.writerow(closePrice)
         
         #Write the HighPrice
         openPrice = []
         openPrice.append(stock)
         openPrice.append('high')
             
         for i in range(len(all_lines)):
             Day = int(i)
             openPrice.append(all_lines[Day]['2. high'])
         filewriter.writerow(openPrice)
         
         #Write the LowPrice
         highPrice = []
         highPrice.append(stock)
         highPrice.append('low')
             
         for i in range(len(all_lines)):
             Day = int(i)
             highPrice.append(all_lines[Day]['3. low'])
         filewriter.writerow(highPrice)

         
         #Write the LowPrice
         lowPrice = []
         lowPrice.append(stock)
         lowPrice.append('close')
             
         for i in range(len(all_lines)):
             Day = int(i)
             lowPrice.append(all_lines[Day]['4. close'])
         filewriter.writerow(lowPrice)
         
         #Write the LowPrice
         volume = []
         volume.append(stock)
         volume.append('Volume')
             
         for i in range(len(all_lines)):
             Day = int(i)
             volume.append(all_lines[Day]['6. volume'])
         filewriter.writerow(volume)

#Eliminates extra space at end of file
with open(filename, 'rb+') as f:
    f.seek(0,2)                 # end of file
    size=f.tell()               # the size...
    f.truncate(size-1)
