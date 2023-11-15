#ifndef __MOTORS__
#define __MOTORS__


#include "controller.h"

#define PWM_CLOCK 50
#define PWM_RANGE 1024

void initMotors();
void forward(int speed, int angle);
void backward(int speed, int angle);
void stop();


#endif
