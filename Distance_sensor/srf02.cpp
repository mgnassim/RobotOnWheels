#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;

int read_distance(){
    int  fd;
    int reg=00;// command register
    int data=81; //data command
    fd=wiringPiI2CSetup(0x70) ;//i2c addres
    wiringPiI2CWriteReg8 (fd,reg, data);// write to register and give command
    sleep(1);//give sensor time to think
    int data = wiringPiI2CReadReg8 (fd,3);//read distance in cm
    return data;
}



int main(){


    while (true) {
        cout << "gemeten afstand is: " << read_distance() << "\n";

    }

    return 0;
}
