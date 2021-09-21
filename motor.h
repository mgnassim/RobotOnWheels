//ahha
// Created by bilal on 16-9-2021.
//

#ifndef PROJECT_ROW_MOTOR_H
#define PROJECT_ROW_MOTOR_H

#include <wiringPi.h>
#include <wiringPiI2C.h>
int fd;
fd =wiringPiI2CSetup (0x31) ;
uint8_t  arr[7] = {7,3,0xA5,1,3,0xA5,2};
write(fd,&arr[0],7);

#endif //PROJECT_ROW_MOTOR_H
