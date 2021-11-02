#include <pigpio.h>
#include <iostream>
using namespace std;
#include <iostream>
#include<wiringPi.h>
#include<unistd.h>
//servo pin
const int servoPin = 17;

// parameters pwm
const int pwmFrequency = 50;
const int pwmRange = 1000;

// servo werkbereik
const double minPwm = 2.3; // 2.3% PWM ->  0 %
const double maxPwm = 12.5; // 12.5% PWM ->  100 %

 void initaliseServo()
{
    gpioSetPWMfrequency(servoPin, pwmFrequency);
    gpioSetPWMrange(servoPin, pwmRange);

    cout << "Servo PWM range: <" << minPwm << ", " << maxPwm << "> [%]" << endl;
}

void setServo(double anglePercent)
{
    double pwmPercent = (maxPwm - minPwm) * (0.01 * anglePercent) + minPwm; // % PWM
    double pwmValue = (0.01 * pwmPercent) * pwmRange; // wartosc dla PWM

    gpioPWM(servoPin, (int)pwmValue);

    cout << "Servo PWM value: " << pwmPercent << " [%]" << endl;
}

int main()
{
    if(gpioInitialise() < 0)
        cout << "Initialisation error." << endl;

    else
    {
        initaliseServo();

        while(true)
        {
            double anglePercent;

            cout << "Angle <0, 100> [%]: ";
            cin >> anglePercent;

            if(anglePercent < 0.0)
                break;

            if(anglePercent > 100.0)
                anglePercent = 100.0;

            setServo(anglePercent);
        }

        gpioTerminate();
    }

    return 0;
}