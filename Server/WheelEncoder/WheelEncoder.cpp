#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <stdbool.h>
#include <iostream>

#define encoderOutput 28
static volatile int globalCounter;
int rpm, speed, rps;

int interval = 1000;
long previousMillis = 0;
long currentMillis = 0;
double Circumference = 0.2105;

//Interrupt service routine:
void wheelInterrupt(void)
{
    ++globalCounter;
    fflush(stdout);
}

class WheelEncoder
{
public:
    void initRPM()
    {
        wiringPiSetup();
        pullUpDnControl(encoderOutput, PUD_DOWN);

        //initialisation
        wiringPiISR(encoderOutput, INT_EDGE_FALLING, &wheelInterrupt);
        previousMillis = millis();
    }

    int readSpeed()
    {
        currentMillis = millis();
        if (currentMillis - previousMillis > interval)
        {
            previousMillis = currentMillis;

            rpm = (float)(globalCounter * 60 / 20);
            rps = rpm / 60;
            speed = Circumference * rps;

            globalCounter = 0;
        }

        return speed;
        usleep(500);
    }
};

int main()
{

    WheelEncoder wheelEncoder;
    wheelEncoder.initRPM();
    wheelEncoder.readSpeed(); 

    return 0;
}

extern "C"
{
    WheelEncoder* WheelEncoder_new() { return new WheelEncoder(); }
    void WheelEncoder_initRPM(WheelEncoder* wheelencoder) { wheelencoder -> initRPM(); }
    int WheelEncoder_readSpeed(WheelEncoder* wheelencoder) { return wheelencoder -> readSpeed(); }
}