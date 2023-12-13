#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <SDL2/SDL.h>

#include "gpioPins.h"

void initSpeaker() {
    pinMode(PIN_SPEAKER, OUTPUT);
}

void playAudio(int button) {
    const char *audioFiles[] = {"audio1.mp3", "audio2.mp3", "audio3.mp3", "audio4.mp3"};

    // associe une valeur à la touche pressée par l'utilisateur
    int arrowPressed = -1;
    switch (button) {
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            arrowPressed = 1;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            arrowPressed = 2;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            arrowPressed = 3;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            arrowPressed = 4;
            break;
        default:
            return;
    }
    if (arrowPressed != -1){
        const char command[100];
        sprintf(command, "mpg123 %s", audioFiles[arrowPressed-1]);  // mpg123 permet de lire fichier mp3 -> sprintf permet de formater une Cdc
        system(command) // permet de lancer l'execution d'une commande
    }
}