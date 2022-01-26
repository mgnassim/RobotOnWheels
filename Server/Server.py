#!/usr/bin/python
# import the modules
from base64 import encode
from ctypes import cdll
import socket, time
import threading
from threading import Thread

# load the libraries
libMovement = cdll.LoadLibrary('/home/pi/app_control/CarMovement/libMovement.so')
libTemperature = cdll.LoadLibrary('/home/pi/app_control/Temperature/libTemperature.so')
libCompass = cdll.LoadLibrary('/home/pi/app_control/Compass/libCompass.so')
libUltra = cdll.LoadLibrary('/home/pi/app_control/Ultrasone/libUltra.so')
libWaterSensor = cdll.LoadLibrary('/home/pi/app_control/WaterSensor/libWaterSensor.so')
libWheelEncoder = cdll.LoadLibrary('/home/pi/app_control/WheelEncoder/libWheelEncoder.so')
libSiren = cdll.LoadLibrary('/home/pi/app_control/SirenFlash/libSirenFlash.so')
libWaterPump = cdll.LoadLibrary('/home/pi/app_control/WaterPump/libWaterPump.so')

class WaterPump(object):

     # constructor
    def __init__(self):
        # attribute
        self.obj = libWaterPump.WaterPump_new()

    def shootWaterPump(self):
        libWaterPump.WaterPump_shootWaterPump(self.obj)

    def stopWaterPump(self):
        libWaterPump.WaterPump_stopWaterPump(self.obj)

class SirenFlash(object):

     # constructor
    def __init__(self):
        # attribute
        self.obj = libSiren.Siren_new()
    
    def playSiren(self):
        libSiren.Siren_playSiren(self.obj)

    def playFlash(self):
        libSiren.Siren_playFlash(self.obj)

    def turnOff(self):
        libSiren.Siren_turnOff(self.obj)

class WheelEncoder(object):

    def __init__(self):
        self.obj = libWheelEncoder.WheelEncoder_new()
    
    def initialRPM(self):
        libWheelEncoder.WheelEncoder_initRPM(self.obj)

    def returnSpeed(self):
        return libWheelEncoder.WheelEncoder_readSpeed(self.obj)

class WaterSensor(object):

     # constructor
    def __init__(self):
        # attribute
        self.obj = libWaterSensor.WaterSensor_new()

    def getMoistureValue(self):
        return libWaterSensor.WaterSensor_returnMoistureValue(self.obj)

class Compass(object):

    def __init__(self):
            self.obj = libCompass.MPU_new()
        
    def initCompass(self):
        libCompass.initMPU(self.obj)

    def returnAngle(self):
        return libCompass.MPU_readAngle(self.obj)

    def returnOrientation(self):
        return libCompass.MPU_readOrientation(self.obj)

class Ultrasonic(object):

     # constructor
    def __init__(self):
  
        # attribute
        self.obj = libUltra.Ultrasonic_new()
    
    def returnDistance(self):
        return libUltra.Ultrasonic_returnDistance(self.obj)

class Temperature(object):

    def __init__(self):

        self.obj = libTemperature.Temperature_new()

    def returnTemperature(self):
        return libTemperature.Temperature_readTemp(self.obj)

class Movement(object):

     # constructor
    def __init__(self):
  
        # attribute
        self.obj = libMovement.Movement_new()

    def forward(self):
        libMovement.Movement_goForwards(self.obj)

    def backward(self):
        libMovement.Movement_goBackwards(self.obj)
    
    def left(self):
        libMovement.Movement_goLeft(self.obj)

    def right(self):
        libMovement.Movement_goRight(self.obj)
    
    def stop(self):
        libMovement.Movement_stop(self.obj)

# create a class object
car = Movement()
temp = Temperature()
ultra = Ultrasonic()
wheelEncoder = WheelEncoder()
compass = Compass()
sirenFlash = SirenFlash()
waterPump = WaterPump()

#initiating
wheelEncoder.initialRPM()
compass.initCompass()

listensocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
listensocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
Port = 8000
maxConnections = 999 
HOST = '172.20.10.10'
IP = socket.gethostname()

def sendSensorData():
    while True:
        orientationToSend = str(returnOrientation(compass.returnAngle())).encode('utf-8')
        temperatureToSend = str(temp.returnTemperature()).encode('utf-8')
        distanceToSend = str(ultra.returnDistance()).encode('utf-8')
        speedToSend = str(wheelEncoder.returnSpeed()).encode('utf-8')
        moistureValueToSend = str(returnMoisture(waterSensor.getMoistureValue())).encode('utf-8')
        endMessageToSend = str(temperatureToSend + " " + distanceToSend + " " + speedToSend + " " + orientationToSend).encode('utf-8') + b'\n'
        clientsocket.sendall(endMessageToSend)

def returnMoisture(moisture):
        if moisture <= 2000:
            return "Low"
        else:
            return "High"

def returnOrientation(angle):
        if angle > 337.25 or angle < 22.5:
            return "North"
        elif angle > 292.5 and angle < 337.25:
            return "North-West"
        elif angle > 247.5 and angle < 292.5:
            return "West"
        elif angle > 202.5 and angle < 247.5:
            return "South-West"
        elif angle > 157.5 and angle < 202.5:
            return "South"
        elif angle > 112.5 and angle < 157.5:
            return "South-East"
        elif angle > 67.5 and angle < 112.5:
            return "East"
        elif angle > 0 and angle < 67.5:
            return "North-East"

def server():
    while True:
        message = clientsocket.recv(1024).decode()
        print('(TCP) message received is: '+ message +'\n')

        if "w" in message:
            car.forward()

        elif "s" in message:    
            car.backward()

        elif "a" in message:
            car.left()
        
        elif "d" in message:
            car.right()
        
        elif "q" in message:
            car.stop()
        
        elif "z" in message:
            waterPump.shootWaterPump()

        elif "x" in message:
            waterPump.stopWaterPump()

        elif "v" in message:
            sirenFlash.turnOff()

        elif "b" in message:
            Thread(target=sirenFlash.playSiren).start()
            Thread(target=sirenFlash.playFlash).start()

listensocket.bind(('', Port))

listensocket.listen(maxConnections)
print("(TCP-Riding) Server started at " + IP + " on port " + str(Port))

(clientsocket, clientaddress) = listensocket.accept()
print("(TCP-Riding) New connection made with ", clientaddress)

#doesnt get executed till there is an accepted connection 
Thread(target=sendSensorData).start() # 2nd thread
server() # main thread
