// Important! DO NOT MODIFY this file.
// You will not submit this file.
// This file is provided for your understanding of the program procedure.

// Skeleton code of CSE237A, Sensor interaction
// For more details, please see the instructions on the class website.

#include <stdio.h>
#include <pthread.h>
#include <wiringPi.h>
#include <softPwm.h>
#include "assignment1.h"

// Thread declaration macros
#define thread_decl(NAME) \
void* thread_##NAME(void* param) { \
	SharedVariable* pV = (SharedVariable*) param; \
	body_##NAME(pV); \
	return NULL; }

// Declare threads for each sensor/actuator function
thread_decl(haza_gas)
thread_decl(PM25)
thread_decl(temp_hum)
thread_decl(flame)
thread_decl(rgbcolor)
thread_decl(buzzer)
thread_decl(display)
thread_decl(button)

// Thread creation and joining macros
#define thread_create(NAME) pthread_create(&t_##NAME, NULL, thread_##NAME, &v);
#define thread_join(NAME) pthread_join(t_##NAME, NULL);

int main(int argc, char* argv[]) {
	// Initialize shared variable
	SharedVariable v;

	// Initialize WiringPi library
	if (wiringPiSetup() == -1) {
		printf("Failed to setup wiringPi.\n");
		return 1; 
	}

	// Initialize shared variable and sensors
	init_shared_variable(&v);
	init_sensors(&v);

	// Thread identifiers
	pthread_t t_haza_gas,
			  t_PM25,
			  t_temp_hum,
			  t_flame,
			  t_rgbcolor,
			  t_buzzer,
			  t_display,
			  t_button;

	// Main program loop
	while (v.bProgramExit != 1) {
		// Create sensing threads
		thread_create(haza_gas);
		thread_create(PM25);
		thread_create(temp_hum);
		thread_create(flame);
		thread_create(rgbcolor);
		thread_create(buzzer);
		thread_create(display);
		thread_create(button);

		// Wait for all threads to finish
		thread_join(haza_gas);
		thread_join(PM25);
		thread_join(temp_hum);
		thread_join(flame);
		thread_join(rgbcolor);
		thread_join(buzzer);
		thread_join(display);
		thread_join(button);

		// Add a slight delay between iterations
		delay(10);
	}

	printf("Program finished.\n");

	return 0;
}
