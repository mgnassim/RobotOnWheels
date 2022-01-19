# IT201/2-3(Fire Brigade)

## About this project
For this project we had to create a raspberryPi controlled car that can be used in rescue situations.
Our idea was a firebrigade assitance car that can be remotely controlled by an app on your phone.
Our project contains the following functionalities: <br>
- Orientation (magnetometer)
- Critical temperature warning (temperature sensor)
- Low/high water level
- Water Pump
- Movement water hose (servo)
- Siren (speaker/light)
- Speed in m/s (wheel encoder)
- Control application (Java)



## Before starting
Before starting with this product make shure you have an android device available for the application. The application was designed for a screen ratio of 3040 x 1440 pixels in landscape mode. If you use a smaller/bigger screen, the layout may not be optimal.

## Installation

First make shure your system is up-to-date by using the following commands:
sudo apt-get update
sudo apt-get upgrade

Enter the command sudo raspi-config on your raspberryPi and go to interface options. Now enable SPI, I2C and Camera. Now reboot.

For the use of this code the following external libraries are needed on the raspberryPi:
- wiringPi<br>
     sudo apt-get install wiringPi <br>
- OpenCV<br>
    https://solarianprogrammer.com/2019/09/17/install-opencv-raspberry-pi-raspbian-cpp-python-development/
- pigpio <br>   
     https://abyz.me.uk/rpi/pigpio/download.html
- fmod<br>
     https://wiki.debian.org/FMOD     


To download the application install AndroidStudio and open the Java app file from this directory. 

## Code explanation

- In map OpenCV there are some cpp files that will walk you through OpenCV but first make sure that the OpenCV
library is installed on your raspberryPi. With those files you will learn the basics
of OpenCV in C++. FaceDetection.cpp is the file that we used to detect human faces. In here we refer to this file haarcascade_frontalface_default.xml,
so you have also to download this file on your raspberryPi.

- In map Compass_sensor you can find the code for the magnetometer sensor MPU-9250.
This sensor it consists of three parts gyroscope, accelerometer and magnetometer. The code is written in C++. 
So that means that there is two files cpp en h. In the MPU9250.h file we declared the variable's, methods and the registers we need.
In the MPU9250.cpp file we included the header file alongside some other libraries. 
This code is intended to get an orientation(compass) of the rover.

-  Low/high water level is responsible for the measuring of the water level in the tank. Base on the level of water it gives a high or low waterlevel. The code is written in C. File https://gitlab.fdmci.hva.nl/balalib/project-row/-/blob/WaterPomp/Water_pomp/water_level_sensor.c contains the code of water level before running this code the Installation process must be done first. The libary that is needed is wiringPi. 


## How to use

## Important Information

## Contact information
Joris Brouwer: joris.brouwer2@hva.nl<br>
Aghead Bilal: aghead.bilal@hva.nl<br>
Bilal Malik: bilal.malik2@hva.nl<br>
Nassim Mengat: nassim.mengat@hva.nl<br>
Stefano Igbinosun: stefano.igbinosun@hva.nl
