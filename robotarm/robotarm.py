# coding: utf8
import os
from os.path import expanduser
import subprocess
import serial
import serial.tools.list_ports
import sys
import time
import warnings
from random import randint

class Robotarm:

    @classmethod
    def __init__(self, locale = "EN_US", extra = False):
        arduino_ports = [
                    p.device
                        for p in serial.tools.list_ports.comports()
                        for x in range (0, 10)
                        if 'ttyUSB%d' % x  in p.name or "ttyACM%d" % x in p.name]
        if not arduino_ports:
                raise IOError("No Arduino found")
        if len(arduino_ports) > 1:
                warnings.warn('Multiple Arduinos found - using the first')
        self.ser = serial.Serial(
                            port=arduino_ports[0],
                            baudrate = 9600
                        )

    # fonction pas besoin d'instancier une classe pour l'appeler
    # Coffeehack.compute_value au lieu de coffee = Coffeehack()
    # coffee.compute_value

    def go_left_base(self, leftbase):
        goleftbase = 'B'+str(leftbase)+'L'
        self.ser.write(goleftbase)
        print(goleftbase)

    def go_right_base(self, rightbase):
        gorightbase = 'B'+str(rightbase)+'R'
        self.ser.write(gorightbase)
        print(gorightbase)

    #def open_grip(self):
        #opengrip = 'B'+'O'
        #self.ser.write(opengrip)
        #print(opengrip)

    def close_grip(self):
        closegrip = 'B'+'C'
        self.ser.write(closegrip)
        print(closegrip)

    def return_position(self):
        randomposition = randint(0,180)
        #returnposition = 'B'+ str(randomposition) +'F'
        returnposition = 'B'+'F'
        self.ser.write(returnposition)
        print(returnposition)

    def taking_ball(self):
        takingball = 'B'+'M'
        self.ser.write(takingball)
        print(takingball)

    def dance(self):
        dance = 'B'+'X'
        self.ser.write(dance)
        print(dance)

    def release_ball(self):
        release = 'B'+'W'
        self.ser.write(release)
        print(release)


# test de Bjay
'''if (__name__ == "__main__"):
    c = CoffeeHack();
    c.pour("normal", "short","fort",1)
    c.pour("normal",u"allongé","fort",1)
    c.pour("normal", "short","fort",2)
    c.pour("normal",u"allongé","fort",2)
    c.pour("normal", "short","mild",1)
    c.pour("normal",u"allongé","mild",1)
    c.pour("normal", "short","mild",2)
    c.pour("normal",u"allongé","mild",2)
    c.pour("normal", "short","normal",1)
    c.pour("normal",u"allongé","normal",1)
    c.pour("normal", "short","normal",2)
    c.pour("normal",u"allongé","normal",2)
    c.pour("normal", "short","extra strong",1)
    c.pour("normal",u"allongé","extra strong",1)
    c.pour("normal", "short","extra strong",2)
    c.pour("normal",u"allongé","extra strong",2)'''
