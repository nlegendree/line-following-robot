#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <SDL2/SDL.h>

#include "gpioPins.h"

void initSpeaker() {
    pinMode(PIN_SPEAKER, OUTPUT);
}

void playAudio(SDL_Event event) {
    const char *audioFiles[] = {"audio1.mp3", "audio2.mp3", "audio3.mp3", "audio4.mp3"};

    // associe une valeur à la touche pressée par l'utilisateur
    int arrowPressed = -1;
    if (event.cbutton.type == SDL_CONTROLLERBUTTONDOWN) {
        switch (event.cbutton.button) {
            case SDL_CONTROLLER_BUTTON_DPAD_UP:
                arrowPressed = 0;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                arrowPressed = 1;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                arrowPressed = 2;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                arrowPressed = 3;
                break;
        }
        if (arrowPressed != -1){
            const char command[100];
            sprintf(command, "mpg123 %s &", audioFiles[arrowPressed]);  // mpg123 permet de lire fichier mp3 -> sprintf permet de formater une Cdc
            system(command) // permet de lancer l'execution d'une commande
        }
    }
}