#include "moteur.h"
#include "i2cLCD.h"
#include "buzzer.h"
#include "gpio_pin.h"

#include <stdio.h>
#include <stdlib.h>

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
    return (gauche && centre && droite) || (gauche && centre) || (centre && droite);
}

bool detecterIntersectionEnT(bool gauche, bool centre, bool droite){
    return gauche && droite;
}


void suivreLigne(int pin_capteur_gauche, int pin_capteur_centre, int pin_capteur_droit){
    
    bool gauche = detecterLigne(pin_capteur_gauche);
    bool centre = detecterLigne(pin_capteur_centre);
    bool droite = detecterLigne(pin_capteur_droit);
    bool intersection = detecterIntersection(pin_capteur_gauche,pin_capteur_centre, pin_capteur_droit)

    if (detecterIntersection(gauche,centre,droite))
        avancer();
    else if (!gauche){
        tournerDroite();
    }
    else if (!droite){
        tournerGauche();
    }
    else if(intersection){
        int direction = rand() % 3; // retourne un nombre aléatoire entre 0, 1, 2
        if (direction == 0){
            avancer();
        }
        else if(direction == 1) {
            tournerGauche();
        }
        else{
            tournerDroite();
        }
    }
    else{
        //rien n'est détecté, le root est perdu -> alerte, arret d'urgence et message
        arreter();
        buzzerOn();
        lcdWrite("Aucune ligne detectée");
    }
}
