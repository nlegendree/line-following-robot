#ifndef __MOTORS__
#define __MOTORS__


#include "controller.h"

#define PWM_CLOCK 400
#define PWM_RANGE 1024
#define PWM_TRIGGER(X) ((int)((X)*PWM_RANGE)/MAX_TRIGGER)

void initMotors();
void forward(int speed, int angle);
void backward(int speed, int angle);
void stop();
void LF_forward();
void LF_turnLeft();
void LF_turnRight();


#endif
