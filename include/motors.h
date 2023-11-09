#ifndef __MOTORS__
#define __MOTORS__


#include "controller.h"

#define PWM_CLOCK 400
#define PWM_RANGE 1024
#define PWM_TRIGGER(X) ((int)((X)*PWM_RANGE)/MAX_TRIGGER)

void initMotors();
void forward(int R2, int leftAxis);
void backward(int L2, int leftAxis);
void stop();
void LF_forward();
void LF_turnLeft();
void LF_turnRight();


#endif