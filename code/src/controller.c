#include "controller.h"

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

SDL_GameController* initController() {
    SDL_Init(SDL_INIT_GAMECONTROLLER);
    while (SDL_NumJoysticks() < 1) {}
    return SDL_GameControllerOpen(0);
}

bool buttonIsPressed(int BUTTON, SDL_Event event) {
    return event.type == SDL_CONTROLLERBUTTONDOWN && event.cbutton.button == BUTTON;
}

bool buttonIsReleased(int BUTTON, SDL_Event event) {
    return event.type == SDL_CONTROLLERBUTTONUP && event.cbutton.button == BUTTON;
}

bool buttonIsBeingPressed(SDL_GameController *controller, SDL_GameControllerButton BUTTON) {
    return SDL_GameControllerGetButton(controller,BUTTON);
}

int triggerValue(SDL_GameController *controller, SDL_GameControllerAxis TRIGGER) {
    return SDL_GameControllerGetAxis(controller,TRIGGER);
}

int axisValue(SDL_GameController *controller, SDL_GameControllerAxis AXIS) {
    int val = SDL_GameControllerGetAxis(controller,AXIS);
    if (val <= DEADZONE*MIN_AXIS || val >= DEADZONE*MAX_AXIS)
        return val;
    return 0;
}