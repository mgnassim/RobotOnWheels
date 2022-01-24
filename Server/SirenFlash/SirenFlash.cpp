#include <iostream>   //needed for
#include <wiringPi.h> // needed for usage Rpi
#include <fmod.h>     // needed for fmod
#include <cstddef>    // needed for null
#include <fmod.hpp>   // needed for fmod
#include <stdio.h>    // needed for printf
#include <thread>     // needed for threading
#include <unistd.h>   // needed functions
#include <conio.h>    // needed for getch
#include <string>
using namespace std;

class Siren
{

    FMOD::System *system; //null pointers
    FMOD::Sound *sound;   //Address of a variable to receive a newly created FMOD::Sound object.
    FMOD::Channel *channel;

public:
    const int pinBlue = 29; // declared GPIOpin for led
    bool playing = true;

    Siren()
    {
        wiringPiSetup();
        FMOD::System_Create(&system);         // Create the main system object.
        system->init(5, FMOD_INIT_NORMAL, 0); // Initialize FMOD.
        system->createStream("/home/pi/app_control/SirenFlash/s.mp3", FMOD_DEFAULT, 0, &sound);
    }

    void play()
    {
        playing = true;
        system->playSound(sound, NULL, true, &channel);
        channel->setVolume(3);
        channel->setPaused(false);
    }

    void flash()
    {
        while (playing)
        {
            pinMode(pinBlue, OUTPUT); // Configure GPIO0 as an output

            digitalWrite(pinBlue, 1);
            delay(750); // Delay 500ms
            digitalWrite(pinBlue, 0);
            delay(600); // Delay 500ms
        }
    }

    void off()
    {
        playing = false;
        digitalWrite(pinBlue, 0);
        channel->setPaused(true);
    }
};

extern "C"
{
    Siren *Siren_new() { return new Siren(); }
    void Siren_playSiren(Siren *siren) { siren->play(); }
    void Siren_playFlash(Siren *siren) { siren->flash(); }
    void Siren_turnOff(Siren *siren) { siren->off(); }
}