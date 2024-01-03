#ifndef __CONTROLLER__
#define __CONTROLLER__


#include <SDL2/SDL.h>
#include <stdbool.h>

#define MAX_TRIGGER         32767
#define MAX_AXIS            32767
#define MIN_AXIS           -32768
#define DEADZONE_PERCENT    15 // Deadzone percentage
#define DEADZONE            (DEADZONE_PERCENT/100.0)

// Controller initialization
SDL_GameController* initController();

// Function to check if a specific button is pressed
bool buttonIsPressed(int BUTTON, SDL_Event event);

// Function to check if a specific button is released
bool buttonIsReleased(int BUTTON, SDL_Event event);

// Function to check if a specific button is currently being pressed on the controller
bool buttonIsBeingPressed(SDL_GameController *controller, SDL_GameControllerButton BUTTON);

// Function to get the value of a specific trigger on the controller
int triggerValue(SDL_GameController *controller, SDL_GameControllerAxis TRIGGER);

// Function to get the value of a specific axis on the controller with a deadzone check
int axisValue(SDL_GameController *controller, SDL_GameControllerAxis AXIS);


#endif

