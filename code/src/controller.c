#include "controller.h"

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

SDL_GameController* initController() {
    int numControllers = 0;
    while (numControllers < 1) {
        SDL_Quit();
        SDL_Init(SDL_INIT_GAMECONTROLLER);
        numControllers = SDL_NumJoysticks();
    }
    SDL_GameController* controller = SDL_GameControllerOpen(0);
    return controller;
}

bool buttonIsPressed(int BUTTON, SDL_Event event) {
    return event.type == SDL_CONTROLLERBUTTONDOWN && event.cbutton.button == BUTTON;
}

bool buttonIsReleased(int BUTTON, SDL_Event event) {
    return event.type == SDL_CONTROLLERBUTTONUP && event.cbutton.button == BUTTON;
}

bool buttonIsBeingPressed(int BUTTON, SDL_Event event, bool *state) {
    if (buttonIsPressed(BUTTON,event))
        *state = 1;
    if (buttonIsReleased(BUTTON,event))
        *state = 0;
    return *state;
}

int triggerValue(int TRIGGER, SDL_Event event, int *state) {
    if (event.caxis.type == SDL_CONTROLLERAXISMOTION && event.caxis.axis == TRIGGER)
        *state = event.caxis.value;
    return *state;
}

int axisValue(int AXIS, SDL_Event event, int *state) {
    if (event.caxis.type == SDL_CONTROLLERAXISMOTION && event.caxis.axis == AXIS) {
        if (event.caxis.value <= DEADZONE*MIN_AXIS || event.caxis.value >= DEADZONE*MAX_AXIS)
            *state = event.caxis.value;
        else
            *state = 0;
    }
    return *state;
}