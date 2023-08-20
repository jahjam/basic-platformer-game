#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include "structs.h"
#include "init.h"
#include "render.h"
#include "processInput.h"

int main(int argc, char *argv[]) {
    // this is our main application
    App app;
    // this is our main player
    Actor player;
    // setting a bunch of bytes to 0 for the size of the app
    memset(&app, 0, sizeof(App));
    memset(&player, 0, sizeof(Actor));
    // tracking if the app is running
    bool isRunning = false;

    // Init player (TO BE MOVED)
    player.x = 20;
    player.y = 20;

    init(&app, &isRunning);

    while (isRunning) {
        render(&app, &player);
        processInput(&isRunning);
    }

    return 0;
}