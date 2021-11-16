//
// Created by bilal on 6-10-2021.
//
#include <fstream>//ifstream in c++ is a stream class which stands for input file stream.This is used for reading data from file.
#include <string>
#define KY001_Signal_PIN 4

path_to_sensor = "/sys/bus/w1/devices/28-01205434fbd3/w1_slave"

void read_temp_raw();
void read_temp();