/***
 * Code for siren 
 *To play audio we need the FMOD lib to make it possible. FMOD is a proprietary sound effects engine and authoring tool for video games and applications developed by Firelight Technologies.
 ***/



#include <iostream>   //needed for inpot ouput
#include <wiringPi.h> // needed for usage Rpi
#include <fmod.h>     // needed for fmod
#include <cstddef>    // needed for null
#include <fmod.hpp>   // needed for fmod
#include <unistd.h>   // needed functions



class Siren
{

    FMOD::System *system; // pointer to store Address of a variable of newly created FMOD::System object.
    FMOD::Sound *sound;   //pointer to store Address of a variable of newly created FMOD::Sound object.
    FMOD::Channel *channel; //pointer to store Address of a variable of newly created FMOD::Channel object.
    
    //var
    const int PIN_BLUE = 29; // declared GPIOpin for led
    bool playing = true; // Bool for flashing LED while siren is on
    const int MAX_CH = 1; // The maximum number of channels to be used in FMOD.
    int FMOD_VOL = 5; // Value for volume between low-high 1-10
    int ON =1; //High
    int OFF =0; //LOW

    /* FMOD param */
    // MAX_CH 1 /* The maximum number of channels to be used in FMOD.*/ 
    //fmod_flag      /* This can be a selection of flags to change the behaviour of FMOD at initialization time.*/
    //OPPT           /* Optional. Specify 0 or NULL to ignore*

public:

    /***
 * initalise and set default values
 * Check for errors
***/
    Siren()
    {
        wiringPiSetup(); //for GPIO
        FMOD::System_Create(&system); // Create the main system object.
        system->init(MAX_CH, FMOD_INIT_NORMAL, NULL); // Initialize FMOD : (max_ch,fmod_flag,OPPT)
        
        //param: (file,fmod_flag,OPPT,Address of a variable for storage object)
        system->createStream("/home/pi/app_control/SirenFlash/s.mp3", FMOD_DEFAULT, NULL, &sound); 
        //open and load  the file, and pre-buffer a small amount of data so that it will be able to play

    }


    /***
 * play audio
***/

    void play()
    {
        playing = true;//set bool true

        system->playSound(sound, NULL, true, &channel); //param: (*sound,OPPT,paused,addres channel)
        channel->setVolume(FMOD_VOL);
        channel->setPaused(false);
    }

    /***
 * Flash led on of on the beat while playing audio
***/

    void flash()
    {
        pinMode(pinBlue, OUTPUT); // Configure GPIO0 as an output
        while (playing)
        {
            digitalWrite(PIN_BLUE, ON); //turn on
            delay(750); // Delay 750ms 
            digitalWrite(PIN_BLUE, OFF); // turn of
            delay(600); // Delay 600ms 
        }
    }


    /***
 * turn audio and led of
***/
    void off()
    {
        playing = false;
        digitalWrite(PIN_BLUE, OFF);
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
