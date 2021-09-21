#include <wiringPi.h>
#include <wiringPiI2C.h>
int main(){
        int  fd;
        fd=wiringPiI2CSetup (0x32) ;
        wiringPiI2CWriteReg8 (fd, 0x7, 0x3) ;
        wiringPiI2CWriteReg8 (fd, 0xA5,0x2) ;
        wiringPiI2CWriteReg16(fd, 0x3, 0x02A5) ;
};
