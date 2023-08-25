#include "render.h"

void prepare(App *app) {
    SDL_SetRenderDrawColor(app->renderer, 21, 21, 21, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(app->renderer);
}

void render(App *app) {
    SDL_RenderPresent(app->renderer);
}
