#include <SDL2/SDL.h>

#ifndef TEST_PROJECT_STRUCTS_H
#define TEST_PROJECT_STRUCTS_H

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

typedef struct {
    int x;
    int y;
} Actor;

#endif //TEST_PROJECT_STRUCTS_H
