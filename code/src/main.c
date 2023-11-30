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
    if (distance < 5) //Bug si obstacle trop proche (ne devrait pas arriver) valeur à 1200 environ à vérifier en TP.
        return 1;

    return 0;
}

void lineFinder(int lcd, bool *obstacleWasDetected){
    bool gauche = detecterLigne(PIN_SUIVEUR_GAUCHE);
    bool centre = detecterLigne(PIN_SUIVEUR_CENTRE);
    bool droite = detecterLigne(PIN_SUIVEUR_DROIT);
    printf("%d %d %d\n",gauche,centre,droite);

    if (obstacleDetect(lcd)) {
        stopMotors();
        if (!(*obstacleWasDetected)) {
            lcdClear(lcd); lcdPrintf(lcd,"Near obstacle!");
            buzzerOn();
            *obstacleWasDetected = 1;
        }
    }
    else {
        if (detecterIntersection(gauche,centre,droite) || centre || (!gauche && !centre && !droite)) // Si aucun capteur n'a detecte la ligne, on avance quand meme
            LF_forward();
        else if (gauche)
            LF_turnLeft();
        else if (droite)
            LF_turnRight();
        if (*obstacleWasDetected) {
            lcdClear(lcd); lcdPrintf(lcd,"No obstacles!");
            buzzerOff();
            *obstacleWasDetected = 0;
        }
    }
}

void manualControl(
        int lcd,
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
    lcdClear(lcd); lcdPrintf(lcd,"Speed : %d",R2-L2);
}

int main(int argc, char* argv[]) {
    // WiringPi Initialization
    wiringPiSetupGpio();
    
    // LCD Initialization
    int lcd = initLCD();

    // Controller Initialization
    lcdClear(lcd); lcdPrintf(lcd,"Waiting for     controller...");
    SDL_GameController *controller = initController();

    // Motors Initialization
    initMotors();

    // Line-Finder Initialization
    initSuiveurLigne();
    
    // Line-Finder Initialization
    initDistanceSensor();
    
    // buzzer Initialization
    initBuzzer();
    buzzerOff();

    // Event States Initialization
    int L2state = 0;
    int R2state = 0;
    int LXstate = 0;

    // Boucle principale
    SDL_Event event;
    bool exit = 0;
    int mode = MODE_MANUAL;
    bool obstacleWasDetected = 0;
    while (!exit) {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            exit = 1;
        else if (event.cdevice.type == SDL_CONTROLLERDEVICEADDED) {
            lcdClear(lcd); lcdPrintf(lcd,"Controller      connected");
            controller = SDL_GameControllerOpen(0);
        }
        else if (event.cdevice.type == SDL_CONTROLLERDEVICEREMOVED) {
            lcdClear(lcd); lcdPrintf(lcd,"Controller      disconnected");
            SDL_GameControllerClose(controller);
        }
        else {
            if (buttonIsPressed(SDL_CONTROLLER_BUTTON_A,event)) // Press CROSS to enter Line-Finder Mode
                mode = MODE_LINEFINDER;
            else if (buttonIsPressed(SDL_CONTROLLER_BUTTON_B,event)) { // Press CIRCLE to leave Line-Finder Mode
                buzzerOff();
                mode = MODE_MANUAL;
            }

            if (mode == MODE_LINEFINDER)
                lineFinder(lcd,&obstacleWasDetected);
            else if (mode == MODE_MANUAL)
                manualControl(lcd,event,&L2state,&R2state,&LXstate);
        }
    }

    buzzerOff();
    SDL_Quit();

    return 0;
}
