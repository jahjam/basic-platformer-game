#include "structs.h"

void blit(App *app, SDL_Texture *texture, int x, int y) {
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;

    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    printf("%d\n", dest.x);

    SDL_RenderCopy(app->renderer, texture, NULL, &dest);
}