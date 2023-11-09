#include "lineFinder.h"
#include "motors.h"
#include "i2cLCD.h"
#include "buzzer.h"
#include "gpioPins.h"

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


void lineFinder(){
    
    bool gauche = detecterLigne(PIN_SUIVEUR_GAUCHE);
    bool centre = detecterLigne(PIN_SUIVEUR_CENTRE);
    bool droite = detecterLigne(PIN_SUIVEUR_DROIT);

    if (detecterIntersection(gauche,centre,droite) || centre || !(gauche && centre && droite)) // Si aucun capteur n'a detecte la ligne, on avance quand meme
        LF_forward();
    else if (gauche){
        LF_turnLeft();
    }
    else if (droite){
        LF_turnRight();
    }
    else if(detecterIntersectionEnT(gauche,droite)){ // On considere que la fin du parcours est marquée par une intersection en T
        stop();
    }
}