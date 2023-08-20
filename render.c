#include <SDL_image.h>
#include "structs.h"
#include "render.h"

void render(App *app, Actor *actor) {
//    SDL_SetRenderDrawColor(app->renderer, 21, 21, 21, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(app->renderer);

    SDL_Surface *surface = IMG_Load("../assets/Characters_V3_Colour.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(app->renderer, surface);
    SDL_FreeSurface(surface);

    if (!surface) {
        printf("%s\n", SDL_GetError());
        return;
    }

    SDL_Rect srcRect = {0, 160, 16, 16};
    SDL_Rect dstRect = {actor->x, actor->y, 32, 32};

    SDL_RenderCopy(app->renderer, texture, &srcRect, &dstRect);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(app->renderer);
}
