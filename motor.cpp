#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

//using namespace std::this_thread; // sleep_for, sleep_until
//using namespace std::chrono; // nanoseconds, system_clock, second

void goForwards(int fd); //prototype
void goBackwards(int fd); //prototype
void stop(int fd); //prototype
void goLeft(int fd); //prototype
void goRight(int fd); //prototype

int main() {
    int fd;
    fd = wiringPiI2CSetup(0x32);

    char ch=0;

    cin >> ch;

    do
    {
        switch(ch)
        {
            case 'W':
            case 'w':
                goForwards(fd);
                break;
            case 'A':
            case 'a':
                goLeft(fd);
                break;
            case 's':
            case 'S':
                goBackwards(fd);
                break;
            case 'D':
            case 'd':
                goRight(fd);
                break;

        }

    } while (ch != 'Q' && ch!='q');
}

//    goForwards(fd);
//    sleep_for(seconds(1));
//    stop(fd);
//    goBackwards(fd);
//    sleep_for(seconds(1));
//    stop(fd);
//    goRight(fd);
//    sleep_for(seconds(1));
//    stop(fd);
//    goLeft(fd);
//    sleep_for(seconds(1));
//    stop(fd);


void goForwards(int fd) {
    unsigned char arr[7] = {7, 3, 0x22, 1, 3, 0x22, 1};
    write(fd, &arr[0], 7);
}

void stop(int fd) {
    unsigned char arr[7] = {7, 3, 0x22, 0, 3, 0x22, 0};
    write(fd, &arr[0], 7);
}

void goBackwards(int fd) {
    unsigned char arr[7] = {7, 3, 0x22, 2, 3, 0x22, 2};
    write(fd, &arr[0], 7);
}

void goLeft(int fd) {
    unsigned char arr[7] = {7, 3, 0x50, 2, 3, 0x50, 1};
    write(fd, &arr[0], 7);
}

void goRight(int fd) {
    unsigned char arr[7] = {7, 3, 0x50, 1, 3, 0x50, 0};
    write(fd, &arr[0], 7);
}
