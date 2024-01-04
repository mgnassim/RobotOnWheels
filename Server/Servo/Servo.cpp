/***
    * Code for servo
 ***/

#include <pigpio.h>
#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
#include <conio.h>


class Servo
{

public:
    int servoPin = 17;     //pin
    int pwmFrequency = 50; // hertz default p=20 ms
    //PWM range by default 255(8b) dutycycle 100% dutycycle always on

    // servo werkbereik 
    int clockwise = 2500;    //pulse width 2.5ms to move most clockwise
    int antiClockwise = 500; //pulse width 0.5ms to move most anticlockwise
    int off = 0;   //pulse width 0 is of

    // index
    int level = 0; //val for storing


    /***
 * initalise and set default values
 * Check for errors
***/

    Servo()
    {
        //set pin and freq
        gpioSetPWMfrequency(servoPin, pwmFrequency);
        //initialise GPIO
        gpioInitialise();
        if (gpioInitialise() < 0)
        {
            cout << "Initialisation error." << endl;
        }
    }

    /***
 * setter for changing default val such as pin and freq
***/
    void setData(int pin, int pwmFreq)
    {
        this->servoPin = pin;
        this->pwmFrequency = pwmFreq;
        gpioSetPWMfrequency(servoPin, pwmFrequency);
    }

    /***
 * setter for changing range clockwise and anticlockwise
***/

    void setRange(int clockwise, int antiClockwise)
    {
        this->clockwise = clockwise;
        this->antiClockwise = antiClockwise;
    }

    /***
 * send an pulse to the servo to move anticlockwise
***/

    void moveAnticlockwise() //up
    {
        if (level <= -1)
        {
        }
        else
        {
            gpioServo(servoPin, antiClockwise);
            usleep(500);
            gpioServo(servoPin, off);
            level--;
        }
    }

    /***
 * send an pulse to the servo to move clockwise
***/

    void moveClockwise() //down
    {
        if (level >= 2)
        {
        }
        else
        {
            gpioServo(servoPin, clockwise);
            usleep(650);

            gpioServo(servoPin, off);
            level++;
        }
    }
};

extern "C"
{
    Servo *Servo_new() { return new Servo(); }
    void Servo_moveClockwise(Servo *servo) { servo->moveClockwise(); }
    void Servo_moveAntiClockwise(Servo *servo) { servo->moveAnticlockwise(); }
}
