#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, second

int main(){

    int  fd;
    fd=wiringPiI2CSetup (0x31) ;//i2c addres
    unsigned char arr[2]={00,0x51};//register port and command

    while (true) {
        wiringPiI2CWriteReg8 (fd,arr[0], 2);
        sleep_for(seconds(1));
        int data = wiringPiI2CReadReg16 (fd,1);
        //cout << "gemeten afstand is: " << data << "\n";
    }

    return 0;
};
