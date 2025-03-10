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
#include <softPwm.h>
#include <softTone.h>
//#include <dht.h>
//#include "MQ135.h"

//MQ135 gasSensor = MQ135(PIN_HAZA_GAS);


void init_shared_variable(SharedVariable* sv) {
    sv->bProgramExit = 0;
    sv->temperature = 0;
    sv->humidity = 0;
    sv->button = RUNNING;
    sv->buzzerOn = 0;


}

void ledInit(void) {
    //initialize SMD and DIP
    softPwmCreate(PIN_SMD_RED, 0, 0xff);
    softPwmCreate(PIN_SMD_BLU, 0, 0xff);
    softPwmCreate(PIN_SMD_GRN, 0, 0xff);
}


void init_sensors(SharedVariable* sv) {
    ledInit();

    //output pins
    //pinMode(PIN_ALED, OUTPUT);
    softToneCreate(PIN_BUZZER);


    //input pins
    pinMode(PIN_FLAME, INPUT);
    pinMode(PIN_TEMP_HUM, INPUT);
    pinMode(PIN_HAZA_GAS, INPUT);
    //pinMode(PIN_PM25, INPUT);
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_BUTTON, INPUT);

}

// 1. Hazardous gas sensor
void body_haza_gas(SharedVariable *sv)
{   
    //float ppm = gasSensor.getPPM();
    int ppm = READ(PIN_HAZA_GAS);
    printf("the gas value is %d", ppm);
}

// 2. PM2.5/PM10 sensor
void body_PM25(SharedVariable *sv)
{

}

// 3. DHT11 temperature& humidity sensor
void body_temp_hum(SharedVariable *sv)
{
    /*
    int temp_hum = DHT.read11(PIN_TEMP_HUM);
    sv->humidity = DHT.humidity;
    sv->temperature = DHT.temperature;
    */
}

// 4. Flame sensor
void body_flame(SharedVariable *sv)
{
    sv->flameOn = READ(PIN_FLAME);
}

// 5. SMD RGB LED (Surface Mount Device)
void body_rgbcolor(SharedVariable *sv)
{
    
}

// 6. Passive Buzzer
void body_buzzer(SharedVariable *sv)
{
    /*
    if (sv->button == RUNNING) {
        if(sv->buzzerOn == 1) {
            unsigned long curTime = millis();
            if (curTime - sv->buzzerTime < 3000) {
                int newTone = 3000 - (curTime - sv->buzzerTime);
                if (newTone % 100 > 50) {
                    newTone = 1000;
                } else {
                    newTone = 1500;
                }
                softToneWrite(PIN_BUZZER, newTone);
            } else {
                softToneWrite(PIN_BUZZER, 0);
                sv->buzzerOn = 0;
            }
        }
    }
    */
}

// 7. LCD display
void body_display(SharedVariable *sv)
{

}

// 8. Button
void body_button(SharedVariable *sv)
{
    int buttonRead = READ(PIN_BUTTON);
    static int lastRead = HIGH;

    if (lastRead == LOW && buttonRead == HIGH) {
        if (sv->button == RUNNING) {
            sv->button = PAUSE;
        } else {
            sv->button = RUNNING;
        }
    }

    lastRead = buttonRead;
}
