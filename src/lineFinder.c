#include <wiringPi.h>
#include <stdio.h>

#define LINE_FINDER_PIN 17 // Utilisez le numéro de la broche GPIO correct

int main(void) {
    if (wiringPiSetupGpio() == -1) {
        printf("Échec de l'initialisation de wiringPi. Vérifiez vos privilèges.\n");
        return 1;
    }

    pinMode(LINE_FINDER_PIN, INPUT);

    while (1) {
        int lineDetected = digitalRead(LINE_FINDER_PIN);

        if (lineDetected == LOW) {
            printf("Ligne détectée\n");
        } else {
            printf("Ligne non détectée\n");
        }

        delay(100); // Attendre 100 millisecondes avant de lire à nouveau
    }

    return 0;
}

