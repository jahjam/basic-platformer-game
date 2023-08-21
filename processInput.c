#include <SDL2/SDL.h>
#include <stdbool.h>
#include "processInput.h"
#include "structs.h"

void processInput(App *app, bool *isRunning) {
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

                handleKeyDown(app, &sdlEvent.key);
                break;
            case SDL_KEYUP:
                handleKeyUp(app, &sdlEvent.key);
                break;
        }
    }
}

void handleKeyDown(App *app, SDL_KeyboardEvent *sdlEvent) {
    if (sdlEvent->repeat == 0) {
        if (sdlEvent->keysym.scancode == SDL_SCANCODE_W) {
            app->up = 1;
        }
        if (sdlEvent->keysym.scancode == SDL_SCANCODE_S) {
            app->down = 1;
        }
        if (sdlEvent->keysym.scancode == SDL_SCANCODE_A) {
            app->left = 1;
        }
        if (sdlEvent->keysym.scancode == SDL_SCANCODE_D) {
            app->right = 1;
        }
    }
}

void handleKeyUp(App *app, SDL_KeyboardEvent *sdlEvent) {
    if (sdlEvent->repeat == 0) {
        if (sdlEvent->keysym.scancode == SDL_SCANCODE_W) {
            app->up = 0;
        }
        if (sdlEvent->keysym.scancode == SDL_SCANCODE_S) {
            app->down = 0;
        }
        if (sdlEvent->keysym.scancode == SDL_SCANCODE_A) {
            app->left = 0;
        }
        if (sdlEvent->keysym.scancode == SDL_SCANCODE_D) {
            app->right = 0;
        }
    }
}