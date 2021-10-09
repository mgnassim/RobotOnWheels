//
// Created by bilal on 8-10-2021.
//
#include <iostream>
#include <fstream> // to open file ( the sensor here)
#include <string> // to use find function
#include <stdlib.h> //to use atoi
using namespace std;


//#include "TempS.h"



void read_temp_raw(){
    std::fstream sensor;
    sensor.open("/sys/bus/w1/devices/28-01205434fbd3/w1_slave")
    string raw_frame;
    sensor >> raw_frame;
    sensor.close();
    return raw_frame;

}
void read_temp(){
    string raw_frame = read_temp_raw();
    string str_temperature = raw_frame.substr( raw_frame.find_last_of("t=")+1 );

    float temperature = atoi( str_temperature.c_str() );
    temperature = temperature / 1000;
    float temperature_round = temperature * 10;
    temperature_round = int(temperature_round);
    temperature_round /= 10;

    return temperature_round;

}

int main(){


    while (true) {
        cout << "gemeten afstand is: " << temperature_round << "\n";
    }

    return 0;
};