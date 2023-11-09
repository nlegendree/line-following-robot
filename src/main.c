#include "controller.h"
#include "i2cLCD.h"
#include "gpioPins.h"
#include "lineFinder.h"
#include "motors.h"

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
        lcdClear(lcd);


        // Line-Finder Mode
        if (buttonIsPressed(BUTTON_CROSS,controller,ev)) { // Press CROSS to enter Line-Finder Mode
            while(!buttonIsPressed(BUTTON_CIRCLE,controller,ev)) { // Press CIRCLE to leave Line-Finder Mode
                libevdev_next_event(controller, LIBEVDEV_READ_FLAG_NORMAL, &ev);
                lineFinder();
            }
        }


        // Manual Mode
        lcdPrintf(lcd,"Manual Mode");
        manualControl(controller,ev,&L2state,&R2state,&LXstate);


        delay(10);
    }
    
    return 0;
}