#ifndef __LINE_FINDER__
#define __LINE_FINDER__


#include <stdbool.h>

void initSuiveurLigne()
bool detecterLigne(int pin_linefinder);
bool detecterIntersection(int pin_capteur_gauche, int pin_capteur_centre, int pin_capteur_droit);
bool detecterIntersectionEnT(bool gauche, bool centre, bool droite);
bool suivreLigne(int pin_capteur_gauche, int pin_capteur_centre, int pin_capteur_droit);


#endif