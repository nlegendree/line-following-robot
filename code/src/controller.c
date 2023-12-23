#include "controller.h"

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

// Controller initialization
SDL_GameController* initController() {
    SDL_Init(SDL_INIT_GAMECONTROLLER);
    return NULL;
}

// Function to check if a specific button is pressed
bool buttonIsPressed(int BUTTON, SDL_Event event) {
    return event.type == SDL_CONTROLLERBUTTONDOWN && event.cbutton.button == BUTTON;
}

// Function to check if a specific button is released
bool buttonIsReleased(int BUTTON, SDL_Event event) {
    return event.type == SDL_CONTROLLERBUTTONUP && event.cbutton.button == BUTTON;
}

// Function to check if a specific button is currently being pressed on the controller
bool buttonIsBeingPressed(SDL_GameController *controller, SDL_GameControllerButton BUTTON) {
    return SDL_GameControllerGetButton(controller,BUTTON);
}

// Function to get the value of a specific trigger on the controller
int triggerValue(SDL_GameController *controller, SDL_GameControllerAxis TRIGGER) {
    return SDL_GameControllerGetAxis(controller,TRIGGER);
}

// Function to get the value of a specific axis on the controller with a deadzone check
int axisValue(SDL_GameController *controller, SDL_GameControllerAxis AXIS) {
    int val = SDL_GameControllerGetAxis(controller,AXIS);
    if (val <= DEADZONE*MIN_AXIS || val >= DEADZONE*MAX_AXIS)
        return val;
    return 0;
}