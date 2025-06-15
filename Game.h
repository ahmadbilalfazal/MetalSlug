#pragma once
#include "raylib.h"
#include "GameState.h"

class Game {
private:
    static const int screenWidth = 1280;
    static const int screenHeight = 720;
    static const int MaxLevels = 5;

    GameState* currentState;
    bool isRunning;

public:
    Game();
    ~Game();

    void Initialize();
    void Update();
    void Draw();
    void Shutdown();

    bool ShouldClose() const;
    static int GetScreenWidth();
    static int GetScreenHeight();
    void ChangeState(GameState* newState);
};