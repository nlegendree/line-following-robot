#ifndef __LINE_FINDER__
#define __LINE_FINDER__


#include <stdbool.h>

#define LF_SPEED MAX_TRIGGER

void initSuiveurLigne();
bool detecterLigne(int pin_linefinder);
bool detecterIntersection(bool gauche, bool centre, bool droite);
bool detecterIntersectionEnT(bool gauche, bool droite);
void lineFinder();
void LF_forward();
void LF_turnLeft();
void LF_turnRight();


#endif