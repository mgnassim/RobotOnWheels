#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <unistd.h>

int main(){

    int  fd;
    unsigned short xl, xy;
    fd = wiringPiI2CSetup (0x68) ;//i2c addres
    xy = wiringPiI2CReadReg8(fd, 0x03); // x msb
    xl = wiringPiI2CReadReg8(fd, 0x04);  // x lsb

    ize_t  read(int fd, void *buf, size_t count);



    return 0;
};
