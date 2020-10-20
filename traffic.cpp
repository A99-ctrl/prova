#include <iostream>
#include <wiringPi.h>


using namespace std;

///
/// Configuration
///

const int BlinkErrorMs = 1000;

//faccio il setup delle porte dei led, del vettore con i tempi e dello stato dei led se sono accesi o spenti
//rosso->verde->giallo
const int led_rosso = 0;
const int led_verde = 1;
const int led_giallo = 2;
//                    ros   ver    gia
const int timeMs[] = {5000, 5000, 3000};
//bool status[] = {false, false, false};
///
/// Utils
///
void init()
{
    wiringPiSetup();
    pinMode(led_rosso, OUTPUT);
    pinMode(led_verde, OUTPUT);
    pinMode(led_giallo, OUTPUT);
}

void startOff(){
    digitalWrite(led_rosso, false);
    digitalWrite(led_verde, false);
    digitalWrite(led_giallo, false);
    }

/*void setLed(int ledNumber)
{
    if (ledNumber == led_rosso){
        digitalWrite(led_rosso, true);
        delay(timeMs[0]);
        digitalWrite(led_rosso, false);
    }
    else if (ledNumber == led_verde){
        digitalWrite(led_verde, true);
        delay(timeMs[1]);
    }
    else if (ledNumber == led_giallo){
        digitalWrite(led_giallo, true);
        delay(timeMs[2]);
        digitalWrite(led_giallo, false);
        digitalWrite(led_verde, false);
    }
}*/

void NextStatus(int led_number){
    switch (led_number){
        case 0: {
            digitalWrite(led_rosso, true);
            delay(timeMs[0]);
            digitalWrite(led_rosso, false);
        }break;
        case 1: {
            digitalWrite(led_verde, true);
            delay(timeMs[1]);
        }break;
        case 2: {
            digitalWrite(led_giallo, true);
            delay(timeMs[2]);
            digitalWrite(led_giallo, false);
            digitalWrite(led_verde, false);
        }break;
    }
}

void Error()
{
    while(1)
    {
        delay(BlinkErrorMs);
        digitalWrite(led_giallo, true);
        delay(BlinkErrorMs);
        digitalWrite(led_giallo, false);
    } // error loop
}
///
///Main cycle
///
int main()
{
    init();
    startOff();
    unsigned int count = 0;
    while(1)
    {
        NextStatus(led_rosso);
        NextStatus(led_verde);
        NextStatus(led_giallo);
        //Increment timer counter
        count++;
        //start error after 3 full cycle
        if(count > 1)
        {
            Error();
        }
    } // main loop
}
