#!/usr/bin/env python


import time
import serial


ser = serial.Serial(
  
   port='/dev/ttyUSB0',
   baudrate = 115200,
   parity=serial.PARITY_NONE,
   stopbits=serial.STOPBITS_ONE,
   bytesize=serial.EIGHTBITS,
   timeout=0.5
)



while 1:
   data = '90,low,15.6,125*\n'
   ser.write(data)
   print data
   
   time.sleep(1)
   '''
   print 'hello'
   time.sleep(5)
   ser.write('goodbye')
   print 'goodbye'
   time.sleep(.5)
   '''
   
port.close()
