#ifndef TEST_PROJECT_STRUCTS_H
#define TEST_PROJECT_STRUCTS_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "defs.h"

typedef struct Actor Actor;
typedef struct App App;
typedef struct Stage Stage;

typedef struct {
    void (*logic)(App *app, Actor *actor, Stage *stage, double deltaTime, bool *playerIsAlive);

    void (*draw)(App *app, Actor *actor, Stage *stage);
} Delegate;

struct App {
    SDL_Renderer *renderer;
    SDL_Window *window;
    Uint32 millisecsPreviousFrame;
    Delegate delegate;
    int keyboard[MAX_KEYBOARD_KEYS];
};

typedef struct {
    double x;
    double y;
} Vec2;

typedef struct {
    double w;
    double h;
} Dimensions;


struct Actor {
    Vec2 actorPosition;
    Vec2 actorVelocity;
    Dimensions actorDimensions;
    int health;
    int reload;
    int yOffset;
    Actor *next;
    SDL_Texture *texture;
    SDL_RendererFlip flipType;
    SDL_Rect srcRectl;
    int side;
};

struct Stage {
    Actor fighterHead, *fighterTail;
    Actor arrowHead, *arrowTail;
} ;

#endif //TEST_PROJECT_STRUCTS_H
