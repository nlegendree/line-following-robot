#include "gpio_pin.h"

#include <wiringPi.h>
#include <stdio.h>

int main() {
    if (wiringPiSetupGpio() == -1) {
        printf("Échec de l'initialisation de WiringPi. Vérifiez vos privilèges.\n");
        return 1;
    }

    pinMode(PIN_BUZZER, OUTPUT);

    while (1) {
        // Activer le buzzer pour générer un signal sonore
        digitalWrite(PIN_BUZZER, HIGH);
        delay(1000); // Laisser le buzzer actif pendant 1 seconde
        // Désactiver le buzzer
        digitalWrite(PIN_BUZZER, LOW);
        delay(1000); // Attendre pendant 1 seconde
    }

    return 0;
}
