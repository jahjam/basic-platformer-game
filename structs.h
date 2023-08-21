#include <SDL2/SDL.h>

#ifndef TEST_PROJECT_STRUCTS_H
#define TEST_PROJECT_STRUCTS_H

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    Uint32 millisecsPreviousFrame;
    int up;
    int down;
    int left;
    int right;
} App;

typedef struct {
    double x;
    double y;
} Vec2;

typedef struct {
    Vec2 actorPosition;
    Vec2 actorVelocity;
} Actor;

#endif //TEST_PROJECT_STRUCTS_H
