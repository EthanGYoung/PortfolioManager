#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Jan 20 16:15:44 2018

@author: ethanyoung
"""

import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.base import MIMEBase
from email import encoders
import sys

error = False
attach = False
subject = ""

#Prints usage if no params passed
if (len(sys.argv) == 1):
    print("Usage: SendEmail.py <-option [-e error, -a attachment]> 'Subject'")
    exit(1)
elif (len(sys.argv) == 2):
    subject = "No Subject"
else:
    subject = str(sys.argv[2:][0])
    
#Error in code somewhere
if (sys.argv[1:][0] == "-e"):
    subject = "Error: " + subject
    error = True
elif (sys.argv[1:][0] == "-a"):
    attach = True
    
fromaddr = "portfoliomanagerupdate@gmail.com"
toaddr = "Eyoung8@wisc.edu"
 
msg = MIMEMultipart()
 
msg['From'] = fromaddr
msg['To'] = toaddr
msg['Subject'] = subject

body = ""

#Attaches only if attachment specified
if (attach):
    msg.attach(MIMEText(body, 'plain'))
         
    filename = "CurrentPicks.txt"
    attachment = open("./CurrentPicks.txt", "rb")
         
    part = MIMEBase('application', 'octet-stream')
    part.set_payload((attachment).read())
    encoders.encode_base64(part)
    part.add_header('Content-Disposition', "attachment; filename= %s" % filename)
         
    msg.attach(part)
 
server = smtplib.SMTP('smtp.gmail.com', 587)
server.starttls()
server.login(fromaddr, "PortfolioManager")
text = msg.as_string()
server.sendmail(fromaddr, toaddr, text)
server.quit()
