#Object Oriented Switching network interface
#Brendan Saxberg
#Run this to interface with 5 10-way & 1 6-way switch network controlled by 6 arduinos.

import serial
import socket
import time
import logging
import sys
import time
import io

def numtobin(num):
    return int ((num)*(2**18)/(20) + (2**18/2))

class AD5780():
    def __init__(self):
        #No good commands to/from this guy
        ard = serial.Serial('COM3', 9600, timeout=1)
        self.ard = ard
        #self.ard = serial.Serial('COM6', 9600, timeout=1)
        #self.ard = serial.Serial('COM6', 115200, timeout=1)
        # self.ard = [""]
        # self.serial = [] # Holds the arduino serial address
    #makes connection between channel and common out on switch specified
    #Sets the voltage of dac dacnum to voltage voltage
    def set(self,dacnum, voltage):
        binvolt = numtobin(voltage)#Convert from voltage -10 to 10 to 2^18 bit num
        combinedstring = 'SET' + ' ' + str(dacnum) + ' ' + str(binvolt) + ' \r\n'
        # print('Combined String: ' + str(combinedstring))
        self.ard.write(combinedstring.encode())

    #Initializes all of the dacs
    def init(self):
        self.ard.write(b'INIT \r\n')
        # combinedstring = 'INIT \r\n'
        # print('Combined String: ' + combinedstring)
        # self.ard.write(combinedstring.encode())

    #this relies on the ramp code in arduino, which has step as step in bits.  speed is
    def ramp(self,dacnum,voltage,step,speed):
        bvoltage = numtobin(voltage)
        bstep = numtobin(step)
        bspeed = numtobin(speed)
        combinedstring = 'RAMP' + ' ' + str(dacnum) + ' ' + str(bvoltage) + ' ' + str(bstep) + ' ' + str(bspeed) + ' \r\n'
        self.ard.write(combinedstring.encode())

    #step, speed in bits
    def ramp2(self, dacnum, voltage, step, speed):
        bvoltage = numtobin(voltage)

        combinedstring = 'RAMP' + ' ' + str(dacnum) + ' ' + str(bvoltage) + ' ' + str(step) + ' ' + str(
            speed) + ' \r\n'
        self.ard.write(combinedstring.encode())
    #ramps voltage
if __name__ == '__main__':

    a=AD5780()
    print(a.ard.is_open)
    time.sleep(1)
    print(a.init())
    #a.init()
    time.sleep(1)
    print(a.ard.read(1000))
    # a.set(1,1)
    print(a.ard.read(1000))
    a.ramp2(5,5,10,10)
    # for i in range(8):
    #     time.sleep(.1)
    #     a.set(i+1,i-1)
    #     print(a.ard.read(1000))
    #     time.sleep(.25)

