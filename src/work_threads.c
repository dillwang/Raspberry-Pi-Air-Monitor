/*
Description:
-Work threads function for final project of CSE 147 WI25
-Adapted from the individual assignment part 2
Name: Ziying (Mark) Yan & Diyou Wang
Email: z7yan@ucsd.edu & diw011@ucsd.edu
Date: 3/11/2025
*/

#include "work_threads.h"
#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <softTone.h>

#include <wiringSerial.h>
#include <unistd.h>
#include "lcd2004_lib.c"

#define MAX_TIMINGS 85
#define SERIAL_PORT "/dev/ttyAMA0" // UART Serial Port on Raspberry Pi

void init_shared_variable(SharedVariable *sv)
{
    sv->bProgramExit = 0;
    sv->temperature = 0;
    sv->humidity = 0;
    sv->pm1_0 = 0;
    sv->pm2_5 = 0;
    sv->pm10 = 0;
    sv->button = PAUSE;
    sv->gasOn = LOW;
    sv->flameOn = LOW;
}

void ledInit(void) {
    //initialize SMD and DIP
    softPwmCreate(PIN_SMD_RED, 0, 0xff);
    softPwmCreate(PIN_SMD_BLU, 0, 0xff);
    softPwmCreate(PIN_SMD_GRN, 0, 0xff);
}

void init_sensors(SharedVariable* sv) {
    //output pins
    //ledInit();
    softToneCreate(PIN_BUZZER);
        
    pinMode(PIN_SMD_RED, OUTPUT);
    pinMode(PIN_SMD_BLU, OUTPUT);
    pinMode(PIN_SMD_GRN, OUTPUT);
    
    //input pins
    pinMode(PIN_FLAME, INPUT);
    pinMode(PIN_TEMP_HUM, INPUT);
    pinMode(PIN_HAZA_GAS, INPUT);
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_BUTTON, INPUT);

    //init LCD display
    fd = wiringPiI2CSetup(LCDAddr);
    init();
}
// -------- Helper Functions --------

//Reads pms5003 for air quality data
//Stores at sv
void read_pms5003(int fd, int *sv_pm1_0, int *sv_pm2_5, int *sv_pm10)
{
    unsigned char buffer[32];
    
    //printf("serialdata: %d\n", serialDataAvail(fd));

    int stop = 0;
    while (stop == 0)
    {
        if (serialDataAvail(fd) >= 32)
        { // Read 32 bytes from the sensor
            for (int i = 0; i < 32; i++)
            {
                buffer[i] = serialGetchar(fd);
            }

            // Check if packet starts with correct header (0x42, 0x4D)
            if (buffer[0] == 0x42 && buffer[1] == 0x4D)
            {
                int pm1_0 = (buffer[4] << 8) | buffer[5];
                int pm2_5 = (buffer[6] << 8) | buffer[7];
                int pm10 = (buffer[8] << 8) | buffer[9];

                *sv_pm1_0 = pm1_0;
                *sv_pm2_5 = pm2_5;
                *sv_pm10 = pm10;

                stop ++;
            }
        }
        //only run once
        //stop ++;
    }
}

//Reads data from DHT11 sensor
//If success, fills in temperature and humidity and returns 1.
//If failure, returns 0.
int readDHT11(int pin, int *temperature, int *humidity) {
    int data[5] = {0, 0, 0, 0, 0};
    int lastState = HIGH;
    int counter = 0;
    int j = 0;

    //pull the pin LOW for 18ms.
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(18);

    //pull pin HIGH for 40 ms
    digitalWrite(pin, HIGH);
    delayMicroseconds(40);

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

        if (i >= 4 && (i % 2 == 0)) {
            data[j/8] <<= 1;
            if (counter > 30)
                data[j/8] |= 1;
            j++;
        }
    }

    //should have received 40 bits
    if (j >= 40) {
        int checksum = data[0] + data[1] + data[2] + data[3];
        if ((checksum & 0xFF) == data[4]) {
            *humidity = data[0];
            *temperature = data[2];
            return 1;
        } else {
            // checksum failed
            return 0;
        }
    }
    return 0;
}

// -------- Thread Functions --------

// 1. Hazardous gas sensor
void body_haza_gas(SharedVariable *sv)
{   
    int ppm = READ(PIN_HAZA_GAS);

    if (ppm == LOW)
    {
        sv->gasOn = HIGH;
    }

    printf("1. The hazardous gas value is: %d\n", ppm);
}

