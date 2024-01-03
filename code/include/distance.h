#ifndef __DISTANCE__
#define __DISTANCE__


#define DISPLAY_DISTANCE    50
#define STOP_DISTANCE       20

// Distance sensor initialization
void initDistanceSensor();

// Function to acquire the distance through the ultrasonic sensor
int getDistance();


#endif