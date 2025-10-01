#ifndef __MOTORS__
#define __MOTORS__

#include "controller.h"

#define PWM_CLOCK 50
#define PWM_RANGE 1024

// Motors initialization
void initMotors();

// Function to make the robot move forward with a specified speed and steering angle
void forward(int speed, int angle);

// Function to make the robot move backward with a specified speed and steering angle
void backward(int speed, int angle);

// Function to stop the motors
void stopMotors();

#endif