// 2. PM2.5/PM10 sensor
void body_PM25(SharedVariable *sv)
{
    // Open serial port
    int fd = serialOpen(SERIAL_PORT, 9600);

    if (fd < 0)
    {
        fprintf(stderr, "Error opening serial port\n");
    }
    
    //printf("Reading MS5003 sensor data...\n");
    read_pms5003(fd, &sv->pm1_0, &sv->pm2_5, &sv->pm10);
    printf("2. PM1.0: %d µg/m³, PM2.5: %d µg/m³, PM10: %d µg/m³\n", sv->pm1_0, sv->pm2_5, sv->pm10);

    // Close serial port
    serialClose(fd);
}

// 3. DHT11 temperature& humidity sensor
void body_temp_hum(SharedVariable *sv)
{
    int success = readDHT11(PIN_TEMP_HUM, &sv->temperature, &sv->humidity);
    printf("3. temperature is %d, humidity is %d \n", sv->temperature, sv->humidity);
}

// 4. Flame sensor
void body_flame(SharedVariable *sv)
{
    int flame = READ(PIN_FLAME);

    if (flame == HIGH)
    {
        sv->gasOn = HIGH;
    }

    printf("4. flame detection value: %d\n", flame);
}

// 5. SMD RGB LED
void body_rgbcolor(SharedVariable *sv)
{
    // Air quality: green
    if (sv->pm2_5 < 10)
    {
        WRITE(PIN_SMD_RED, 0x80);
        WRITE(PIN_SMD_GRN, 0xff);
        WRITE(PIN_SMD_BLU, 0x00);
        printf("5. SMD RGB LED: green\n");
    }

    // Air quality: yellow
    else if (sv->pm2_5 < 25)
    {
        WRITE(PIN_SMD_RED, 0x00);
        WRITE(PIN_SMD_GRN, 0x00);
        WRITE(PIN_SMD_BLU, 0xFF);
        printf("5. SMD RGB LED: blue\n");
    }

    else if (sv->pm2_5 < 45)
    {
        WRITE(PIN_SMD_RED, 0xFF);
        WRITE(PIN_SMD_GRN, 0xA0);
        WRITE(PIN_SMD_BLU, 0x00);
        printf("5. SMD RGB LED: yellow\n");
    }

    else
    {
        WRITE(PIN_SMD_RED, 0xFF);
        WRITE(PIN_SMD_GRN, 0x00);
        WRITE(PIN_SMD_BLU, 0x00);
        printf("5. SMD RGB LED: red\n");
    }

}

// 6. Passive Buzzer
void body_buzzer(SharedVariable *sv)
{

    if (sv->button == PAUSE) {
        softToneWrite(PIN_BUZZER, 0);
        printf("6. Buzzer off\n");
    }

    else if (sv->gasOn == HIGH || sv->flameOn == HIGH) {
        softToneWrite(PIN_BUZZER, 1000);
        //sv->button == RUNNING;
        printf("6. Buzzer On\n");
    }

}

// 7. LCD display
void body_display(SharedVariable *sv)
{
    
    char msg1[30];
    sprintf(msg1, "Temperature: %d", sv->temperature);
    
    char msg2[30];
    sprintf(msg2, "Humidity: %d", sv->humidity);
    
    write_data(0, 0, msg1);
    write_data(0, 1, msg2);

    if (sv->gasOn == LOW){
        write_data(20, 0, "Gas: Safe");
    }
    else {
        write_data(20, 0, "Gas: Detected!");
    }    
    
    if (sv->flameOn == LOW){
        write_data(20, 1, "Flame: Safe");
    }
    else {
        write_data(20, 1, "Flame: Detected!"); 
    }

    printf("6. Displaying temperature & humidity, and hazardous gas and flame status\n");
}

// 8. Button
void body_button(SharedVariable *sv)
{
    int buttonRead = READ(PIN_BUTTON);
    static int lastRead = HIGH;
    

    if (lastRead == LOW && buttonRead == HIGH) {
        if (sv->button == RUNNING) {
            sv->button = PAUSE;
            printf("8. Button pressed: PAUSE\n");
        } 
        else {
            sv->button = RUNNING;
            printf("8. Button pressed: RUNNING\n");
        }

    }
    lastRead = buttonRead;
}
