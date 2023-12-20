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
    digitalWrite(PIN_M1A,HIGH);
    digitalWrite(PIN_M2A,LOW);
    digitalWrite(PIN_M1B,LOW);
    digitalWrite(PIN_M2B,HIGH);
    
    float coeffSpeed = (float)LF_SPEED/MAX_TRIGGER;
    pwmWrite(PIN_EN1,(int)round(coeffSpeed*PWM_RANGE));
    pwmWrite(PIN_EN2,(int)round(coeffSpeed/2*PWM_RANGE));
}

void LF_turnRight() {
    forward(LF_SPEED_ROTATION,MAX_AXIS);
}
