#include "animate.h"

void animate(Actor *actor, int aniIndex) {
    uint32_t currentFrame =
            ((SDL_GetTicks() - actor->animationStartTime)
            * actor->frameRatePerSecond / 1000)
            % actor->numFrames;

    actor->srcRectl.y = (int)(aniIndex * actor->srcRectl.h);
    actor->srcRectl.x = (int)(currentFrame * actor->srcRectl.w);
}
