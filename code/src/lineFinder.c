#include "lineFinder.h"
#include "motors.h"
#include "i2cLCD.h"
#include "buzzer.h"
#include "gpioPins.h"

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void initLineFinder() {
    pinMode(PIN_LINEFINDER_LEFT, INPUT);
    pinMode(PIN_LINEFINDER_CENTER, INPUT);
    pinMode(PIN_LINEFINDER_RIGHT, INPUT);
}

bool detectLine(int pin_capteur) {
    return digitalRead(pin_capteur);
}

bool detectIntersection(bool left, bool center, bool right){
    return ((left && center && right) || (left && right) || (left && center) || (center && right));
}

void LF_forward() {
    forward(LF_SPEED,0);
}

void LF_turnLeft() {
    forward(LF_SPEED_ROTATION,MIN_AXIS);
}

void LF_turnRight() {
    forward(LF_SPEED_ROTATION,MAX_AXIS);
}
