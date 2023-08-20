#include <SDL2/SDL.h>
#include <stdbool.h>
#include "structs.h"
#include "init.h"
#include "render.h"
#include "processInput.h"

int main(int argc, char *argv[]) {
    // this is our main application
    App app;
    // setting a bunch of bytes to 0 for the size of the app
    memset(&app, 0, sizeof(App));
    // tracking if the app is running
    bool isRunning = false;

    init(&app, &isRunning);

    while (isRunning) {
        render(&app);
        processInput(&isRunning);
    }

    return 0;
}