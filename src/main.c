#include "controller.h"
#include "i2cLCD.h"
#include "gpioPins.h"

#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>
#include <wiringPi.h>
#include <lcd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

void manualControl(
        struct libevdev *controller,
        struct input_event ev,
        int *L2state,
        int *R2state,
        int *LXstate) 
{
    int L2 = triggerValue(TRIGGER_L2,controller,ev,L2state);
    if (L2 > 0) {
        printf("R2, PWM_R2 : %d, %d\n",L2,(int)(L2*1024)/255);
    }

    int R2 = triggerValue(TRIGGER_R2,controller,ev,R2state);
    if (R2 > 0) {
        printf("R2, PWM_R2 : %d, %d\n",R2,(int)(R2*1024)/255);
    }

    int LX = axisValue(AXIS_LX,controller,ev,LXstate);
    if (LX != MID_AXIS) {
        printf("AXIS LEFT X : %d\n",LX);
    }
}

int main() {

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

        system("clear");
        lcdClear(lcd);
        

        // Line-Finder Mode
        if (buttonIsPressed(BUTTON_CROSS,controller,ev)) { // Press CROSS to enter Line-Finder Mode
            while(!buttonIsPressed(BUTTON_CIRCLE,controller,ev) && suivreLigne(PIN_SUIVEUR_GAUCHE,PIN_SUIVEUR_CENTRE,PIN_SUIVEUR_DROIT)) { // Press CIRCLE to leave Line-Finder Mode
                libevdev_next_event(controller, LIBEVDEV_READ_FLAG_NORMAL, &ev);
            }
        }


        // Manual Mode
        manualControl(controller,ev,&L2state,&R2state,&LXstate);


        delay(10);
    }
    
    return 0;
}