#include "main.h"

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

    bool playerIsAlive = true;

    srand(time(NULL));

    init(&app, &isRunning);

    setup(&app, &player, &stage);

    while (isRunning && playerIsAlive) {
        prepare(&app);
        processInput(&app, &isRunning);
        update(&app, &stage, &player, MILLISEC_PER_FRAME, &playerIsAlive);
        render(&app);
    }

    return 0;
}