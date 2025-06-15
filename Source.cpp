#include "Game.h"

int main() {
	GetWorkingDirectory();
    Game game;
    game.Initialize();

    while (!game.ShouldClose()) {
        game.Update();
        game.Draw();
    }

    game.Shutdown();
    return 0;
}