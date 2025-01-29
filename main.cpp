#include "game.h"
#include <iostream>

using namespace std;

int main(void) {
    Game game(1280.0, 720.0);    // create the game object
    game.SetupGameWorld();

    while (game.getIsRunning()) {
        game.mainLoop();
    }

    return 0;
}