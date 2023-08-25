#include "structs.h"
#include "setup.h"
#include "blit.h"
#include <SDL_image.h>
#include <stdlib.h>

static void logic(App *app, Actor *actor, Stage *stage, double deltaTime) {
    handlePlayer(app, actor, stage, deltaTime);
    handleArrows(stage, deltaTime);
}

static void draw(App *app, Actor *actor, Stage *stage) {
    drawPlayer(app, actor);
    drawArrows(app, stage);
}

static void setupPlayer(App *app, Actor *player, Stage *stage) {
    stage->fighterTail->next = player;
    stage->fighterTail = player;

    player->actorPosition.x = 10;
    player->actorPosition.y = 10;
    player->actorVelocity.x = 100.0;
    player->actorVelocity.y = 100.0;
    player->actorDimensions.w = 32;
    player->actorDimensions.h = 32;
    player->srcRectl.w = 16;
    player->srcRectl.h = 16;
    player->srcRectl.x = 0;
    player->srcRectl.y = 160;

    player->texture = IMG_LoadTexture(app->renderer, "../assets/Characters_V3_Colour.png");
}

void setup(App *app, Actor *actor, Stage *stage) {
    app->delegate.logic = logic;
    app->delegate.draw = draw;

    memset(stage, 0, sizeof(Stage));
    stage->fighterTail = &stage->fighterHead;
    stage->arrowTail = &stage->arrowHead;

    setupPlayer(app, actor, stage);

    arrowTexture = IMG_LoadTexture(app->renderer, "../assets/bow-and-arrows.png");
    enemyTexture = IMG_LoadTexture(app->renderer, "../assets/bow-and-arrows.png");
}

static void handlePlayer(App *app, Actor *actor, Stage *stage, double deltaTime) {
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
        if (actor->reload > 0)
        {
            actor->reload--;
        }
        if (app->keyboard[SDL_SCANCODE_W]) {
            actor->actorPosition.y -= actor->actorVelocity.y * deltaTime;
        }
        if (app->keyboard[SDL_SCANCODE_S]) {
            actor->actorPosition.y += actor->actorVelocity.y * deltaTime;
        }
        if (app->keyboard[SDL_SCANCODE_D]) {
            actor->actorPosition.x += actor->actorVelocity.x * deltaTime;
        }
        if (app->keyboard[SDL_SCANCODE_A]) {
            actor->actorPosition.x -= actor->actorVelocity.x * deltaTime;
        }
        if (app->keyboard[SDL_SCANCODE_F] && actor->reload == 0) {
            fireArrow(app, stage, actor);
        }
    }
}

static void fireArrow(App *app, Stage *stage, Actor *player){
    Actor *arrow;

    arrow = malloc(sizeof(Actor));
    memset(arrow, 0, sizeof(Actor));

    stage->arrowTail->next = arrow;
    stage->arrowTail = arrow;

    int offset = rand() % 51;
    int yOffset =  rand() % 51 - offset;

    arrow->actorPosition.x = player->actorPosition.x;
    arrow->actorPosition.y = player->actorPosition.y;
    arrow->actorVelocity.x = PLAYER_ARROW_SPEED;
    arrow->yOffset = yOffset;
    arrow->health = 1;
    arrow->actorDimensions.w = 16;
    arrow->actorDimensions.h = 16;
    arrow->srcRectl.w = 16;
    arrow->srcRectl.h = 16;
    arrow->srcRectl.x = 32;
    arrow->srcRectl.y = 0;
    arrow->texture = arrowTexture;

    // positions the arrow central to the player sprite
    arrow->actorPosition.y += (player->actorDimensions.h / 2) - (arrow->actorDimensions.h / 2);

    player->reload = 8;
}

static void handleArrows(Stage *stage, double deltaTime) {
    Actor *arrow, *prev;
    SDL_Rect screenBounds;
    SDL_GetDisplayBounds(0, &screenBounds);

    prev = &stage->arrowHead;

    for (arrow = stage->arrowHead.next; arrow != NULL; arrow = arrow->next) {
        arrow->actorPosition.x += arrow->actorVelocity.x * deltaTime;
        arrow->actorPosition.y += arrow->actorVelocity.y + arrow->yOffset * deltaTime;

        if (arrow->actorPosition.x > screenBounds.w) {
            if (arrow == stage->arrowTail)  {
                stage->arrowTail = prev;
            }

            prev->next = arrow->next;
            free(arrow);
            arrow = prev;
        }

        prev = arrow;
    }
}

static void drawPlayer(App *app, Actor *player) {
    blit(app, player);
}

static void drawArrows(App *app, Stage *stage) {
    Actor *b;

    for (b = stage->arrowHead.next; b != NULL; b = b->next) {
        blit(app, b);
    }
}