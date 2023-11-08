#include "lineFinder.h"
#include "motors.h"
#include "i2cLCD.h"
#include "buzzer.h"
#include "gpio_pin.h"

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void initSuiveurLigne() {
    pinMode(PIN_SUIVEUR_GAUCHE, INPUT);
    pinMode(PIN_SUIVEUR_CENTRE, INPUT);
    pinMode(PIN_SUIVEUR_DROIT, INPUT);
}

bool detecterLigne(int pin_capteur) {
    return digitalRead(pin_capteur);
}

bool detecterIntersection(bool gauche, bool centre, bool droite){
    // Si les trois capteurs sont actifs alors on considère la présence d'une intersection
    return ((gauche && centre && droite) || (gauche && centre) || (centre && droite));
}

bool detecterIntersectionEnT(bool gauche, bool droite){
    return (gauche && droite);
}


bool suivreLigne(int pin_capteur_gauche, int pin_capteur_centre, int pin_capteur_droit){
    
    bool gauche = detecterLigne(pin_capteur_gauche);
    bool centre = detecterLigne(pin_capteur_centre);
    bool droite = detecterLigne(pin_capteur_droit);

    if (detecterIntersection(gauche,centre,droite) || centre || !(gauche && centre && droite)) // si aucun capteur n'a detecte la ligne, on avance quand meme
        avancer();
    else if (gauche){
        tournerGauche();
    }
    else if (droite){
        tournerDroite();
    }
    else if(detecterIntersectionEnT(gauche,droite)){ // on considere que la fin du parcours est marquée par une intersection en T
        return 0;
    }

    return 1; // Continuer à suivre la ligne
}
