# IT201/2-3(Fire Brigade)

## About this project
For this project we had to create a raspberryPi controlled car that can be used in rescue situations.<br>
Our idea was a firebrigade assitance car that can be remotely controlled by an app on your phone.<br>
Our project contains the following functionalities:
- Orientation (magnetometer)
- Critical temperature warning (temperature sensor)
- Low/high water level
- Water Pump
- Movement water hose (servo)
- Distance to objects (Ultrasonic sensor)
- Siren (speaker/light)
- Speed in m/s (wheel encoder)
- Live camera view of the rover
- Control application (Java)


## Before starting
Before starting with this product make sure you have an android device available for the application. The application was designed for a screen ratio of 3040 x 1440 pixels (Samsung Galaxy S10) in landscape mode. If you use a smaller/bigger screen, the layout may not be optimal.
Clone this repository onto your system, or download it by clicking the download button as a .zip or however you use.

## Installation

First make sure your system is up-to-date by using the following commands: <br>
**sudo apt-get update <br>
sudo apt-get upgrade**

Enter the command sudo raspi-config on your raspberryPi and go to interface options. Now enable **SPI, I2C and Camera**. Now reboot.

For the use of this code the following external libraries are needed on the raspberryPi:
- **WiringPi**<br>
     http://wiringpi.com/ <br>
- **OpenCV**<br>
    https://solarianprogrammer.com/2019/09/17/install-opencv-raspberry-pi-raspbian-cpp-python-development/
- **Pigpio** <br>   https://abyz.me.uk/rpi/pigpio/download.html
- **FMOD**<br>
     https://wiki.debian.org/FMOD     

For the pc:
- **Android Studio (preferred):** <br>
     https://developer.android.com/studio
     
## Code explanation
# OpenCV
- In the OpenCV folder there are some cpp files that will walk you through OpenCV but first make sure that the OpenCV
library is installed on your raspberryPi. With those files you will learn the basics of OpenCV in C++. Using OpenCV, you can pretty much do every Computer Vision task that you can think of. You can do things such as image processing operations, building GUI, video analysis, 3D reconstruction,
Face and object recognition and so on.. <br>
The reason we use OpenCV is to detect human faces. We implemented our use case using the Haar Cascade classifier. FaceDetection.cpp is the file that is used to detect human faces. It references to haarcascade_frontalface_default.xml, so make sure you download it on your system. I will explain to you what these Haar Cascade Classifiers are. This is basically a machine learning based approach where the cascade function is trained from a large number of positive and negative images. Based on the training, it is then used to detect objects in other images. So how this works, they are huge single .xml files with massive feature sets, each xml corresponding to a very specific type of use case.

# Magnetometer
- First, you need to know that the earth magnetic is very weak, so compasses are terrible sensors. It is very hard to get compass reading if you have an electric motor nearby, big power cables nearby or you are in a classroom with steal desks all these things make the compass not work well. So, your best bet with the compass is to be outside at a wooden table. That’s where it’s going to work the best.
-  MPU-9250 sensor consists of three parts: 3-Axis gyroscope, 3-Axis accelerometer and 3-Axis magnetometer. Reading the gyroscope data will give you degrees per second so the turn rate in x y and z all three axis. The accelerometer measures the acceleration in g’s. The standard value of gravity, or normal gravity, g, is defined as go=980.665 centimeters per second squared, or 32.1741 feet per second squared. And the magnetometer is basically the compass. This sensor has an I2c interface, so make sure you enable the I2c interface option on your raspberryPi.   
- In the Compass_sensor folder you can find the code for the magnetometer MPU-9250. This code is written in C++ and thus consists of two files,
a .cpp and a h. header file. In the MPU9250.h file the the variable's, methods and the registers we need are declared .
In the MPU9250.cpp file the header file alongside some other libraries have to be included. 
This code is intended to get a directional orientation(compass) for the rover.

# Water moisture sensor
-  Low/high water level is responsible for the measuring of the amount of water in the tank. Based on the amount of water it gives a high or low value wich is represented in the application. The water sensor is an analog sensor it gives only analog values back, but the raspberryPi can only read digital values. To get the values of the sensor in digital we use the adc mcp3208 to convert analog to digital. mcp3208 gives the digital values of the water sensor to the raspberry base on the values the high and low will be assigned to the values. Before the use of the adc it require an SPI interface connection that be enable on raspberryPi self with the command sudo raspi-config for the values to come true . The code is written in C++. File https://gitlab.fdmci.hva.nl/balalib/project-row/-/blob/main/Server/WaterSensor/WaterSensor.cpp contains the code for water level. Before running this code, the Installation process must be done first.

