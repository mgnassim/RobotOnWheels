#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPiSPI.h>
#include <iostream>

#define CS_MCP3208 8 //BCM_GPIO_8//starts communication between devices and the conversion. 
#define SPI_CHANNEL 0// the channel of the slave(sensor).
#define SPI_SPEED 1000000 //1MHz clockspeed for communication between devices(master/slave).

class WaterSensor
{
public:
    WaterSensor()
    {
        if (wiringPiSetup() == -1)//if wiringPi fails print error.
        {
            fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));//to get a readable output string for the error number
        }

        if (wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1)//if wiringPisetup parameters fails print error.
        {
            fprintf(stdout, "wiringPiSPISetup Failed: %s\n", strerror(errno));//to get a readable string for the error number
        }

        pinMode(CS_MCP3208, OUTPUT);//tells processor to define pin as output.
    }

    int read_mcp3208_adc(unsigned char adcChannel)
    {
        unsigned char buff[3];
        int adcValue = 0;

        buff[0] = 0x06 | ((adcChannel & 0x07) >> 2);
        buff[1] = ((adcChannel & 0x07) << 6);
        buff[2] = 0x00;

        digitalWrite(CS_MCP3208, 0); //Low : CS Active

        wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);//read/write simultaneous on selected SPI-bus,SPI-data overwrite data in the buffer.

        buff[1] = 0x0F & buff[1];
        adcValue = (buff[1] << 8) | buff[2];

        digitalWrite(CS_MCP3208, 1); //High : CS Inactive
        std::cout << "AdcValue: " << adcValue << std::endl;//prints adcvalue of the sensor.
        return adcValue;// give back conversion value of sensor tru adc. 
    }

    int returnMoistureValue()
    {
        int adcValue[8] = {0};// 

        int val;

        delay(1000);
        adcValue[2] = read_mcp3208_adc(0);//adc values of sensor stored in
        val = adcValue[2];//stored sensor value of adc in val.
        std::cout << "Water value: " << val << std::endl;//print sensor value.
        return val;//gives back sensor value.
    }
};

extern "C"
{
    WaterSensor *WaterSensor_new() { return new WaterSensor(); }
    int WaterSensor_returnMoistureValue(WaterSensor *waterSensor) { return waterSensor->returnMoistureValue(); }
}
