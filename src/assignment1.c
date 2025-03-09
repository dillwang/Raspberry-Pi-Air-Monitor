/*
Name:
Email:
Date:
*/
#include "assignment1.h"
#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include <wiringPi.h>
//#include <softPwm.h>
#include <softTone.h>


void init_shared_variable(SharedVariable* sv) {
    sv->bProgramExit = 0;

}


void init_sensors(SharedVariable* sv) {
    ledInit();

    //output pins
    pinMode(PIN_ALED, OUTPUT);
    //input pins

}

// 1. Hazardous gas sensor
void body_haza_gas(SharedVariable *sv)
{
}

// 2. PM2.5/PM10 sensor
void body_PM25(SharedVariable *sv)
{
}

// 3. DHT11 temperature& humidity sensor
void body_temp_hum(SharedVariable *sv)
{
}

// 4. Flame sensor
void body_flame(SharedVariable *sv)
{
}

// 5. SMD RGB LED (Surface Mount Device)
void body_rgbcolor(SharedVariable *sv)
{
}

// 6. Passive Buzzer
void body_buzzer(SharedVariable *sv)
{
}

// 7. LCD display
void body_display(SharedVariable *sv)
{
}

// 8. Button
void body_button(SharedVariable *sv)
{
}
