#include <SDL_image.h>
#include "structs.h"
#include "render.h"

void render(App *app, Actor *actor) {
    SDL_SetRenderDrawColor(app->renderer, 21, 21, 21, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(app->renderer);

    SDL_Texture *texture = actor->texture;

    if (!texture) {
        printf("%s\n", SDL_GetError());
        return;
    }

    SDL_Rect srcRect = actor->srcRectl;
    SDL_Rect dstRect = {(int) actor->actorPosition.x,
                        (int) actor->actorPosition.y,
                        (int) actor->actorDimensions.w,
                        (int) actor->actorDimensions.h};

    SDL_RenderCopy(app->renderer, texture, &srcRect, &dstRect);

    SDL_RenderPresent(app->renderer);
}
