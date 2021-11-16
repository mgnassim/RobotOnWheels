#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <unistd.h>
#include <stdio.h>
#include <conio.h>

void goForwards(int fd); //prototype
void goBackwards(int fd); //prototype
void stop(int fd); //prototype
void goLeft(int fd); //prototype
void goRight(int fd); //prototype

int main(){

    int fd;
    fd = wiringPiI2CSetup(0x32);


	while(1){

		char ch = getch();

			switch(ch) {

			case 'w':
				printf("W HAS CLICKED\n");
				goForwards(fd);
				break;

			case 's':
				printf("S HAS CLICKED\n");
				goBackwards(fd);
				break;

			case 'a':
				printf("A HAS CLICKED\n");
				goLeft(fd);
				break;

			case 'd':
				printf("D HAS CLICKED\n");
				goRight(fd);
				break;

			default:
				printf("HIJ IS GESTOPT\n");
				stop(fd);
				break;
			}
            if(read_distance()<20){
                cout << "gemeten afstand is: " << read_distance() << "\n";
                stop(fd);

            }
	}
	return 0;
}

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
int read_distance(int fd){
    int reg=00;// command register
    int data=81; //data command
    wiringPiI2CWriteReg8 (fd,reg, data);// write to register and give command
    sleep(1);//give sensor time to think
    int data = wiringPiI2CReadReg8 (fd,3);//read distance in cm
    return data;
}

