#include "structs.h"

void blit(App *app, Actor *actor) {
    SDL_Rect srcRect = actor->srcRectl;
    SDL_Rect dstRect = {(int) actor->actorPosition.x,
                        (int) actor->actorPosition.y,
                        (int) actor->actorDimensions.w,
                        (int) actor->actorDimensions.h};

    SDL_RenderCopyEx(app->renderer, actor->texture, &srcRect, &dstRect, 0, 0, actor->flipType);
}