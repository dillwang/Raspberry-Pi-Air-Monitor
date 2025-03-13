# Home Air Quality Sensor Project on Raspberry Pi 5

## Overview
This project is an air quality monitoring system using the Raspberry Pi 5. It integrates multiple sensors to measure air quality parameters such as PM2.5, hazardous gas levels, temperature, humidity, and flame detection. The system also includes an LCD display, an RGB LED indicator, and a buzzer alarm for real-time feedback.

## Features
- **Hazardous Gas Detection**: Monitors gas levels and triggers an alert if high concentrations of hazardous gas is detected.
- **PM2.5/PM10 Sensor**: Measures particulate particle concentration in the air.
- **Temperature & Humidity Monitoring**: Uses a DHT11 sensor to read real-time temperature and humidity.
- **Flame Sensor**: Detects fire hazards and triggers an alarm.
- **RGB LED Indicator**: Displays different colors based on air quality levels.
- **Buzzer Alarm**: Provides an audible alert for hazardous conditions.
- **LCD Display**: Shows real-time sensor readings and status messages.
- **User Control Button**: Allows toggling between active monitoring and pause mode.

## Hardware Requirements
 1. MQ-135: Hazardous Gas Detection Module
 2. PMS5003: PM2.5/PM10 Sensor
 3. DHT11: Temperature & Humidity Sensor
 4. KY-026: Flame Sensor
 5. KY-009: 3-color SMD LED
 6. KY-006: Passive Buzzer
 7. I2C LCD2004: I2C LCD Display Module
 8. KY-004: Button Switch
- Raspberry Pi 5
- Wiring and Breadboard

## Software Requirements
- **Raspberry Pi OS**
- **wiringPi** (For GPIO handling)
- **softPwm** and **softTone**
- **pthread** (For multi-threading sensor operations)

## Installation & Setup
1. **Clone the Repository**
   ```bash
   git clone https://github.com/dillwang/Raspberry-Pi-Air-Monitor.git
   cd src
   ```

2. **Install Dependencies**
   ```bash
   sudo apt install wiringpi
   ```

3. **Compile the Code**
   ```bash
   make
   ```
   This will compile `main.c`, `work_threads.c`, and `lcd2004_lib.c` into an executable binary.

4. **Run the Program**
   ```bash
   sudo ./main
   ```

## Code Structure
- `main.c` - Main loop for runnning sensor threads.
- `work_threads.c` - Functions to read sensor data and control actuators.
- `work_threads.h` - Header file containing function declarations and shared data structures.
- `lcd2004_lib.c` - Library for controlling the LCD display.
- `Makefile` - Compilation instructions.

## How It Works
  - item On startup, the program initializes sensors and starts multiple threads for each sensor. For GPIO pins, sensors are set as INPUT, and actuators as OUTPUT. For serial and I2C, each of them are initialized with an access address.
  - item When running, each thread reads sensor data and updates sv (shared variable).
  - item Based on the reading of the sensor (1,2,3,4), the actuators (5,6,7,8) has the following response:
    - item The RGB LED changes color based on the level of PM2.5 concentration. Based on the hazard level, it changes from green, blue, yellow, to red.
    - item The buzzer activates if hazardous gas or flame is detected
    - item The LCD updates real-time reading of temperature & humidity, and the status of hazardous gas & flame detection.
    - item A button can be pressed to mute the buzzer if it is accidentally triggered.


## Expected Output
```
1. The hazardous gas value is: 0
2. PM1.0: 12 µg/m³, PM2.5: 20 µg/m³, PM10: 30 µg/m³
3. Temperature: 25°C, Humidity: 55%
4. Flame detection value: 0
5. SMD RGB LED: Green
6. Buzzer: Off
7. Displaying temperature & humidity, and hazardous gas and flame status
8. Button pressed: RUNNING
```

## Troubleshooting
- **LCD Not Displaying?**
  - Ensure I2C is enabled (`sudo raspi-config` > Interfacing Options > I2C > Enable).
- **Sensors Not Responding?**
  - Check wiring and sensor power connections.
  - Serial connector RX and TX should be mixed when wiring from Raspberry Pi to the sensor.
- **Compilation Errors?**
  - Ensure all dependencies are installed and `wiringPi` is properly set up.

## Authors
- **Ziying (Mark) Yan** - [Contact: z7yan@ucsd.edu]
- **Diyou Wang** - [Contact: diw011@ucsd.edu]

## Acknowledgments
- Sunfounder for LCD library.
- Raspberry Pi community for GPIO handling.
- The code is adapted from the individual assignment part 2, with many new features and modified logic.

