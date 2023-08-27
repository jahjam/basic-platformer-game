#include "setup.h"

static void logic(App *app, Actor *player, Stage *stage, double deltaTime, bool *playerIsAlive) {
    handlePlayer(app, player, stage, deltaTime);
    handleEnemy(stage, player, deltaTime, playerIsAlive);
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
    player->srcRectl.y = 0;
    player->flipType = SDL_FLIP_NONE;
    player->side = SIDE_PLAYER;
    player->health = 1;
    player->frameRatePerSecond = 5;
    player->numFrames = 2;
    player->animationStartTime = SDL_GetTicks();
    player->isAnimating = false;

    player->texture = IMG_LoadTexture(app->renderer, "../assets/player-sprite-sheet.png");
}

void setup(App *app, Actor *actor, Stage *stage) {
    app->delegate.logic = logic;
    app->delegate.draw = draw;

    memset(stage, 0, sizeof(Stage));
    stage->fighterTail = &stage->fighterHead;
    stage->arrowTail = &stage->arrowHead;

    setupPlayer(app, actor, stage);

    arrowTexture = IMG_LoadTexture(app->renderer, "../assets/bow-and-arrows.png");
    enemyTexture = IMG_LoadTexture(app->renderer, "../assets/enemy-sprite-sheet.png");

    SDL_GetDisplayBounds(0, &screenBounds);
}

static void handlePlayer(App *app, Actor *player, Stage *stage, double deltaTime) {
    // create screen collision
    if (player->actorPosition.x < 0) player->actorPosition.x = 0;
    if (player->actorPosition.x > screenBounds.w - 32) player->actorPosition.x = screenBounds.w - 32;
    if (player->actorPosition.y < 0) player->actorPosition.y = 0;
    if (player->actorPosition.y > screenBounds.h - 32) player->actorPosition.y = screenBounds.h - 32;

    if (player->actorPosition.x >= 0
        && player->actorPosition.y >= 0
        && player->actorPosition.x <= screenBounds.w - 32
        && player->actorPosition.y <= screenBounds.h - 32) {
        player->isAnimating = false;
        resetSprite(player);

        if (player->reload > 0) {
            player->reload--;
        }
        if (app->keyboard[SDL_SCANCODE_W]) {
            player->isAnimating = true;
            animate(player, 2);
            player->actorPosition.y -= player->actorVelocity.y * deltaTime;
        }
        if (app->keyboard[SDL_SCANCODE_S]) {
            player->isAnimating = true;
            animate(player, 1);
            player->actorPosition.y += player->actorVelocity.y * deltaTime;
        }
        if (app->keyboard[SDL_SCANCODE_D]) {
            player->isAnimating = true;
            animate(player, 3);
            player->actorPosition.x += player->actorVelocity.x * deltaTime;
        }
        if (app->keyboard[SDL_SCANCODE_A]) {
            player->isAnimating = true;
            animate(player, 4);
            player->actorPosition.x -= player->actorVelocity.x * deltaTime;
        }
        if (app->keyboard[SDL_SCANCODE_LSHIFT]) {
            player->actorVelocity.x = 350;
            player->actorVelocity.y = 350;
            player->frameRatePerSecond = 10;
        } else {
            player->actorVelocity.x = 200;
            player->actorVelocity.y = 200;
        }
        if (app->keyboard[SDL_SCANCODE_F] && !player->isAnimating && player->reload == 0) {
            fireArrow(stage, player);
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

    arrow->actorPosition.x = player->actorPosition.x + 32;
    arrow->actorPosition.y = player->actorPosition.y;
    arrow->actorVelocity.x = PLAYER_ARROW_SPEED;
    arrow->yOffset = yOffset;
    arrow->actorDimensions.w = 16;
    arrow->actorDimensions.h = 16;
    arrow->srcRectl.w = 16;
    arrow->srcRectl.h = 16;
    arrow->srcRectl.x = 32;
    arrow->srcRectl.y = 0;
    arrow->texture = arrowTexture;
    arrow->side = SIDE_PLAYER;

    // positions the arrow central to the player sprite
    arrow->actorPosition.y += (player->actorDimensions.h / 2) - (arrow->actorDimensions.h / 2);

    player->reload = 30;
}

static void spawnEnemy(Stage *stage) {
    Actor *enemy;

    enemySpawnTimer -= 1;

    if (enemySpawnTimer <= 0) {
        enemy = malloc(sizeof(Actor));
        memset(enemy, 0, sizeof(Actor));
        stage->fighterTail->next = enemy;
        stage->fighterTail = enemy;

        int randSpawn = rand() % screenBounds.h - 32;

        enemy->actorPosition.x = screenBounds.w;
        enemy->actorPosition.y = randSpawn > 0 ? randSpawn : 2;
        enemy->texture = enemyTexture;
        enemy->actorDimensions.w = 32;
        enemy->actorDimensions.h = 32;
        enemy->srcRectl.w = 16;
        enemy->srcRectl.h = 16;
        enemy->srcRectl.x = 0;
        enemy->srcRectl.y = 0;
        enemy->actorVelocity.x = -100.0;
        enemy->flipType = SDL_FLIP_HORIZONTAL;
        enemy->side = SIDE_ENEMY;
        enemy->health = 1;
        enemy->frameRatePerSecond = 5;
        enemy->numFrames = 2;
        enemy->animationStartTime = SDL_GetTicks();

        enemySpawnTimer = 30 + (rand() % 60);
    }
}

static void handleEnemy(Stage *stage, Actor *player, double deltaTime, bool *playerIsAlive) {
    Actor *enemy, *prev;

    prev = &stage->fighterHead;

    for (enemy = stage->fighterHead.next; enemy != NULL; enemy = enemy->next) {
        if (enemy != player) {
            animate(enemy, 1);

            enemy->actorPosition.x += enemy->actorVelocity.x * deltaTime;
            enemy->actorPosition.y += enemy->actorVelocity.y * deltaTime;

            if (collision(
                    enemy->actorPosition.x,
                    enemy->actorPosition.y,
                    enemy->actorDimensions.h,
                    enemy->actorDimensions.w,
                    player->actorPosition.x,
                    player->actorPosition.y,
                    player->actorDimensions.h,
                    player->actorDimensions.w
            )) {
                // handle end game
                *playerIsAlive = false;
            }

            if (enemy->actorPosition.x < -enemy->actorDimensions.w || enemy->health <= 0) {
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

        if (arrowHitEnemy(stage, arrow) || arrow->actorPosition.x > screenBounds.w) {
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

static int arrowHitEnemy(Stage *stage, Actor *arrow) {
    Actor *enemy;

    for (enemy = stage->fighterHead.next; enemy != NULL; enemy = enemy->next) {
        if (enemy->side != arrow->side && collision(
                arrow->actorPosition.x,
                arrow->actorPosition.y,
                arrow->actorDimensions.h,
                arrow->actorDimensions.w,
                enemy->actorPosition.x,
                enemy->actorPosition.y,
                enemy->actorDimensions.h,
                enemy->actorDimensions.w
        )) {
            enemy->health = 0;
            return 1;
        }
    }

    return 0;
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