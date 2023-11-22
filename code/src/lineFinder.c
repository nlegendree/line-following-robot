#include "lineFinder.h"
#include "motors.h"
#include "i2cLCD.h"
#include "buzzer.h"
#include "gpioPins.h"

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void initSuiveurLigne() {
    pinMode(PIN_SUIVEUR_GAUCHE, INPUT);
    pinMode(PIN_SUIVEUR_CENTRE, INPUT);
    pinMode(PIN_SUIVEUR_DROIT, INPUT);
}

bool detecterLigne(int pin_capteur) {
    return digitalRead(pin_capteur);
}

bool detecterIntersection(bool gauche, bool centre, bool droite){
    return ((gauche && centre && droite) || (gauche && droite) || (gauche && centre) || (centre && droite));
}

void LF_forward() {
    forward(LF_SPEED,0);
}

void LF_turnLeft() {
    forward(LF_SPEED,MIN_AXIS);
}

void LF_turnRight() {
    forward(LF_SPEED,MAX_AXIS);
}
