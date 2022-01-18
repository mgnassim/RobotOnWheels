# IT201/2-3(Fire Brigade)

## About this project
For this project we had to come with an idea for a rescue car.
We came up with an firebrigade rover remotly controlled with an app.
Our rover has the following functions:
- Orientation (magnetometer)
- Critical temperature warning (temperature sensor)
- Low/high water level
- Water Pump
- Movement water hose (servo)
- Siren (speaker/light)
- Speed in m/s (wheel encoder)
- Control application (Java)



## Before starting
Before starting with this product make shure you have an android device available for the application. the application was designed for a screen ratio of 3040 x 1440 pixels in landscape mode. If you use a smaller/bigger screen, the layout may not be optimal.

## Installation

First make shure your system is up-to-date by using the following commands:
sudo apt-get update
sudo apt-get upgrade

Enter the command sudo raspi-config on your raspberryPi and go to interface options. Now enable SPI, I2C and Camera. Now reboot.

For the use of this code the following external libraries are needed on the raspberryPi:
- wiringPi
    ~ sudo apt-get install wiringPi ~
- OpenCV
    ~ https://solarianprogrammer.com/2019/09/17/install-opencv-raspberry-pi-raspbian-cpp-python-development/ ~
- pigpio    
    ~ https://abyz.me.uk/rpi/pigpio/download.html ~
- fmod
    ~ https://wiki.debian.org/FMOD ~    


To download the application install AndroidStudio and open the Java app file from this directory. 

## How to use


## Important Information

    ~The START keyword should only be said after hearing a second beep. 
    This means that the robot is ready to hear you out (subscribe/unsubscribe).
    The advice above also applies to the BINGO keyword.

    ~The robot makes a little movement while saying a number but there is still a chance the robot can fall over.
    That is why it is recommended to have someone close to the robot if that happens.

    ~Only scan the QR-Code on the card when the robot is done with talking and you hear a second beep.
    This is the most safe way to recognize a valid winner and overload of data to the robot. 

## Contact information
Joris Brouwer: joris.brouwer2@hva.nl<br>
Aghead Bilal: aghead.bilal@hva.nl<br>
Bilal Malik: bilal.malik2@hva.nl<br>
Nassim Mengat: nassim.mengat@hva.nl<br>
Stefano Igbinosun: stefano.igbinosun@hva.nl
