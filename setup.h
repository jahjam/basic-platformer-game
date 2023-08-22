#ifndef TEST_PROJECT_SETUP_H
#define TEST_PROJECT_SETUP_H

#include "structs.h"

void setup (App *app, Actor *actor, Stage *stage);
static void draw(App *app, Actor *actor, Stage *stage);
static void logic(App *app, Actor *actor, Stage *stage, double deltaTime);
static void setupPlayer(App *app, Actor *player, Stage *stage);
static void handlePlayer(App *app, Actor *actor, Stage *stage, double deltaTime);
static void handleArrows(Stage *stage, double deltaTime);
static void drawArrows(App *app, Stage *stage);
static void drawPlayer(App *app, Actor *actor);
static void fireArrow(App *app, Stage *stage, Actor *player);

#endif //TEST_PROJECT_SETUP_H
