#include <SDL2/SDL.h>
#include <stdbool.h>
#include "structs.h"
#include "init.h"
#include "render.h"
#include "processInput.h"
#include "update.h"
#include "setup.h"

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

    init(&app, &isRunning);

    setup(&player);

    while (isRunning) {
        processInput(&app, &isRunning);
        update(&app, &player);
        render(&app, &player);
    }

    return 0;
}