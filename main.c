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
    memset(&app, 0, sizeof(App));
    // this is our main player
    Actor player;
    memset(&player, 0, sizeof(Actor));

    Stage stage;
    memset(&stage, 0, sizeof(Stage));

    // tracking if the app is running
    bool isRunning = false;

    init(&app, &isRunning);

    setup(&app, &player, &stage);

    while (isRunning) {
        prepare(&app);
        processInput(&app, &isRunning);
        update(&app, &stage, &player);
        render(&app);
    }

    return 0;
}