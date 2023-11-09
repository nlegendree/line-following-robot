#ifndef __MOTORS__
#define __MOTORS__


void initMotors();
void forward(int R2, int leftAxis);
void backward(int L2, int leftAxis);
void stop();
void LF_forward();
void LF_turnLeft();
void LF_turnRight();


#endif