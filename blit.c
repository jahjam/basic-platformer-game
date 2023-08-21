#include "structs.h"

void blit(App *app, Actor *actor, double deltaTime) {
    SDL_Rect screenBounds;
    SDL_GetDisplayBounds(0, &screenBounds);

    // create screen collision
    if (actor->actorPosition.x < 0) actor->actorPosition.x = 0;
    if (actor->actorPosition.x > screenBounds.w - 64) actor->actorPosition.x = screenBounds.w - 64;
    if (actor->actorPosition.y < 0) actor->actorPosition.y = 0;
    if (actor->actorPosition.y > screenBounds.h - 64) actor->actorPosition.y = screenBounds.h - 64;

    if (actor->actorPosition.x >= 0
        && actor->actorPosition.y >= 0
        && actor->actorPosition.x <= screenBounds.w - 64
        && actor->actorPosition.y <= screenBounds.h - 64) {
        if (app->up) {
            actor->actorPosition.y -= actor->actorVelocity.y * deltaTime;
        }
        if (app->down) {
            actor->actorPosition.y += actor->actorVelocity.y * deltaTime;
        }
        if (app->right) {
            actor->actorPosition.x += actor->actorVelocity.x * deltaTime;
        }
        if (app->left) {
            actor->actorPosition.x -= actor->actorVelocity.x * deltaTime;
        }
    }
}