#include "Game.h"

int main() {
    SetWorkingDirectory(GetApplicationDirectory());

    Game game;
    game.Initialize();

    while (!game.ShouldClose()) {
        game.Update();
        game.Draw();
    }

    game.Shutdown();
    return 0;
}