/***
 * Author: Aghead_Bilal
 * Declaration of variables, constants, and functions
 * Some of the registeries of the MPU9250
 ***/

#ifndef MPU_H
#define MPU_h

class MPU
{
private:
    int lastDirection;

public:
    int fd, comp;
    short readData(const int address, const int dev);
    bool checkDataReady();
    void mpuInit();
    void waitDataReady();
    double readTemperature();
    double getCompassAngle();
    int getLastDirection();
    void setLastDirection(int direction);
    string returnOrientation();
};

#endif

/* MPU9250 registers */
// MPU I2C address
#define SENS_ADDR 0x68      /* The address of the MPU9250 */

/* MPU Control registers */
#define PWR_MGMT_1   0x6B   /* Power management register */
#define SMPLRT_DIV   0x19   /* Sample rate register */
#define CONFIG       0x1A   /* Configuration register */
#define GYRO_CONFIG  0x1B   /* Gyro configuration register */
#define INT_ENABLE   0x38   /* Enable interupts */
#define INT_PIN_CFG  0x37   /* Start magnetometer address */

// MPU output registers:
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define GYRO_XOUT_H  0x43
#define GYRO_YOUT_H  0x45
#define GYRO_ZOUT_H  0x47
#define THEMP_OUT 0x41

// Magnetometer I2C address
#define COMP_ADDR 0x0C

// Magnetometer registers
#define COMP_XOUT 0x03
#define COMP_YOUT 0x05
#define COMP_ZOUT 0x07
#define COMP_ST   0x02
#define COMP_ST2  0x09        /* Status 2 register, must read to confirm data is read */

#define COMP_CONTROL 0x0A     /* Compass controll (5.8 in datasheet) */
#define COMP_CONTROL2 0x0B
