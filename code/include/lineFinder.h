#ifndef __LINE_FINDER__
#define __LINE_FINDER__


#include <stdbool.h>

#define LF_SPEED 			(int)(MAX_TRIGGER/1.3)  // Motors speed in line-finding mode
#define LF_SPEED_ROTATION 	(int)(LF_SPEED/1)       // Motors rotation speed in line-finding mode

// Line finder sensors initialization
void initLineFinder();

// Function to check the state of a specific line finder sensor
bool detectLine(int pin_linefinder);

// Function to check if the sensors are detecting any kind of intersection
bool detectIntersection(bool gauche, bool centre, bool droite);

// Function to make the robot move forward in line-finding mode
void LF_forward();

// Function to make the robot turn left in line-finding mode
void LF_turnLeft();

// Function to make the robot turn right in line-finding mode
void LF_turnRight();


#endif
