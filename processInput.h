#ifndef TEST_PROJECT_PROCESSINPUT_H
#define TEST_PROJECT_PROCESSINPUT_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "structs.h"

void processInput(App *app, bool *isRunning);
void handleKeyDown(App *app, SDL_KeyboardEvent *sdlEvent);
void handleKeyUp(App *app, SDL_KeyboardEvent *sdlEvent);

#endif //TEST_PROJECT_PROCESSINPUT_H
