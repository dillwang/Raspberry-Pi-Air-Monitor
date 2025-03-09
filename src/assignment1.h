/*
Description:
Name:
Email:
Date:
*/

#ifndef _ASSIGNMENT_BODY_
#define _ASSIGNMENT_BODY_

#include <stdint.h>

// Macros
#define TURN_ON(pin) digitalWrite(pin, 1)
#define TURN_OFF(pin) digitalWrite(pin, 0)

#define READ(pin) digitalRead(pin)
#define WRITE(pin, x) digitalWrite(pin, x)

// Constants
#define RUNNING 3
#define PAUSE 2

#define LOW 0
#define HIGH 1

#define CLOCKWISE 0
#define COUNTER_CLOCKWISE 1

#define NO_SOUND 0
#define DETECT_SOUND 1

#define IDLE 0
#define GREEN 1
#define RED 2
#define BLUE 3

// Pin number definitions
// Total: 8 sensors

// 1. Hazardous gas sensor
#define PIN_HAZA_GAS 8

// 2. PM2.5/PM10 sensor
#define PIN_PM25

// 3. DHT11 temperature& humidity sensor
#define PIN_TEMP_HUM 9

// 4. Flame sensor
#define PIN_FLAME 7

// 5. SMD RGB LED (Surface Mount Device)
#define PIN_SMD_RED 27
#define PIN_SMD_GRN 28
#define PIN_SMD_BLU 29

// 6. Passive Buzzer
#define PIN_BUZZER 25

// 7. LCD display

// 8. Button
#define PIN_BUTTON 24

typedef struct shared_variable {
    int bProgramExit; // Once set to 1, the program will terminate.


} SharedVariable;

// Initiating shared variables
void init_shared_variable(SharedVariable *sv);
void init_sensors(SharedVariable *sv);

// 1. Hazardous gas sensor
// 2. PM2.5/PM10 sensor
// 3. DHT11 temperature& humidity sensor
// 4. Flame sensor
// 5. SMD RGB LED (Surface Mount Device)
// 6. Passive Buzzer
// 7. LCD display
// 8. Button

// Initiating body functions for the sensors
void body_haza_gas(SharedVariable *sv);
void body_PM25(SharedVariable *sv);
void body_temp_hum(SharedVariable *sv);
void body_flame(SharedVariable *sv);
void body_rgbcolor(SharedVariable *sv);
void body_buzzer(SharedVariable *sv); 
void body_display(SharedVariable *sv)
void body_button(SharedVariable *sv);

#endif
