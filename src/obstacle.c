#include <wiringPi.h>
#include "obstacle.h"
#include "distance.h"
#include "buzzer.h"
#include "i2cLCD.h"

int obstacleDistance() {
    return getDistance(); // Utilise la fonction du capteur de distance
}

void obstacleDetect() {
    while (1) {
        int distance = obstacleDistance();

        if (distance < 5) { //Bug si obstacle trop proche (ne devrait pas arriver) valeur à 1200 environ à vérifier en TP.
            // Obstacle trop proche, arrête les moteurs
            // motors_stop();
            lcdClear(); //Les fonctions concernant le LCD ne fonctionnent pas pour l'instant à régler...
            lcdSetCursor(0, 0);
            lcdWrite("Obstacle proche!");
            buzzerOn();  // Active le buzzer
        } else {
            // Pas d'obstacle proche, redémarre les moteurs
            // motors_start();
            lcdClear();
            lcdSetCursor(0, 0);
            lcdWrite("Pas d'obstacle");
            buzzerOff();  // Désactive le buzzer
        }
        
        delay(100);
    }
}