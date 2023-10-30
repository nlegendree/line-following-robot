#include "controller.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>

int main() {

    //Controller Initialization
    struct libevdev *controller = initController();
    printf("Input device name : \"%s\"\n", libevdev_get_name(controller));

    //Controller Detection
    int Xstate = 0;
    int L2state = 0;
    int R2state = 0;
    int LXstate = MID_AXIS;
    while (1) {
        struct input_event ev;
        libevdev_next_event(controller, LIBEVDEV_READ_FLAG_NORMAL, &ev);
        system("clear");

        if (buttonIsPressed(BUTTON_CROSS,controller,ev,&Xstate)) {
            printf("X is pressed\n");
        }

        int L2 = triggerValue(TRIGGER_L2,controller,ev,&L2state);
        if (L2 > 0) {
            printf("L2 : %d\n",L2);
        }

        int R2 = triggerValue(TRIGGER_R2,controller,ev,&R2state);
        if (R2 > 0) {
            printf("R2 : %d\n",R2);
        }

        int LX = axisValue(AXIS_LX,controller,ev,&LXstate);
        if (LX != MID_AXIS) {
            printf("AXIS LEFT X : %d\n",LX);
        }
        //delay(10);
    }
    
    return 0;
}