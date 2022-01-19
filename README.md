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

## How to use

## Important Information

## Contact information
Joris Brouwer: joris.brouwer2@hva.nl<br>
Aghead Bilal: aghead.bilal@hva.nl<br>
Bilal Malik: bilal.malik2@hva.nl<br>
Nassim Mengat: nassim.mengat@hva.nl<br>
Stefano Igbinosun: stefano.igbinosun@hva.nl
