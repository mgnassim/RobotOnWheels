#include <iostream>
#include <fstream>  // lib to open file
#include <string>   // to use find function
#include <stdlib.h> //to use atoi
#include <regex>
#include <string>
using namespace std;

class Temperature
{
public:
    string read_temp_raw()
    {
        fstream sensorFile;
        sensorFile.open("/sys/bus/w1/devices/28-01205469337e/w1_slave", ios::in); //read mode
        string raw_frame;
        if (sensorFile.is_open())
        {
            string line;
            while (getline(sensorFile, line))
            {
                raw_frame = line;

                regex regexp("t=(.+)");
                smatch m;
                regex_search(raw_frame, m, regexp);
                for (string x : m)
                {
                    raw_frame = x;
                }
            }
        }
        sensorFile.close();
        return raw_frame;
    }

    int readTemp()
    {
        int temperature = std::stoi(read_temp_raw());
        temperature = temperature / 1000;
        int temperature_round = temperature * 10;
        temperature_round = int(temperature_round);
        temperature_round /= 10;

        return temperature_round;
    }
};

extern "C"
{
    Temperature* Temperature_new() { return new Temperature(); }
    int Temperature_readTemp(Temperature* temperature) { return temperature -> readTemp(); }
}