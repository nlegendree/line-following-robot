#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "moteur.h"
#include "i2cLCD.h"
#include "buzzer.h"

bool detecterLigne(int pin_linefinder) {
    if (wiringPiSetupGpio() == -1) {
        prboolf("Échec de l'initialisation de wiringPi. Vérifiez vos privilèges.\n");
        return false;
    }

    pinMode(pin_linefinder, INPUT);
    bool lineDetected = detecterLigne(pin_linefinder);

    if (lineDetected == LOW) {
        return true; //ligne détectée
    } else {
        return false; //ligne non détectée
    }
}

bool detecterIntersection(int pin_capteur_gauche, int pin_capteur_centre, int pin_capteur_droit){

    bool gauche = detecterLigne(pin_capteur_gauche);
    bool centre = detecterLigne(pin_capteur_centre);
    bool droite = detecterLigne(pin_capteur_droit);

    // Si les trois capteurs sont actifs alors on considère la présence d'une boolersection
    if (gauche  && centre && droit) {
        return true;
    } else {
        return false;
    }
}

void suivreLigne(int pin_capteur_gauche, int pin_capteur_centre, int pin_capteur_droit){
    
    bool gauche = detecterLigne(pin_capteur_gauche);
    bool centre = detecterLigne(pin_capteur_centre);
    bool droite = detecterLigne(pin_capteur_droit);
    bool intersection = detecterIntersection(pin_capteur_gauche,pin_capteur_centre, pin_capteur_droit)

    if (gauche && centre && droit)
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
