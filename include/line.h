#ifndef __LINE__
#define __LINE__

bool detecterLigne(int pin_linefinder);
bool detecterIntersection(int pin_capteur_gauche, int pin_capteur_centre, int pin_capteur_droit);
void suivreLigne(int pin_capteur_gauche, int pin_capteur_centre, int pin_capteur_droit);