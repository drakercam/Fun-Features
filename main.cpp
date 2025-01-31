#include "game.h"
#include <iostream>

using namespace std;

int main(void) {
    Game game(1360.0, 800);    // create the game object
    game.SetupGameWorld();

    while (game.getIsRunning()) {
        game.mainLoop();
    }

    return 0;
}