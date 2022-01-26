#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <stdbool.h>
#include <iostream>

#define encoderOutput 28// sensor pin 
static volatile int globalCounter;//varible reserve in memory and keeps changing.
int rpm, speed, rps;

int interval = 1000; // 1sec 
long previousMillis = 0;//extended size variables for number storage.
long currentMillis = 0;//extended size variables for number storage.
double Circumference = 0.2105;// circumferce of the roverwheel.

//Interrupt service routine:
void wheelInterrupt(void)
{
    ++globalCounter;// adds up the pulses of the wheelencoder.
    fflush(stdout);// clear the output buffer, move data to console.
}

class WheelEncoder
{
public:
    void initRPM()
    {
        wiringPiSetup();// initialise the wiringPisetup and functions.
        pullUpDnControl(encoderOutput, PUD_DOWN);//sets the resister mode on the given pin.

        //initialisation
        wiringPiISR(encoderOutput, INT_EDGE_FALLING, &wheelInterrupt);//calls the adres of the function if input goes from 0 to 1 on the sensor pin.
        previousMillis = millis();// starts the timer.
    }

    int readSpeed()
    {
        currentMillis = millis();//starts second timer while having current time of previous timer.
        if (currentMillis - previousMillis > interval)//remaining time bigger than 1sec
        {
            previousMillis = currentMillis;//save up the time of current in previousmillis. 

            rpm = (float)(globalCounter * 60 / 20);// rpm caculation
            rps = rpm / 60;// rps caculation
            speed = Circumference * rps;//M/s caculation.

            globalCounter = 0;// resets counter. 
        }

        return speed;// give back the value of M/s caculation.
        usleep(500);
    }
};

extern "C"
{
    WheelEncoder* WheelEncoder_new() { return new WheelEncoder(); }
    void WheelEncoder_initRPM(WheelEncoder* wheelencoder) { wheelencoder -> initRPM(); }
    int WheelEncoder_readSpeed(WheelEncoder* wheelencoder) { return wheelencoder -> readSpeed(); }
}
