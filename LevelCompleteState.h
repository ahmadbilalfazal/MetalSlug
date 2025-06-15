#pragma once
#include "Game.h"
#include "GameState.h"
#include "raylib.h"

class LevelCompleteState : public GameState {
private:
    Game* game;
    int currentScore;
    int levelNumber;
    bool isGameComplete;
    Texture2D background;
    Texture2D completeTexture;
    Sound completeSound;

public:
    LevelCompleteState(Game* game, int score, bool gameComplete);
    ~LevelCompleteState() override;

    void Enter() override;
    void Exit() override;
    void Update() override;
    void Draw() override;

    bool ShouldTransition() override;
    GameState* GetNextState() override;
};