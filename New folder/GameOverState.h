#pragma once
#include "Game.h"
#include "GameState.h"
#include "raylib.h"

class GameOverState : public GameState {
private:
    Game* game;
    int finalScore;
    Texture2D background;
    Texture2D gameOverTexture;
    Sound gameOverSound;

public:
    GameOverState(Game* game, int score);
    ~GameOverState() override;

    void Enter() override;
    void Exit() override;
    void Update() override;
    void Draw() override;

    bool ShouldTransition() override;
    GameState* GetNextState() override;
};