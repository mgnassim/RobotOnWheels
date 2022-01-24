#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <unistd.h>

/***
 * Author: Bilal_Malik
 * Code for SRF02 ultrasonic sensor
 *The SRF02 does not require any user calibration
 ***/

     /* SRF02 registers */
// MPU I2C address
#define SENS_ADDR 0x70      /* The address of the SRF02 on I2C*/

/*  Registers */
#define CMD_REG   0   /* Command register */
#define RNG_LOW_REG   3  /* low byte result register */

/* Commands */
#define CMD_RRM_CM   81   /*Command for Real Ranging Mode Result in centimeters*/


class Ultrasonic {
    
    public:
        int returnDistance() {

            wiringPiI2CWriteReg8(wiringPiI2CSetup(SENS_ADDR),CMD_REG, CMD_RRM_CM);// write to reg
            sleep(1); //give the sensor time for measurement
            return wiringPiI2CReadReg8(wiringPiI2CSetup(SENS_ADDR),RNG_LOW_REG);//Read result from register in cm
            
    }
};

extern "C" {
    Ultrasonic* Ultrasonic_new(){ return new Ultrasonic(); }
    int Ultrasonic_returnDistance(Ultrasonic* ultrasonic){ return ultrasonic -> returnDistance(); }
}
