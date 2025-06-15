#include "Game.h"

int main() {
    Game game;
    game.Initialize();

    while (!game.ShouldClose()) {
        game.Update();
        game.Draw();
    }

    game.Shutdown();
    return 0;
}