#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <unistd.h>
#include <glob.h>
#include <iostream>
#include <stdio.h>
#include <OneWire.h>
#define KY001_Signal_PIN 4

void setup(){

    pinMode(KY001_Signal_PIN,OUTPUT);
    cout<<"pin setup" << endl;
}
void TemperaturMessurment(){
    f = open(device_file, 'r')
    lines = f.readlines()
    f.close()
    return lines
}


int main(){
    setup();

    return 0;
};
