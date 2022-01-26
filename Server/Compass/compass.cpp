/***
* Author: Aghead_Bilal
* This code is written for the MPU9250 sensor
* With this code you can read data from the sensor, this includes: compass and temperature
***/

#include <wiringPiI2C.h> // Used to communicate over I2C
#include <wiringPi.h>    // Used to startup wiringpi

#include <unistd.h> // Include sleep functions
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;

#include "compass.h"

// Add debug options. use OUT(your text) to print only when debug mode is enabled
#define DEBUG_MODE 0 // '0' must be '1' to show the debug output
#if DEBUG_MODE == 1
#define OUT(x) cout << "Mpu9250: " << x << endl
#else
#define OUT(x)
#endif

/***
 * Start the MPU and enable all devices
 * WARNING: Needs to be run to enable Magnetometer I2C address
***/
void MPU::mpuInit()
{
    OUT("Starting MPU");

    // Start the device and save it
    fd = wiringPiI2CSetup(SENS_ADDR);

    // wake up device
    wiringPiI2CWriteReg8(fd, PWR_MGMT_1, 0x00);
    usleep(1000);

    // Set clock source to be PLL with x-axis gyroscope reference, bits 2:0 = 001
    wiringPiI2CWriteReg8(fd, PWR_MGMT_1, 0x01);
    usleep(1000);

    // Configure Gyro and Accelerometer
    // Disable FSYNC and set accelerometer and gyro bandwidth to 44 and 42 Hz, respectively;
    wiringPiI2CWriteReg8(fd, CONFIG, 0x03);
    usleep(1000);

    // Set sample rate = gyroscope output rate/(1 + SMPLRT_DIV)
    // Use a 200 Hz rate;
    wiringPiI2CWriteReg8(fd, SMPLRT_DIV, 0x04);
    usleep(1000);

    // Write to Gyro Configuration register
    wiringPiI2CWriteReg8(fd, GYRO_CONFIG, 24);
    usleep(1000);

    // Write to interrupt enable register
    wiringPiI2CWriteReg8(fd, INT_ENABLE, 0x01);
    usleep(1000);

    wiringPiI2CWriteReg8(fd, INT_PIN_CFG, 0x12);
    usleep(1000);

    // Start Magnetometer device and save it
    comp = wiringPiI2CSetup(COMP_ADDR);
    usleep(10000);

    // Disable measurements
    wiringPiI2CWriteReg8(comp, 0x0a, 0x0);
    sleep(1);

    // Start continuous measurement mode 8Hz (set to 0x6 for 100Hz)
    wiringPiI2CWriteReg8(comp, COMP_CONTROL, 0x16);

    OUT("MPU init completed");
}

/***
 * Read the values from the given address and return as one address
 * @param Address(int): The register address the data is located
 * @param Device(int): The device object, Compass or MPU
 * @return (short): The complete value
 ***/
short MPU::readData(int address, int device)
{
    unsigned short lowByte, highByte;
    short int value;
    highByte = wiringPiI2CReadReg8(device, address);    /* Read the upper part of the value */
    lowByte = wiringPiI2CReadReg8(device, address + 1); /* Read the lower part of the value */
    value = (highByte << 8) | lowByte;                  /* Stitch the values together */
    return value;
}

/***
 * Read the temperature from the sensor
 * @return(double): The temperature in degrees Celcius
 ***/
double MPU::readTemperature()
{
    // Divide the temperature reading by 340 and then add +36.53 to convert to Celsius.
    return (readData(THEMP_OUT, fd) / 340) + 36.53;
}

/***
 * Check the compass data is ready,
 * @return(bool): True if data is ready false in other cases
 ***/
bool MPU::checkDataReady()
{
    int tmp = wiringPiI2CReadReg8(comp, COMP_ST);
    if (tmp && 0x01)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/***
 * Wait until the data is ready
 * If not ready wait 5 second
 ***/
void MPU::waitDataReady()
{
    bool readyStatus = checkDataReady();
    if (readyStatus)
    {
        return;
    }
    else
    {
        usleep(500);
        waitDataReady();
    }
}

/***
 * Read the values from the compass and calculates the orientation angle
 * @return(double): The orientation angle of the rover
 ***/
double MPU::getCompassAngle()
{
    double angle;
    short x, y, z;

    // Wait with measurement on data ready
    waitDataReady();

    // Get measurements from the compass
    usleep(100);
    x = readData(COMP_XOUT, comp);
    usleep(100);
    y = readData(COMP_YOUT, comp);
    usleep(100);
    z = readData(COMP_ZOUT, comp);
    usleep(100);

    // Read to confirm the reading is ready
    wiringPiI2CReadReg8(comp, COMP_ST2);
    usleep(100);
    OUT("X: " << x);
    OUT("Y: " << y);
    OUT("Z: " << z);

    // Convert the x and y values to the heading of the car
    // The arctanget function is used to determine the angle measures of a right triangle when the legs of the triangle are known
    // From polar coordinates

    angle = atan2((double)y, (double)x) * (180 / M_PI);

    if (angle < 0)
        angle += 360.0;
    if (angle > 360)
        angle -= 360.0;

    // Save angle for quick access
    MPU::setLastDirection((int)angle);

    return angle;
}

string MPU::returnOrientation()
{

    if (getLastDirection() > 337.25 || getLastDirection() < 22.5)
    {
        return "North";
    }
    else if (getLastDirection() > 292.5 && getLastDirection() < 337.25)
    {
        return "North-West";
    }
    else if (getLastDirection() > 247.5 && getLastDirection() < 292.5)
    {
        return "West";
    }
    else if (getLastDirection() > 202.5 && getLastDirection() < 247.5)
    {
        return "South-West";
    }
    else if (getLastDirection() > 157.5 && getLastDirection() < 202.5)
    {
        return "South";
    }
    else if (getLastDirection() > 112.5 && getLastDirection() < 157.5)
    {
        return "South-East";
    }
    else if (getLastDirection() > 67.5 && getLastDirection() < 112.5)
    {
        return "East";
    }
    else if (getLastDirection() > 0 && getLastDirection() < 67.5)
    {
        return "North-East";
    }
}

/***
 * Get the last measured direction
 ***/
int MPU::getLastDirection()
{
    return MPU::lastDirection;
}

/***
 * Set the last measured value
 ***/
void MPU::setLastDirection(int direction)
{
    MPU::lastDirection = direction;
}

extern "C"
{
    MPU* MPU_new() { return new MPU(); }
    void initMPU(MPU* compass) { compass -> mpuInit(); }
    int MPU_readAngle(MPU* compass) { return compass -> getCompassAngle(); }
}
