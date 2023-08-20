#include <SDL2/SDL.h>
#include <stdbool.h>
#include "processInput.h"

void processInput(bool *isRunning) {
    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
            case SDL_QUIT:
                *isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
                    *isRunning = false;
                    break;
                }
        }
    }
}