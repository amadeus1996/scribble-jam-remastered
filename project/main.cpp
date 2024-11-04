#include "headers/Game.h"

int main() {
    auto &game = Game::getInstance();
    game.run();
    Game::destroyInstance();
    return 0;
}
