#include "structs.h"
#include "render.h"

void render(App *app) {
    SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(app->renderer);
    SDL_RenderPresent(app->renderer);
}
