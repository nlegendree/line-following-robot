#ifndef __LINE_FINDER__
#define __LINE_FINDER__


#include <stdbool.h>

#define LF_SPEED 			(int)(MAX_TRIGGER/1)
#define LF_SPEED_ROTATION 	(int)(LF_SPEED/1)

void initSuiveurLigne();
bool detecterLigne(int pin_linefinder);
bool detecterIntersection(bool gauche, bool centre, bool droite);
void lineFinder();
void LF_forward();
void LF_turnLeft();
void LF_turnRight();


#endif
