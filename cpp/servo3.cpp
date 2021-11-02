#include <pigpio.h>
#include <iostream>
#include<wiringPi.h>
#include<unistd.h>
#include <conio.h>
using namespace std;

//servo pin
const int servoPin = 17;

// parameters pwm
const int pwmFrequency = 50;
const int pwmRange = 255;

// servo werkbereik
const int off=0;
const int clockwise=2500;
const int antiClockwise=500;

void initaliseServo()
{
    gpioSetPWMfrequency(servoPin, pwmFrequency);

    cout << "Servo PWM range: <" << endl;
}

void goUp()
{
    gpioServo(servoPin,antiClockwise);
    sleep(1);
    gpioServo(servoPin,off);

    cout << "up: " <<  endl;
}
void godown()
{
    gpioServo(servoPin, clockwise);
    sleep(1);
    gpioServo(servoPin,off);

    cout << "down: " <<  endl;
}

int main()
{
    initaliseServo();
    gpioInitialise();


    while(1) {
        char ch = getch();

        switch (ch) {

            case 'w':
                printf("W HAS CLICKED\n");
                goUp();
                break;

            case 's':
                printf("S HAS CLICKED\n");
                godown();
                break;

            default:
                printf("HIJ IS GESTOPT\n");
                break;
        }
    }

    return 0;
}
