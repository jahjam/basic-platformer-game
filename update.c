#include "structs.h"
#include "main.h"
#include "blit.h"

void update(App *app, Actor *actor) {
    Uint32 timeToWait = MILLISEC_PER_FRAME - (SDL_GetTicks() - app->millisecsPreviousFrame);

    if (timeToWait > 0 && timeToWait <= MILLISEC_PER_FRAME) {
        SDL_Delay(timeToWait);
    }

    double deltaTime = (SDL_GetTicks() - app->millisecsPreviousFrame) / 1000.0;

    app->millisecsPreviousFrame = SDL_GetTicks();

    blit(app, actor, deltaTime);
}