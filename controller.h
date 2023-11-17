#ifndef __CONTROLLER__
#define __CONTROLLER__


#include <SDL2/SDL.h>
#include <stdbool.h>

#define BUTTON_CROSS 0
#define BUTTON_SQUARE 2
#define BUTTON_TRIANGLE 3
#define BUTTON_CIRCLE 1

#define MAX_TRIGGER 32767
#define MAX_AXIS 32767
#define MIN_AXIS -32768
#define DEADZONE_PERCENT 15 // Deadzone percentage
#define DEADZONE (int)(DEADZONE_PERCENT/100)

struct libevdev *initController();
bool buttonIsPressed(int BUTTON, SDL_Event event);
bool buttonIsReleased(int BUTTON, SDL_Event event);
bool buttonIsBeingPressed(int BUTTON, SDL_Event event, bool *state);
int triggerValue(int TRIGGER, SDL_Event event, int *state);
int axisValue(int AXIS, SDL_Event event, int *state);


#endif

