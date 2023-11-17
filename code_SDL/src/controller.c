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

int main_test_c(int argc, char* argv[]) {
    printf("Waiting for controller...\n");
    initController();
    printf("Controller connected\n");

    // States
    bool Xstate = 0;
    int L2state = 0;
    int LXstate = 0;

    // Boucle principale
    SDL_Event event;
    while (1) {
        SDL_PollEvent(&event);
        if (event.cdevice.type == SDL_CONTROLLERDEVICEREMOVED) {
            printf("Controller disconnected\n");
            initController();
            printf("Controller connected\n");
        }
        else {
            if (buttonIsBeingPressed(SDL_CONTROLLER_BUTTON_A,event,&Xstate)) {
                printf("Tu appuyes sur X\n");
            }
            int L2 = triggerValue(SDL_CONTROLLER_AXIS_TRIGGERLEFT,event,&L2state);
            if (L2 > 0) {
                printf("L2 : %d\n", L2);
            }
            int LX = axisValue(SDL_CONTROLLER_AXIS_LEFTX,event,&LXstate);
            if (LX != 0) {
                printf("Axis Left : %d\n", LX);
            }
        }
    }

    return 0;
}
