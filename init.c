#include <stdbool.h>
#include "structs.h"
#include "defs.h"
#include "init.h"

void init(App *app, bool *isRunning) {
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    app->window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_RESIZABLE
    );

    if (!app->window) {
        printf("Error initialising SDL window!");
        return;
    }

    app->renderer = SDL_CreateRenderer(
            app->window,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!app->renderer) {
        printf("Error rendering SDL window!");
        return;
    }

//    SDL_SetWindowFullscreen(app->window, SDL_WINDOW_FULLSCREEN);

    *isRunning = true;
}
