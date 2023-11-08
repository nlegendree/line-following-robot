#include "obstacle.h"
#include "distance.h"
#include "buzzer.h"
#include "lcd.h"

#include <wiringPi.h>

void obstacleDetect(int lcd) {
    int distance = getDistance();

    if (distance < 5) { //Bug si obstacle trop proche (ne devrait pas arriver) valeur à 1200 environ à vérifier en TP.
        // Obstacle trop proche, arrête les moteurs
        // motors_stop();
        lcdClear(lcd);
        lcdPrintf(lcd,"Obstacle proche!");
        buzzerOn();
    } else {
        // Pas d'obstacle proche, redémarre les moteurs
        // motors_start();
        lcdClear(lcd);
        lcdPrintf(lcd,"Pas d'obstacle");
        buzzerOff();
    }
}