# Water pump
-  Water Pump is an essential part of the product it makes sure to pump the water out of the tank and through the hose. The Code is pretty simple, by using a switch case you can turn the pump on or off. The pump self can only be controlled true a relais module for the code to work. File https://gitlab.fdmci.hva.nl/balalib/project-row/-/blob/main/Server/WaterPump/WaterPump.cpp contains the code and is written in C++. 

# Wheel Encoder (speedometer)
- wheel encoder measures the speed of the rover itself in meters per secon(m/s). The code make use of interupts to make sure that after every second a caculation takes place for the speed. The sensor gives a value in RPM(rotations per minute) and converts it to meters per second. The caculation of the M/s is done with the help of the RPM, RPS and circumference of the wheel. File https://gitlab.fdmci.hva.nl/balalib/project-row/-/blob/main/Server/WheelEncoder/WheelEncoder.cpp contains the code and is written in C++. 

# Ultrasonic sensor
- The SRF02 is a single transducer ultrasonic rangefinder in our case the sensor  is responsible for measuring the distance between the car and the object.
It takes 65 milliseconds from issuing the ping command to the result being available.
The datasheet includes a list of all of its commands but for now we using command 81, which sends a burst and returns the result in cm. 
We are using mostly the wiringPI lib for the code. Our code has only one function returnDistance. This fucntion does the following it write to the location registor and gives the command for Real Ranging Mode Result in centimeters. After that we give the sensor time for measurement.(the sesnor wil give an burst and wil wait for an echo then it wil make an calculation) after that we wil read out the data from the register location 3 here we wil find the result in cm and this data we wil return to the function.

To compile use the following command: "g++ -Wall *name file* -o *give name executable* -lwiringPi"

# Siren
- In the siren folder you can find the code for the siren. The siren consists of an LED light and a speaker. when the siren turns on, the led starts to blink and an audio files starts playing thorugh the speaker. to compile use the following command: "g++ -Wall  *name file**  -o *give name executable* -lwiringPi -I/usr/local/include -L/usr/local/lib -lfmod -pthread"

# Servomotor
- the servo motor is used for an up and down motion. it makes it  possible to move the waterhose up and down. The lib We need is pigpio. with this library it is easy to make the servo due PWM.
first we have to decleare the gpio pin as an output pin. After that we have to set an freq for the servo 50 herts is the common freq for the servo to work. We have 2 function for the servo clockwise and anticlockwise

To compile use the following commanD: "g++ -Wall -pthread -o *name file* *name executable* -lpigpio -lrt"

# Server
•	The server can be ran by running ‘python Server.py’ in the command line on the raspberry pi. In Server.py you will find several classes which implement the use of the code written in C/C++ for the sensor/actuators. For example there is a class called Ultrasonic. This class has a function which returns the distance between the rover and the ultrasonic sensor. That function calls another function from a shared library compiled from C/C++ which does the actual executing and calculating.  <br><br>
To be actually able to use code from the shared library, we use a standard python library called ‘ctypes’.  It provides C compatible data types, and allows calling functions in DLLs or shared libraries. It can be used to wrap these libraries in pure Python.  From this library we use the class ‘cdll’. This class contains a function called LoadLibrary which does all the work for us and loads a shared library and returns it. 
The server gets messages from the client (app) and uses those messages accordingly to execute a specific function of the rover. <br><br>The ‘keybindings’ are as following: <br>
**b** = turn on the siren <br>
**v** = turn off the siren<br>
**w** = drive forewards <br>
**s** = drive backwards  <br>
**d** = turn left <br>
**a** = turn right<br>
**q** = stop driving<br>
**o** = raise servo(hose)<br>
**l** = lower servo(hose) <br>
**z** = shoot pump<br>
**x** = stop shooting pump<br>

# Client 
•	The Client (the app) has two activities. The first activity has basically only one goal, greeting you with a warm welcome and redirecting the user to the control interface. This contains pretty basic code and contains some textViews with a button in the middle. The button has an onClick trigger which executes a specific function that starts an ‘Intent’. This intent tries to find another java class and redirects the user.
 The second activity is the control interface, where all the magic happens. In the app there are several inner classes to be found. First off there are three classes called ‘Connection’, ‘Receive’ and ‘Send’.  <br><br>
