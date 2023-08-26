#ifndef TEST_PROJECT_SETUP_H
#define TEST_PROJECT_SETUP_H

#include "structs.h"
#include "blit.h"
#include "util.h"
#include <SDL_image.h>
#include <stdlib.h>
#include <stdbool.h>

static SDL_Texture *arrowTexture;
static SDL_Texture *enemyTexture;
static int enemySpawnTimer;
SDL_Rect screenBounds;

void setup(App *app, Actor *actor, Stage *stage);

static void draw(App *app, Actor *actor, Stage *stage);

static void logic(App *app, Actor *actor, Stage *stage, double deltaTime, bool *playerIsAlive);

static void setupPlayer(App *app, Actor *player, Stage *stage);

static void handlePlayer(App *app, Actor *actor, Stage *stage, double deltaTime);

static void handleArrows(Stage *stage, double deltaTime);

static int arrowHitEnemy(Stage *stage, Actor *arrow);

static void drawArrows(App *app, Stage *stage);

static void drawPlayer(App *app, Actor *actor);

static void handleEnemy(Stage *stage, Actor *player, double deltaTime, bool *playerIsAlive);

static void spawnEnemy(Stage *stage);

static void drawEnemy(App *app, Stage *stage);

static void fireArrow(Stage *stage, Actor *player);

#endif //TEST_PROJECT_SETUP_H
