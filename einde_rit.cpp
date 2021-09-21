
//
// Created by Aghoo on 21-9-2021.
//
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <unistd.h>


int main() {
    int fd;
    fd = wiringPiI2CSetup(0x32);
    unsigned char arr[7] = {7,3,0x22,0,3,0x22,0};
    write(fd,&arr[0],7);
}
