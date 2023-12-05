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

bool obstacleDetect() {
    int distance = getDistance();
    printf("%d\n",distance);
    if (distance < 10) 
        return 1;
    return 0;
}

void lineFinder(int lcd){
    bool gauche = detecterLigne(PIN_SUIVEUR_GAUCHE);
    bool centre = detecterLigne(PIN_SUIVEUR_CENTRE);
    bool droite = detecterLigne(PIN_SUIVEUR_DROIT);
    printf("%d %d %d\n",gauche,centre,droite);

    if (obstacleDetect()) {
        stopMotors();
        lcdClear(lcd); lcdPrintf(lcd,"Near obstacle!");
        buzzerOn();
    }
    else {
        if (detecterIntersection(gauche,centre,droite) || centre)
            LF_forward();
        else if (gauche)
            LF_turnLeft();
        else if (droite)
            LF_turnRight();
        lcdClear(lcd); lcdPrintf(lcd,"No obstacles!");
        buzzerOff();
    }
}

void manualControl(int lcd, SDL_GameController *controller) {
    int R2 = triggerValue(controller,SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
    int L2 = triggerValue(controller,SDL_CONTROLLER_AXIS_TRIGGERLEFT);
    int LX = axisValue(controller,SDL_CONTROLLER_AXIS_LEFTX);
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

    // Boucle principale
    SDL_Event event;
    bool exit = 0;
    bool controllerConnected = 0;
    int mode = MODE_MANUAL;
    while (!exit) {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            exit = 1;
        else if (event.cdevice.type == SDL_CONTROLLERDEVICEADDED) {
            lcdClear(lcd); lcdPrintf(lcd,"Controller      connected");
            controller = SDL_GameControllerOpen(0);
            controllerConnected = 1;
        }
        else if (event.cdevice.type == SDL_CONTROLLERDEVICEREMOVED) {
            lcdClear(lcd); lcdPrintf(lcd,"Controller      disconnected");
            SDL_GameControllerClose(controller);
            controllerConnected = 0;
        }
        else if (controllerConnected) {
            if (buttonIsBeingPressed(controller,SDL_CONTROLLER_BUTTON_A)) // Press CROSS to enter Line-Finder Mode
                mode = MODE_LINEFINDER;
            else if (buttonIsBeingPressed(controller,SDL_CONTROLLER_BUTTON_B)) { // Press CIRCLE to leave Line-Finder Mode
                buzzerOff();
                mode = MODE_MANUAL;
            }

            if (mode == MODE_LINEFINDER)
                lineFinder(lcd);
            else if (mode == MODE_MANUAL)
                manualControl(lcd,controller);
        }
    }

    buzzerOff();
    SDL_Quit();

    return 0;
}
