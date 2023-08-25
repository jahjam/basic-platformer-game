#include "update.h"

void update(App *app, Stage *stage, Actor *actor) {
    Uint32 timeToWait = MILLISEC_PER_FRAME - (SDL_GetTicks() - app->millisecsPreviousFrame);

    if (timeToWait > 0 && timeToWait <= MILLISEC_PER_FRAME) {
        SDL_Delay(timeToWait);
    }

    double deltaTime = (SDL_GetTicks() - app->millisecsPreviousFrame) / 1000.0;

    app->millisecsPreviousFrame = SDL_GetTicks();

    app->delegate.logic(app, actor, stage, deltaTime);
    app->delegate.draw(app, actor, stage);
}