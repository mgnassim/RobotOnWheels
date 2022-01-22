#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;

class Ultrasonic {
    public:
        int returnDistance() {

            wiringPiI2CWriteReg8(wiringPiI2CSetup(0x70),00, 81);
            sleep(1);
            return wiringPiI2CReadReg8(wiringPiI2CSetup(0x70),3);
            
    }
};

int main(){

    Ultrasonic ultrasonic;

    ultrasonic.returnDistance();

    return 0;

}

extern "C" {
    Ultrasonic* Ultrasonic_new(){ return new Ultrasonic(); }
    int Ultrasonic_returnDistance(Ultrasonic* ultrasonic){ return ultrasonic -> returnDistance(); }
}
