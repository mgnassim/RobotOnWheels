#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPiSPI.h>
#include <iostream>

#define CS_MCP3208 8 //BCM_GPIO_8
#define SPI_CHANNEL 0
#define SPI_SPEED 1000000 //1MHz

class WaterSensor
{
public:
    WaterSensor()
    {
        if (wiringPiSetup() == -1)
        {
            fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
        }

        if (wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1)
        {
            fprintf(stdout, "wiringPiSPISetup Failed: %s\n", strerror(errno));
        }

        pinMode(CS_MCP3208, OUTPUT);
    }

    int read_mcp3208_adc(unsigned char adcChannel)
    {
        unsigned char buff[3];
        int adcValue = 0;

        buff[0] = 0x06 | ((adcChannel & 0x07) >> 2);
        buff[1] = ((adcChannel & 0x07) << 6);
        buff[2] = 0x00;

        digitalWrite(CS_MCP3208, 0); //Low : CS Active

        wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);

        buff[1] = 0x0F & buff[1];
        adcValue = (buff[1] << 8) | buff[2];

        digitalWrite(CS_MCP3208, 1); //High : CS Inactive
        std::cout << "AdcValue: " << adcValue << std::endl;
        return adcValue;
    }

    int returnMoistureValue()
    {
        int adcValue[8] = {0};

        int val;

        delay(1000);
        adcValue[2] = read_mcp3208_adc(0); //Moisture Sensor
        val = adcValue[2];
        std::cout << "Water value: " << val << std::endl;
        return val;
    }
};

extern "C"
{
    WaterSensor *WaterSensor_new() { return new WaterSensor(); }
    int WaterSensor_returnMoistureValue(WaterSensor *waterSensor) { return waterSensor->returnMoistureValue(); }
}