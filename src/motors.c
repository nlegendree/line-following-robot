#include "motors.h"

#include <math.h>
#include <wiringPi.h>

#include "controller.h"
#include "gpioPins.h"

// Motors initialization
void initMotors() {
    pinMode(PIN_M1A, OUTPUT);
    pinMode(PIN_M1B, OUTPUT);
    pinMode(PIN_M2A, OUTPUT);
    pinMode(PIN_M2B, OUTPUT);
    pinMode(PIN_EN1, PWM_OUTPUT);
    pinMode(PIN_EN2, PWM_OUTPUT);

    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(PWM_CLOCK);
    pwmSetRange(PWM_RANGE);
}

// Function to make the robot move forward with a specified speed and steering angle
void forward(int speed, int angle) {
    // Pins setting to make motors move forward
    digitalWrite(PIN_M1A, HIGH);
    digitalWrite(PIN_M2A, HIGH);
    digitalWrite(PIN_M1B, LOW);
    digitalWrite(PIN_M2B, LOW);

    float coeffSpeed = (float)speed / MAX_TRIGGER;
    if (angle <= 0) {  // If the user turns left, only the speed of the left motor depends on the angle of rotation
        float coeffAngle = (float)(MIN_AXIS - angle) / MIN_AXIS;
        pwmWrite(PIN_EN1, (int)round(coeffAngle * coeffSpeed * PWM_RANGE));
        pwmWrite(PIN_EN2, (int)round(coeffSpeed * PWM_RANGE));
    } else {  // If the user turns right, only the speed of the right motor depends on the angle of rotation
        float coeffAngle = (float)(MAX_AXIS - angle) / MAX_AXIS;
        pwmWrite(PIN_EN1, (int)round(coeffSpeed * PWM_RANGE));
        pwmWrite(PIN_EN2, (int)round(coeffAngle * coeffSpeed * PWM_RANGE));
    }
}

// Function to make the robot move backward with a specified speed and steering angle
void backward(int speed, int angle) {
    // Pins setting to make motors move backward
    digitalWrite(PIN_M1A, LOW);
    digitalWrite(PIN_M2A, LOW);
    digitalWrite(PIN_M1B, HIGH);
    digitalWrite(PIN_M2B, HIGH);

    float coeffSpeed = (float)speed / MAX_TRIGGER;
    if (angle <= 0) {  // If the user turns left, only the speed of the left motor depends on the angle of rotation
        float coeffAngle = (float)(MIN_AXIS - angle) / MIN_AXIS;
        pwmWrite(PIN_EN1, (int)round(coeffAngle * coeffSpeed * PWM_RANGE));
        pwmWrite(PIN_EN2, (int)round(coeffSpeed * PWM_RANGE));
    } else {  // If the user turns right, only the speed of the right motor depends on the angle of rotation
        float coeffAngle = (float)(MAX_AXIS - angle) / MAX_AXIS;
        pwmWrite(PIN_EN1, (int)round(coeffSpeed * PWM_RANGE));
        pwmWrite(PIN_EN2, (int)round(coeffAngle * coeffSpeed * PWM_RANGE));
    }
}

// Function to stop the motors
void stopMotors() {
    pwmWrite(PIN_EN1, 0);
    pwmWrite(PIN_EN2, 0);
}
