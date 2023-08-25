#include "setup.h"

static void logic(App *app, Actor *player, Stage *stage, double deltaTime) {
    handlePlayer(app, player, stage, deltaTime);
    handleEnemy(stage, player, deltaTime);
    handleArrows(stage, deltaTime);
    spawnEnemy(stage);
}

static void draw(App *app, Actor *player, Stage *stage) {
    drawPlayer(app, player);
    drawEnemy(app, stage);
    drawArrows(app, stage);
}

static void setupPlayer(App *app, Actor *player, Stage *stage) {
    stage->fighterTail->next = player;
    stage->fighterTail = player;

    player->actorPosition.x = 10;
    player->actorPosition.y = 10;
    player->actorVelocity.x = 200.0;
    player->actorVelocity.y = 200.0;
    player->actorDimensions.w = 32;
    player->actorDimensions.h = 32;
    player->srcRectl.w = 16;
    player->srcRectl.h = 16;
    player->srcRectl.x = 0;
    player->srcRectl.y = 160;
    player->flipType = SDL_FLIP_NONE;

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
    enemyTexture = IMG_LoadTexture(app->renderer, "../assets/Characters_V3_Colour.png");

    SDL_GetDisplayBounds(0, &screenBounds);
}

static void handlePlayer(App *app, Actor *actor, Stage *stage, double deltaTime) {
    // create screen collision
    if (actor->actorPosition.x < 0) actor->actorPosition.x = 0;
    if (actor->actorPosition.x > screenBounds.w - 32) actor->actorPosition.x = screenBounds.w - 32;
    if (actor->actorPosition.y < 0) actor->actorPosition.y = 0;
    if (actor->actorPosition.y > screenBounds.h - 32) actor->actorPosition.y = screenBounds.h - 32;

    if (actor->actorPosition.x >= 0
        && actor->actorPosition.y >= 0
        && actor->actorPosition.x <= screenBounds.w - 32
        && actor->actorPosition.y <= screenBounds.h - 32) {
        if (actor->reload > 0) {
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
            fireArrow(stage, actor);
        }
    }
}

static void fireArrow(Stage *stage, Actor *player) {
    Actor *arrow;

    arrow = malloc(sizeof(Actor));
    memset(arrow, 0, sizeof(Actor));

    stage->arrowTail->next = arrow;
    stage->arrowTail = arrow;

    int offset = rand() % 51;
    int yOffset = rand() % 51 - offset;

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

static void spawnEnemy(Stage *stage) {
    Actor *enemy;

    enemySpawnTimer -= 1;

    if (enemySpawnTimer <= 0) {
        enemy = malloc(sizeof(Actor));
        memset(enemy, 0, sizeof(Actor));
        stage->fighterTail->next = enemy;
        stage->fighterTail = enemy;

        enemy->actorPosition.x = screenBounds.w;
        enemy->actorPosition.y = rand() % screenBounds.h;
        enemy->texture = enemyTexture;
        enemy->actorDimensions.w = 32;
        enemy->actorDimensions.h = 32;
        enemy->srcRectl.w = 16;
        enemy->srcRectl.h = 16;
        enemy->srcRectl.x = 32;
        enemy->srcRectl.y = 192;
        enemy->actorVelocity.x = -100.0;
        enemy->flipType = SDL_FLIP_HORIZONTAL;

        enemySpawnTimer = 30 + (rand() % 60);
    }
}

static void handleEnemy(Stage *stage, Actor *player, double deltaTime) {
    Actor *enemy, *prev;

    prev = &stage->fighterHead;

    for (enemy = stage->fighterHead.next; enemy != NULL; enemy = enemy->next) {
        if (enemy != player) {
            enemy->actorPosition.x += enemy->actorVelocity.x * deltaTime;
            enemy->actorPosition.y += enemy->actorVelocity.y * deltaTime;

            if (enemy->actorPosition.x < -enemy->actorDimensions.w) {
                if (enemy == stage->fighterTail) {
                    stage->fighterTail = prev;
                }

                prev->next = enemy->next;
                free(enemy);
                enemy = prev;
            }

            prev = enemy;
        }
    }

}

static void handleArrows(Stage *stage, double deltaTime) {
    Actor *arrow, *prev;

    prev = &stage->arrowHead;

    for (arrow = stage->arrowHead.next; arrow != NULL; arrow = arrow->next) {
        arrow->actorPosition.x += arrow->actorVelocity.x * deltaTime;
        arrow->actorPosition.y += arrow->actorVelocity.y + arrow->yOffset * deltaTime;

        if (arrow->actorPosition.x > screenBounds.w) {
            if (arrow == stage->arrowTail) {
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

static void drawEnemy(App *app, Stage *stage) {
    Actor *enemy;

    for (enemy = &stage->fighterHead; enemy != NULL; enemy = enemy->next) {
        blit(app, enemy);
    }
}

static void drawArrows(App *app, Stage *stage) {
    Actor *b;

    for (b = stage->arrowHead.next; b != NULL; b = b->next) {
        blit(app, b);
    }
}