#include "controller.h"

#include <stdio.h>
#include <SDL2/SDL.h>

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
