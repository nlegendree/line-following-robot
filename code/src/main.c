#include "controller.h"
#include "i2cLCD.h"
#include "gpioPins.h"
#include "lineFinder.h"
#include "motors.h"
#include "buzzer.h"
#include "distance.h"

#include <SDL2/SDL.h>
#include <wiringPi.h>
#include <lcd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define MODE_MANUAL     0
#define MODE_LINEFINDER 1

bool obstacleDetect(int lcd) {
    int distance = getDistance();

    if (distance < 5) { //Bug si obstacle trop proche (ne devrait pas arriver) valeur à 1200 environ à vérifier en TP.
        lcdClear(lcd);
        lcdPrintf(lcd,"Obstacle proche!");
        buzzerOn();

        return 1;
    }

    lcdClear(lcd);
    lcdPrintf(lcd,"Pas d'obstacle");
    buzzerOff();

    return 0;
}

void lineFinder(int lcd){
    bool gauche = detecterLigne(PIN_SUIVEUR_GAUCHE);
    bool centre = detecterLigne(PIN_SUIVEUR_CENTRE);
    bool droite = detecterLigne(PIN_SUIVEUR_DROIT);
    printf("%d %d %d\n",gauche,centre,droite);

    if (detecterIntersectionEnT(gauche,droite) /*|| obstacleDetect(lcd)*/) // Intersection en T = fin du parcours
        stopMotors();
    else if (detecterIntersection(gauche,centre,droite) || centre || (!gauche && !centre && !droite)) // Si aucun capteur n'a detecte la ligne, on avance quand meme
        LF_forward();
    else if (gauche)
        LF_turnLeft();
    else if (droite)
        LF_turnRight();
}

void manualControl(
        SDL_Event event,
        int *L2state,
        int *R2state,
        int *LXstate) 
{
    int R2 = triggerValue(SDL_CONTROLLER_AXIS_TRIGGERRIGHT,event,R2state);
    int L2 = triggerValue(SDL_CONTROLLER_AXIS_TRIGGERLEFT,event,L2state);
    int LX = axisValue(SDL_CONTROLLER_AXIS_LEFTX,event,LXstate);
    if (R2 >= L2) {
        forward(R2-L2,LX);
    }
    else {
        backward(L2-R2,LX);
    }
}

int main(int argc, char* argv[]) {
    // WiringPi Initialization
    wiringPiSetupGpio();
    
    // LCD Initialization
    int lcd = initLCD();

    // Controller Initialization
    lcdClear(lcd); lcdPrintf(lcd,"Waiting for     controller...");
    initController();
    lcdClear(lcd); lcdPrintf(lcd,"Controller      connected");

    // Motors Initialization
    initMotors();

    // Line-Finder Initialization
    initSuiveurLigne();

    // Event States Initialization
    int L2state = 0;
    int R2state = 0;
    int LXstate = 0;

    // Boucle principale
    SDL_Event event;
    int mode = MODE_MANUAL;
    while (1) {
        SDL_PollEvent(&event);
        if (event.cdevice.type == SDL_CONTROLLERDEVICEREMOVED) {
            lcdClear(lcd); lcdPrintf(lcd,"Controller      disconnected");
            initController();
            lcdClear(lcd); lcdPrintf(lcd,"Controller      connected");
        }
        else {
            if (buttonIsPressed(SDL_CONTROLLER_BUTTON_A,event)) // Press CROSS to enter Line-Finder Mode
                mode = MODE_LINEFINDER;
            else if (buttonIsPressed(SDL_CONTROLLER_BUTTON_B,event)) // Press CIRCLE to leave Line-Finder Mode
                mode = MODE_MANUAL;

            if (mode == MODE_LINEFINDER)
                lineFinder(lcd);
            else if (mode == MODE_MANUAL)
                manualControl(event,&L2state,&R2state,&LXstate);
        }
    }

    return 0;
}
