#include "lineFinder.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#include "buzzer.h"
#include "gpioPins.h"
#include "i2cLCD.h"
#include "motors.h"

// Line finder sensors initialization
void initLineFinder() {
    pinMode(PIN_LINEFINDER_LEFT, INPUT);
    pinMode(PIN_LINEFINDER_CENTER, INPUT);
    pinMode(PIN_LINEFINDER_RIGHT, INPUT);
}

// Function to check the state of a specific line finder sensor
bool detectLine(int pin_capteur) {
    return digitalRead(pin_capteur);
}

// Function to check if the sensors are detecting any kind of intersection
bool detectIntersection(bool left, bool center, bool right) {
    return ((left && center && right) || (left && right) || (left && center) || (center && right));
}

// Function to make the robot move forward in line-finding mode
void LF_forward() {
    forward(LF_SPEED, 0);
}

// Function to make the robot turn left in line-finding mode
void LF_turnLeft() {
    forward(LF_SPEED_ROTATION, MIN_AXIS);
}

// Function to make the robot turn right in line-finding mode
void LF_turnRight() {
    forward(LF_SPEED_ROTATION, MAX_AXIS);
}