**Connection:** this class has a pretty straightforward function to fullfill. A socket is initialized with data like: the ip address of the pi and the port of the socket. After the socket, an input and output are made which are later used in the classes ‘Receive’ and ‘Send’. <br><br>
**Receive:** This class uses the inputStream of ‘Connection’ and is being used to store the value of the message from the server into a variable. This message contains the values of the sensors wired to the rover. The value of every sensor is split and stored into a array. Each index is the value of each sensor. [0] = temperature, [1] = distance, [2] = rpm of m/s, [3] = orientation/compass, [4] = waterMoistureSensor.
A textView is made then to show the value of each sensor to the user and is refreshed everytime a message is received from the server if its not null. <br><br>
**Send:** This class uses the outputstream made in ‘Connection’ and has a Constructor with a String parameter. It uses the value in the parameter and uses .write() to send the message accordingly to the server. The server uses the message to accordingly execute specific actions the rover is capable of.  <br><br>
Lastly we have the inner class ‘UDP’ which is meant for the live camera stream. The reason because the camera has a seperate server is because another transmission protocol is used for communicaton between the phone and the pi. For this server a socket is being used with UDP. (User Datagram Protocol) A TCP/IP protocol that is widely used for streaming audio and video, voice over IP (VoIP) and videoconferencing. UDP is considered an unreliable delivery protocol because it does not check for errors, but it is still very fast compared to TCP which the other classes use. <br><br>
**UDP:** Java has a standard class called DatagramSocket and DatagramPacket. UDP uses datagrams, which are data packets used in this protocol, to send data to the receiver. First off we start by initializing a DatagramSocket through which we can send DatagramPackets we make after. We make a request datagrampacket in which we request data from the server, after which we make datagrampacket which will have the value of the response from the server. This datagrampacket is way bigger than the request because this will have the base64 value of the camera frame we get. We make a String object which has the value of the message of the datagram packet, which we decode with the help of the function ‘decodeBase64ToBitmap’. 
Exactly as the function says, we converted the base64 message to a Bitmap. A bitmap is a type of memory organization or image file format used to store digital images. Continuously in a while loop running in a seperate thread, the imageView is being changed countless times according to the value of the bitmap. That is how the camera view is being livestreamed to the app.

## How to use

To use the firebrigade rover you only need the rover and a mobile android phone. The mobile android phone needs to release a mobile hotspot to which the raspberry pi of the rover needs to connect to. It should connect to your phone automatically once you turn the rover on (assuming you have had a previous connection with the raspberry pi.). To learn how to setup a mobile hotspot in combination with the pi we refer to this article that explains it step by step: https://medium.com/geekculture/how-to-connect-to-the-raspberry-pi-using-mobile-hotspot-2362a6b02efc.<br><br>
You have the connection and network setup now, perfect! The next step is to get the app onto your android phone. For this step you only need to have your laptop once. Open Android Studio (see Installation) and navigate to ‘File’ in the top left of your screen. Click on ‘Open Project/Folder’ and navigate to where you extracted the repository on your system. Access the folder, we don’t need the whole repository of course because we only need the app. Select ‘Client (App)’ as the folder you want to open and open. <br><br>
It is not small so it may take a few minutes to let the application build with gradle. After you see a message that the build is finished there is a final thing we need to check in the code. To be able to connect to the raspberry pi with the app, you need to insert the valid IP-adress of the raspberry pi. Access SecondActivity.java where you will see  a few initialized variables at the top. The only variable you need to change is ‘String IP_ADDRESS’. Change the value of this variable to the IP of the raspberry pi. <br><br>
Now you have the app setup, it is time to put it on your phone 😄. Grab an USB-C/Micro-USB cable and connect the phone to the computer. Now go to Android Studio and see whether or not the name of the phone appears, where the name of the emulator normally sits. It doesn’t? Use the Connection Assisstant. A wide explanation can be found here: https://developer.android.com/studio/run/device
Run the app on your connected phone and that’s it! The app is now installed onto the phone. The cable can now be removed. <br><br>
The next step is enabling the rover itself. The rover can be turned on by switching the power button on the back. Double check whether all the cables are in the right place and the battery is connected. <br><br>
Once the rover is turned on, the only thing that is left to do is by connecting to the rover by pressing: START RIDE, in the app. This enables a TCP socket connection between the two devices, from which messages can be sent and received by both parties.
To enable the camera used on the raspberry pi, you have to click the CAMERA button on the app to enable an UDP connection from which a camerafeed is sent from the server to the app. Now you can see a live view of the rover! Time to extinguish some fire 🔥🚒!

## Hardware schematic
<img src="https://gitlab.fdmci.hva.nl/balalib/project-row/-/raw/main/img/schema.png" width="500"><br>
<img src="https://gitlab.fdmci.hva.nl/balalib/project-row/-/raw/main/img/tabel.png" width="300"><br>

## Contact information
Joris Brouwer: joris.brouwer2@hva.nl<br>
Aghead Bilal: aghead.bilal@hva.nl<br>
Bilal Malik: bilal.malik2@hva.nl<br>
Nassim Mengat: nassim.mengat@hva.nl<br>
Stefano Igbinosun: stefano.igbinosun@hva.nl
