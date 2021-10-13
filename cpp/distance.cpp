#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;



int main(){
    cout << "start\n";

    int  fd;
    fd=wiringPiI2CSetup(0x70) ;//i2c addres
    //unsigned char arr[2]={00,0x51};//register port and command

    while (true) {
        wiringPiI2CWriteReg8 (fd,00, 81);
        sleep(1);
        int data = wiringPiI2CReadReg8 (fd,3);
        cout << "gemeten afstand is: " << data << "\n";
    }

    return 0;
}
