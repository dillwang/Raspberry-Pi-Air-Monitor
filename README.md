# Smart Air Quality Monitor with Integrated Homemade Air Purifier and Humidifier

## **Project Overview**
This project aims to develop a smart air quality monitoring system integrated with a homemade air purifier and humidifier. The system will continuously monitor air quality and humidity levels and automatically activate the air purifier or humidifier when conditions are suboptimal. Using a Raspberry Pi 5 and multiple sensors, the device will ensure a comfortable and healthy indoor environment by maintaining ideal air quality and moisture levels. The system will be voice-controllable through Amazon Alexa for added convenience and can provide real-time data through a web interface.

## **Objectives**
- Design a compact, low-cost, and efficient air quality monitoring system.
- Automatically activate the air purifier when harmful pollutants are detected.
- Control indoor humidity levels through a humidifier.
- Provide users with real-time air quality and humidity data through a web-based dashboard.
- Integrate with Alexa for voice control and automated routines.

## **Why This Project?**
Air quality and humidity are critical factors in maintaining a healthy indoor environment. With growing concerns over pollution and the increasing time people spend indoors, it is essential to monitor and improve indoor air quality efficiently. Commercial air purifiers and humidifiers often lack integrated, customizable monitoring systems and can be expensive. This project aims to provide a cost-effective, customizable, and fully automated alternative.

Additionally, this project offers an excellent opportunity to apply embedded systems design and IoT integration skills while addressing a real-world problem with significant health benefits. It combines sensor monitoring, software logic, and mechanical actuation in an intelligent, self-regulating system.

## **Challenges of This Project**
- **Sensor Accuracy & Calibration**: Ensuring precise measurements from air quality and humidity sensors requires proper calibration and placement to avoid false readings.
- **Automation Logic & Threshold Setting**: Defining appropriate activation thresholds for air purification and humidification to balance efficiency and power consumption.
- **Integration with Alexa**: Establishing a seamless interaction between the Raspberry Pi and Alexa for real-time voice commands and data retrieval.
- **Hardware Reliability & Efficiency**: Designing an effective and long-lasting air purifier with an optimized fan and HEPA filter while ensuring minimal noise and power consumption.
- **Data Logging & Visualization**: Creating an intuitive dashboard for users to monitor historical air quality trends and make informed decisions.
- **Power Management & Safety**: Implementing efficient power handling, especially for components like fans and mist modules, to avoid overheating or excessive energy usage.

## **Importance of Air Quality and Humidity**
### **Air Quality:**
Poor indoor air quality can cause or exacerbate a wide range of health issues, including:
- Respiratory problems such as asthma and bronchitis.
- Allergic reactions due to airborne particles like dust, pollen, and pet dander.
- Long-term health risks due to exposure to harmful pollutants like VOCs (volatile organic compounds) and PM2.5 particles.

### **Humidity:**
Maintaining the right level of humidity is equally important:
- **Low humidity** can cause dry skin, respiratory discomfort, and increased vulnerability to viruses.
- **High humidity** can lead to mold growth, dust mites, and other allergens.

Optimal humidity levels (between 40% and 60%) promote a healthier indoor environment and prevent conditions that can aggravate allergies and respiratory problems.

## **Project Details**
### **Sensors and Components:**
- **MQ-135 Air Quality Sensor:** Monitors CO2, ammonia, and other harmful pollutants.
- **PM2.5 Sensor:** Measures fine particulate matter.
- **DHT22 Sensor:** Monitors temperature and humidity.
- **Raspberry Pi 5:** Acts as the central controller.
- **Homemade Air Purifier:** Uses a HEPA filter and a high-CFM computer fan.
- **Humidifier:** Controlled via a relay module for automated moisture regulation.

### **System Functionality:**
1. Sensors monitor air quality and humidity in real time.
2. When pollutants or low humidity are detected:
   - The air purifier activates if air quality falls below a set threshold.
   - The humidifier turns on if the humidity level is too low.
3. The system logs and displays sensor data on a web dashboard.
4. Integration with Alexa allows users to control the system through voice commands.

## **Expected Outcomes**
- A fully functional, cost-effective air quality monitor and automatic purifier/humidifier system.
- Real-time monitoring and logging of air quality and humidity.
- Voice control and automated routines via Alexa.
- Improved indoor air quality and a healthier living environment.

## **Project Timeline**
| Task                               | Duration     | Completion Date |
|------------------------------------|---------------|------------------|
| Requirements gathering & design   | 1 week        | Week 1           |
| Hardware setup                    | 2 weeks       | Week 3           |
| Software development & integration| 3 weeks       | Week 6           |
| Alexa integration                  | 1 week        | Week 7           |
| Testing & optimization             | 2 weeks       | Week 9           |
| Final report and presentation      | 1 week        | Week 10          |

## **Budget Estimate (Optional Section)**
| Component                         | Quantity | Cost (USD)       |
|------------------------------------|----------|------------------|
| Raspberry Pi 5                     | 1        | $75              |
| MQ-135 Air Quality Sensor          | 1        | $15              |
| DHT22 Temperature & Humidity Sensor| 1        | $10              |
| PM2.5 Sensor (PMS5003)             | 1        | $20              |
| HEPA Filter & Fan                  | 1        | $30              |
| Relay Module                       | 1        | $5               |
| Power Supply and Cables            | 1 set    | $10              |
| **Total**                          |          | **~$165**        |

## **Purchase List**
* item MQ-135: Hazardous Gas Detection Module
* item PMS5003: PM2.5/PM10 Sensor
* item DHT11: Temperature \& Humidity Sensor
* item KY-009: 3-color SMD LED
* item KY-006: Passive Buzzer
* item I2C LCD2004: I2C LCD Display Module

## Reference
* [https://pinout.xyz/pinout/i2c](https://pinout.xyz/pinout/i2c)
* [https://www.sunfounder.com/products/i2c-lcd2004-module](https://www.sunfounder.com/products/i2c-lcd2004-module)
* [http://wiki.sunfounder.cc/index.php?title=I2C_LCD2004](http://wiki.sunfounder.cc/index.php?title=I2C_LCD2004)


## **License**
This project is open-source and available under the MIT License.

---

Let me know if you want additional formatting changes or sections for GitHub-specific enhancements like installation instructions!

