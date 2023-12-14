#ifndef __SPEAKER__
#define __SPEAKER__


#include <SDL2/SDL.h>

void initSpeaker();
void playAudio(SDL_Event event, char argv0[]);


#endif