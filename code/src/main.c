#include "controller.h"
#include "i2cLCD.h"
#include "gpioPins.h"
#include "lineFinder.h"
#include "motors.h"
#include "buzzer.h"
#include "distance.h"

#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>
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

    if (obstacleDetect(lcd) || detecterIntersectionEnT(gauche,droite)) // Intersection en T = fin du parcours
        stop();
    else if (detecterIntersection(gauche,centre,droite) || centre || !(gauche && centre && droite)) // Si aucun capteur n'a detecte la ligne, on avance quand meme
        LF_forward();
    else if (gauche)
        LF_turnLeft();
    else if (droite)
        LF_turnRight();
}

void manualControl(
        struct libevdev *controller,
        struct input_event ev,
        int *L2state,
        int *R2state,
        int *LXstate) 
{
    int R2 = triggerValue(TRIGGER_R2,controller,ev,R2state);
    int L2 = triggerValue(TRIGGER_L2,controller,ev,L2state);
    int LX = axisValue(AXIS_LX,controller,ev,LXstate);
    if (R2 >= L2) {
        forward(R2-L2,LX);
    }
    else {
        backward(L2-R2,LX);
    }
}

int main() {

    // WiringPi Initialization
    wiringPiSetupGpio();
    
    // LCD Initialization
    int lcd = initLCD();

    // Motors Initialization
    initMotors();

    // Line-Finder Initialization
    initSuiveurLigne();

    // Controller Initialization
    lcdClear(lcd); lcdPrintf(lcd,"Waiting for controller...");
    struct libevdev *controller = initController();
    lcdClear(lcd); lcdPrintf(lcd,"Controller connected");

    // Event States Initialization
    int L2state = 0;
    int R2state = 0;
    int LXstate = MID_AXIS;

    // Controller Detection
    struct input_event ev;
    int mode = MODE_MANUAL;
    while (1) {
        if (libevdev_next_event(controller, LIBEVDEV_READ_FLAG_NORMAL, &ev) < 0) {
            lcdClear(lcd); lcdPrintf(lcd,"Controller disconnected");
            controller = initController();
            lcdClear(lcd); lcdPrintf(lcd,"Controller connected");
        }
        else {
            if (buttonIsPressed(BUTTON_CROSS,controller,ev)) // Press CROSS to enter Line-Finder Mode
                mode = MODE_LINEFINDER;
            else if (buttonIsPressed(BUTTON_CIRCLE,controller,ev)) // Press CIRCLE to leave Line-Finder Mode
                mode = MODE_MANUAL;

            if (mode == MODE_LINEFINDER)
                lineFinder(lcd);
            else if (mode == MODE_MANUAL)
                manualControl(controller,ev,&L2state,&R2state,&LXstate);
        }
    }
    
    return 0;
    
}
