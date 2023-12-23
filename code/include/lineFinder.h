#ifndef __LINE_FINDER__
#define __LINE_FINDER__


#include <stdbool.h>

#define LF_SPEED 			(int)(MAX_TRIGGER/1.3)
#define LF_SPEED_ROTATION 	(int)(LF_SPEED/1)

void initLineFinder();
bool detectLine(int pin_linefinder);
bool detectIntersection(bool gauche, bool centre, bool droite);
void lineFinder();
void LF_forward();
void LF_turnLeft();
void LF_turnRight();


#endif
