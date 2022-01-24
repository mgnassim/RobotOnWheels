#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <unistd.h>

void goForwards(int fd); //prototype
void goBackwards(int fd); //prototype
void stop(int fd); //prototype
void goLeft(int fd); //prototype
void goRight(int fd); //prototype
static int fd = wiringPiI2CSetup(0x32);

class Movement {
    public:
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
};

extern "C" {
    Movement* Movement_new(){ return new Movement(); }
    void Movement_goForwards(Movement* move){ move -> goForwards(fd); }
    void Movement_goBackwards(Movement* move){ move -> goBackwards(fd); }
    void Movement_goRight(Movement* move){ move -> goRight(fd); }
    void Movement_goLeft(Movement* move){ move -> goLeft(fd); }
    void Movement_stop(Movement* move){ move -> stop(fd); }
}
