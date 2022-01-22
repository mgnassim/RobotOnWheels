#include <stdio.h>
#include <wiringPi.h>

#define POMP 1
#define HIGH 1
#define LOW 0

class WaterPump
{
public:
    WaterPump()
    {
        wiringPiSetup();
        pinMode(POMP, OUTPUT);
    }

    void shootWaterPump()
    {
        digitalWrite(POMP, HIGH);
    }

    void stopWaterPump()
    {
        digitalWrite(POMP, LOW);
    }
};

int main(void)
{
    WaterPump waterPump;
    waterPump.shootWaterPump();
    waterPump.stopWaterPump();
}

extern "C"
{
    WaterPump *WaterPump_new() { return new WaterPump(); }
    void WaterPump_shootWaterPump(WaterPump *waterPump) { waterPump->shootWaterPump(); }
    void WaterPump_stopWaterPump(WaterPump *waterPump) { waterPump->stopWaterPump(); }
}