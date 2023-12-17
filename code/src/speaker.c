#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <wiringPi.h>
#include <SDL2/SDL.h>

#include "gpioPins.h"

void initSpeaker() {
    pinMode(PIN_SPEAKER, OUTPUT);
}

<<<<<<< HEAD
void playAudio(SDL_Event event, char argv0[]) {
    char *audios[] = {"audio1.mp3","audio2.mp3","audio3.mp3","audio4.mp3"};
    int audioIndex = -1;
    if (event.cbutton.type == SDL_CONTROLLERBUTTONDOWN) {
        switch (event.cbutton.button) {
            case SDL_CONTROLLER_BUTTON_DPAD_UP:
                audioIndex = 0;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                audioIndex = 1;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                audioIndex = 2;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                audioIndex = 3;
                break;
        }
        if (audioIndex != -1){
            char command[200], programPath[100];
            realpath(argv0, programPath);
            sprintf(command, "mpg123 %s/../audio/%s &", dirname(programPath), audios[audioIndex]);  // mpg123 permet de lire fichier mp3 -> sprintf permet de formater une Cdc
            system(command); // permet de lancer l'execution d'une commande
        }
=======
void playAudio(int button) {
    const char *audioFiles[] = {"audio1.mp3", "audio2.mp3", "audio3.mp3", "audio4.mp3"};

    // associe une valeur à la touche pressée par l'utilisateur
    int arrowPressed = -1;
    switch (button) {
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
        default:
            return;
    }
    if (arrowPressed != -1){
        digitalWrite(PIN_SPEAKER, HIGH);

        const char command[100];
        sprintf(command, "mpg123 %s", audioFiles[arrowPressed-1]);  // mpg123 permet de lire fichier mp3 -> sprintf permet de formater une Cdc
        system(command) // permet de lancer l'execution d'une commande

        digitalWrite(PIN_SPEAKER, LOW);
>>>>>>> 969dd87 (speaker add digitalWrite)
    }
}