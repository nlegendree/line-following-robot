#include "gpio_pin.h"

#include <wiringPi.h>
#include <stdio.h>

int main(void) {
    if (wiringPiSetupGpio() == -1) {
        printf("Échec de l'initialisation de wiringPi. Vérifiez vos privilèges.\n");
        return 1;
    }

    pinMode(PIN_LINEFINDER, INPUT);

    while (1) {
        int lineDetected = digitalRead(PIN_LINEFINDER);

        if (lineDetected == LOW) {
            printf("Ligne détectée\n");
        } else {
            printf("Ligne non détectée\n");
        }

        delay(100); // Attendre 100 millisecondes avant de lire à nouveau
    }

    return 0;
}

