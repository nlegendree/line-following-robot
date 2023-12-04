#ifndef __CONTROLLER__
#define __CONTROLLER__


#include <SDL2/SDL.h>
#include <stdbool.h>

#define MAX_TRIGGER         32767
#define MAX_AXIS            32767
#define MIN_AXIS           -32768
#define DEADZONE_PERCENT    15 // Deadzone percentage
#define DEADZONE            (DEADZONE_PERCENT/100.0)

SDL_GameController* initController();
bool buttonIsPressed(int BUTTON, SDL_Event event);
bool buttonIsReleased(int BUTTON, SDL_Event event);
bool buttonIsBeingPressed(SDL_GameController *controller, SDL_GameControllerButton BUTTON);
int triggerValue(SDL_GameController *controller, SDL_GameControllerAxis TRIGGER);
int axisValue(SDL_GameController *controller, SDL_GameControllerAxis AXIS);


#endif

