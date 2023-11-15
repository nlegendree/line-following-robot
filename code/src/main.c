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
    
    // Motors Initialization
    initMotors();

    // LCD Initialization
    int lcd = initLCD();

    // Line-Finder Initialization
    initSuiveurLigne();

    // Controller Initialization
    struct libevdev *controller = initController();
    printf("Input device name : \"%s\"\n", libevdev_get_name(controller));
    getchar();

    // Event States Initialization
    int L2state = 0;
    int R2state = 0;
    int LXstate = MID_AXIS;

    // Controller Detection
    struct input_event ev;
    while (1) {
        libevdev_next_event(controller, LIBEVDEV_READ_FLAG_NORMAL, &ev);
        //lcdClear(lcd);


        // Line-Finder Mode
        if (buttonIsPressed(BUTTON_CROSS,controller,ev)) { // Press CROSS to enter Line-Finder Mode
            while(!buttonIsPressed(BUTTON_CIRCLE,controller,ev)) { // Press CIRCLE to leave Line-Finder Mode
                libevdev_next_event(controller, LIBEVDEV_READ_FLAG_NORMAL, &ev);
                //lineFinder(lcd);
            }
        }


        // Manual Mode
        //lcdPrintf(lcd,"Manual Mode");
        manualControl(controller,ev,&L2state,&R2state,&LXstate);
    }
    
    return 0;
}
