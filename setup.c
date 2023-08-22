#include "structs.h"
#include "setup.h"
#include "blit.h"
#include "render.h"
#include <SDL_image.h>

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
        if (app->keyboard[SDL_SCANCODE_F]) {
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

    arrow->actorPosition.x = player->actorPosition.x;
    arrow->actorPosition.y = player->actorPosition.y;
    arrow->actorVelocity.y = PLAYER_ARROW_SPEED;
    arrow->health = 1;
    arrow->actorDimensions.w = 48;
    arrow->actorDimensions.h = 48;
    arrow->srcRectl.w = 48;
    arrow->srcRectl.h = 48;
    arrow->srcRectl.x = 0;
    arrow->srcRectl.y = 0;
    arrow->texture = IMG_LoadTexture(app->renderer, "../assets/bow-and-arrows.png");

    arrow->actorPosition.y += (player->actorDimensions.h / 2) - (arrow->actorDimensions.h / 2);

    player->reload = 8;
}

static void handleArrows(Stage *stage, double deltaTime) {
    Actor *b, *prev;
    SDL_Rect screenBounds;
    SDL_GetDisplayBounds(0, &screenBounds);

    prev = &stage->arrowHead;

    for (b = stage->arrowHead.next; b != NULL; b = b->next) {
        b->actorPosition.x += b->actorVelocity.x * deltaTime;
        b->actorPosition.y += b->actorVelocity.y * deltaTime;

        if (b->actorPosition.x > screenBounds.w) {
            if (b == stage->arrowTail)  {
                stage->arrowTail = prev;
            }

            prev->next = b->next;
            free(b);
            b = prev;
        }

        prev = b;
    }
}

static void drawPlayer(App *app, Actor *player) {
    render(app, player);
}

static void drawArrows(App *app, Stage *stage) {
    Actor *b;

    for (b = stage->arrowHead.next; b != NULL; b = b->next) {
        render(app, b);
    }
}