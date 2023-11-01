#ifndef __LINE__
#define __LINE__

void initSuiveurLigne()
bool detecterLigne(int pin_linefinder);
bool detecterIntersection(int pin_capteur_gauche, int pin_capteur_centre, int pin_capteur_droit);
bool detecterIntersectionEnT(bool gauche, bool centre, bool droite)
void suivreLigne(int pin_capteur_gauche, int pin_capteur_centre, int pin_capteur_droit);