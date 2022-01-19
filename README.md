# IT201/2-3(Fire Brigade)

## About this project
For this project we had to create a raspberryPi controlled car that can be used in rescue situations.
Our idea was a firebrigade assitance car that can be remotely controlled by an app on your phone.<br>
Our project contains the following functionalities:
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

First make sure your system is up-to-date by using the following commands:
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
- In the OpenCV folder there are some cpp files that will walk you through OpenCV but first make sure that the OpenCV
library is installed on your raspberryPi. With those files you will learn the basics
of OpenCV in C++. FaceDetection.cpp is the file that is used to detect human faces. It references to haarcascade_frontalface_default.xml,
so make sure you download it on your system.

- In the Compass_sensor folder you can find the code for the magnetometer MPU-9250.
This sensor consists of three parts: gyroscope, accelerometer and magnetometer. This code is written in C++ and thus consists of two files,
a .cpp and a h. header file. In the MPU9250.h file the the variable's, methods and the registers we need are declared .
In the MPU9250.cpp file the header file alongside some other libraries have to be included. 
This code is intended to get a directional orientation(compass) for the rover.

-  Low/high water level is responsible for the measuring of the amount of water in the tank. Based on the amount of water it gives a high or low value wich is represented in the application. The code is written in C. File https://gitlab.fdmci.hva.nl/balalib/project-row/-/blob/WaterPomp/Water_pomp/water_level_sensor.c contains the code for water level. Before running this code, the Installation process must be done first.
-  Water Pump is an essential part of the product it makes sure to pump the water out of the tank and through the hose. The Code is pretty simple, by using a switch caseyou can turn the pump on or off. File https://gitlab.fdmci.hva.nl/balalib/project-row/-/blob/WaterPomp/Water_pomp/waterPomp.c contains the code and is written in C. 
- wheel encoder measures the speed of the rover itself in meters per secon(m/s). The code uses of interupts to make sure that after every second a caculation takes place for the speed. The sensor gives a value in RPM(rotations per minute) and converts it to meters per second. File https://gitlab.fdmci.hva.nl/balalib/project-row/-/blob/Wheel-encoder/Wheel_encoder/speedo.c contains the code and is written in C. 
- In the distance sensor folder you can find the code for the ultrasonic sensor which is responsible for measureing the distance between the car and the object. To compile use the following command: "g++ -Wall *name file* -o *give name executable* -lwiringPi"
- In the siren folder you can find the code for the siren. The siren consists of an LED light and a speaker. when the siren turns on, the led starts to blink and an audio files starts playing thorugh the speaker. to compile use the following command: "g++ -Wall  *name file**  -o *give name executable* -lwiringPi -I/usr/local/include -L/usr/local/lib -lfmod -pthread"
- In the servo folder you can find the code fore the servo motor. The makes it possible to move the waterhose up and down. To compile use the following commanD: "g++ -Wall -pthread -o *name file* *name executable* -lpigpio -lrt"

## How to use
To use the firebrigade rover you only need the rover and a mobile android phone. The mobile android phone needs to release a mobile hotspot to which the raspberry pi of the rover needs to connect to. It should connect to your phone automatically once you turn the rover on (presuming you have had a previous connection with the raspberry pi.). To learn how to setup a mobile hotspot in combination with the pi we refer to this article that explains it step by step: https://medium.com/geekculture/how-to-connect-to-the-raspberry-pi-using-mobile-hotspot-2362a6b02efc.

Once you have the network setup, the only thing that is left to do is by connecting to the rover by pressing: START RIDE, in the app.
This enables a TCP socket connection between the two devices, from which messages can be sent and received by both parties. 

To enable the camera used on the raspberry pi, you have to click the CAMERA button on the app to enable an UDP connection from which camerafeed is sent from the server to the app.

## Important Information
## Hardware schematic
<img src="https://gitlab.fdmci.hva.nl/balalib/project-row/-/raw/main/img/schema.png" width="500"><br>
<img src="https://gitlab.fdmci.hva.nl/balalib/project-row/-/raw/main/img/tabel.png" width="300"><br>

## Contact information
Joris Brouwer: joris.brouwer2@hva.nl<br>
Aghead Bilal: aghead.bilal@hva.nl<br>
Bilal Malik: bilal.malik2@hva.nl<br>
Nassim Mengat: nassim.mengat@hva.nl<br>
Stefano Igbinosun: stefano.igbinosun@hva.nl
