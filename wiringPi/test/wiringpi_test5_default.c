// WiringPi test program: Kernel char device interface / sysfs successor
// Compile: gcc -Wall wiringpi_test1_device.c -o wiringpi_test1_device -lwiringPi

#include "wpi_test.h"
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>


const int GPIO = 19;
const int GPIOIN = 26;
const int ToggleValue = 4;


int main (void) {

	printf("WiringPi GPIO test program 1 (using GPIO%d (output) and GPIO%d (input))\n", GPIO, GPIOIN);
	printf(" testing digitalWrite, digitalRead and pullUpDnControl\n");

	if (wiringPiSetupGpio()  == -1) {
		printf("wiringPiSetupGpio failed\n\n");
		exit(EXIT_FAILURE);
	}
	pinMode(GPIOIN, INPUT);
	pinMode(GPIO, OUTPUT);

	printf("toggle %d times ...\n", ToggleValue);
	for (int loop=1; loop<ToggleValue; loop++) {
		digitalWriteEx(GPIO, GPIOIN, LOW);
		delayMicroseconds(600000);
		digitalWriteEx(GPIO, GPIOIN, HIGH);
		delayMicroseconds(600000);
	}

	digitalWrite(GPIO, LOW);

	printf("\nWiringPi GPIO test program (using GPIO%d (input pull up/down) and GPIO%d (input))\n", GPIO, GPIOIN);
	pullUpDnControl (GPIO, PUD_UP);
	pinMode(GPIO, INPUT);
	delayMicroseconds(3000000);
	pullUpDnControl (GPIOIN, PUD_OFF);

     for (int loop=1; loop<ToggleValue; loop++) {
		pullUpDnControlEx (GPIO, GPIOIN, PUD_DOWN);
		delayMicroseconds(600000);
		pullUpDnControlEx (GPIO, GPIOIN, PUD_UP);
		delayMicroseconds(600000);
    }

	//Error wrong direction - only for fun
	digitalWrite(GPIO, LOW);

	return(EXIT_SUCCESS);
}

