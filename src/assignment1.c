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
#define MAX_TIMINGS 85

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

    int success = readDHT11(PIN_TEMP_HUM, sv->temperature, sv->humidity);
    printf("the operation was %d, temperature is %d, humidity is %d", success, sv->temperature, sv->humidity);
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



// Reads data from a DHT11 sensor connected to 'pin'.
// On success, fills in temperature and humidity and returns 1.
// On failure, returns 0.
int readDHT11(int pin, int *temperature, int *humidity) {
    int data[5] = {0, 0, 0, 0, 0};
    int lastState = HIGH;
    int counter = 0;
    int j = 0;

    // Step 1. Send start signal: pull the pin LOW for at least 18ms.
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(18); // 18ms delay

    // Step 2. Pull pin HIGH for 40 microseconds.
    digitalWrite(pin, HIGH);
    delayMicroseconds(40);

    // Step 3. Set pin to input mode to read the sensor response.
    pinMode(pin, INPUT);

    // Read the timings for each bit.
    for (int i = 0; i < MAX_TIMINGS; i++) {
        counter = 0;
        while (digitalRead(pin) == lastState) {
            counter++;
            delayMicroseconds(1);
            if (counter == 255)
                break;
        }
        lastState = digitalRead(pin);

        // The first few transitions are part of the sensor's response signal.
        if (i >= 4 && (i % 2 == 0)) {
            data[j/8] <<= 1;
            // If the high pulse was long, it's a 1; if short, it's a 0.
            if (counter > 30)
                data[j/8] |= 1;
            j++;
        }
    }

    // We should have received 40 bits (5 bytes) of data.
    if (j >= 40) {
        int checksum = data[0] + data[1] + data[2] + data[3];
        if ((checksum & 0xFF) == data[4]) {
            *humidity = data[0];      // Integral part of humidity.
            *temperature = data[2];   // Integral part of temperature.
            return 1;
        } else {
            // Checksum failed.
            return 0;
        }
    }
    return 0;
}
