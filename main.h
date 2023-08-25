
#ifndef TEST_PROJECT_MAIN_H
#define TEST_PROJECT_MAIN_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>
#include "structs.h"
#include "init.h"
#include "render.h"
#include "processInput.h"
#include "update.h"
#include "setup.h"

const int FPS = 60;
const int MILLISEC_PER_FRAME = 1000 / FPS;

int main(int argc, char *argv[]);

#endif //TEST_PROJECT_MAIN_H
