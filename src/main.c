#include "controller.h"
#include "i2cLCD.h"

#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>
#include <wiringPi.h>
#include <lcd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main() {

    // LCD Initialization
    int lcd = initLCD();

    // Controller Initialization
    struct libevdev *controller = initController();
    printf("Input device name : \"%s\"\n", libevdev_get_name(controller));
    getchar();

    // Controller Detection
    struct input_event ev;
    int Xstate = 0;
    int L2state = 0;
    int R2state = 0;
    int LXstate = MID_AXIS;
    while (1) {
        libevdev_next_event(controller, LIBEVDEV_READ_FLAG_NORMAL, &ev);

        system("clear");
        lcdClear(lcd);
        
        // Mode suiveur de ligne
        if (buttonIsPressed(BUTTON_CROSS,controller,ev)) { // Appuyer sur CROIX pour entrer dans le mode suiveur de ligne
            while(!buttonIsPressed(BUTTON_CIRCLE,controller,ev)) { // Appuyer sur ROND pour quitter le mode suiveur de ligne
                libevdev_next_event(controller, LIBEVDEV_READ_FLAG_NORMAL, &ev);
                // Actions
            }
        }

        // Mode manuel
        if (buttonIsBeingPressed(BUTTON_SQUARE,controller,ev,&Xstate)) {
            printf("SQUARE is pressed\n");
        }

        int L2 = triggerValue(TRIGGER_L2,controller,ev,&L2state);
        if (L2 > 0) {
            printf("L2 : %d\n",L2);
            lcdPrintf(lcd,"L2 : %d\n",L2);
        }

        int R2 = triggerValue(TRIGGER_R2,controller,ev,&R2state);
        if (R2 > 0) {
            printf("R2 : %d\n",R2);
        }

        int LX = axisValue(AXIS_LX,controller,ev,&LXstate);
        if (LX != MID_AXIS) {
            printf("AXIS LEFT X : %d\n",LX);
        }

        delay(10);
    }
    
    return 0;
}