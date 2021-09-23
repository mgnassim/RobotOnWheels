#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <unistd.h>

int main(){

    int  fd;
    fd = wiringPiI2CSetup (0x70) ;//i2c addres
    //unsigned char arr[2]={00,0x51};//register port and command
    //unsigned char arr1[1]={0x03};


    while (1) {
        wiringPiI2CWriteReg8 (fd,00,81);
        sleep(1);
        int data = wiringPiI2CReadReg8(fd,3);
        printf("gemeten afstand is %d\n", data);
        sleep(1);
    }

    return 0;
};
