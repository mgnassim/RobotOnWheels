//
// Created by bilal on 8-10-2021.
//
#include <iostream>
#include <fstream> // lib to open file
#include <string> // to use find function
#include <stdlib.h> //to use atoi
using namespace std;


//#include "TempS.h"



string read_temp_raw(){
    fstream sensorFile;
    sensorFile.open("/sys/bus/w1/devices/28-01205434fbd3/w1_slave",ios::in);//read mode
    string raw_frame;
    if (sensorFile.is_open()) {
        string line;
        while (getline(sensorFile,line)){
            raw_frame=line;
        }
    }
    sensorFile.close();
    return raw_frame;

    }

float read_temp(){
    read_temp_raw();
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
        cout << "gemeten tempratuur is: " << read_temp() << "\n";
    }

    return 0;
}