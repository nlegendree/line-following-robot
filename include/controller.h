#ifndef __CONTROLLER__
#define __CONTROLLER__


#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>

#define DEVICE_NAME "Controller" // Part of the name specified in the 'evtest' command

#define BUTTON_CROSS BTN_SOUTH
#define BUTTON_SQUARE BTN_WEST
#define BUTTON_TRIANGLE BTN_NORTH
#define BUTTON_CIRCLE BTN_EAST

#define MAX_TRIGGER 255
#define TRIGGER_L2 ABS_Z
#define TRIGGER_R2 ABS_RZ

#define MAX_AXIS 255
#define MID_AXIS MAX_AXIS/2
#define DEADZONE_PERCENT 12 // Deadzone percentage
#define DEADZONE (int)(DEADZONE_PERCENT/100.0*MID_AXIS) 
#define AXIS_LX ABS_X
#define AXIS_LY ABS_Y
#define AXIS_RX ABS_RX
#define AXIS_RY ABS_RY

struct libevdev *initController();
int buttonIsPressed(int BUTTON, struct libevdev *controller,struct input_event ev,int *state);
int triggerValue(int TRIGGER, struct libevdev *controller,struct input_event ev,int *state);
int axisValue(int AXIS, struct libevdev *controller,struct input_event ev,int *state);


#endif

