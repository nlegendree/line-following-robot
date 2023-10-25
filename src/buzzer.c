#include <wiringPi.h>
#include <stdio.h>

#define BUZZER_PIN 17 // Utilisez le numéro de la broche GPIO correct

int main() {
    if (wiringPiSetupGpio() == -1) {
        printf("Échec de l'initialisation de WiringPi. Vérifiez vos privilèges.\n");
        return 1;
    }

    pinMode(BUZZER_PIN, OUTPUT);

    while (1) {
        // Activer le buzzer pour générer un signal sonore
        digitalWrite(BUZZER_PIN, HIGH);
        delay(1000); // Laisser le buzzer actif pendant 1 seconde
        // Désactiver le buzzer
        digitalWrite(BUZZER_PIN, LOW);
        delay(1000); // Attendre pendant 1 seconde
    }

    return 0;
}
