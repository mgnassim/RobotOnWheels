#include <wiringPi.h>
#include <wiringPiI2C.h>
int main(){
    int  sensor;
    sensor=wiringPiI2CSetup (0x70) ;
};
