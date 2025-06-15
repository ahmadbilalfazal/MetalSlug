#pragma once
#include "Game.h"
#include "GameState.h"
#include "raylib.h"
#include "Level.h"

class PlayState : public GameState {
private:
    Game* game;
    Level* currentLevel;
    int currentLevelNumber;
    int playerScore;
    bool isPaused;
    Texture2D pauseTexture;
    Sound levelStartSound;
    Sound gameOverSound;

public:
    PlayState(Game* game);
    ~PlayState() override;

    void Enter() override;
    void Exit() override;
    void Update() override;
    void Draw() override;

    bool ShouldTransition() override;
    GameState* GetNextState() override;

private:
    void LoadLevel(int levelNumber);
    void UnloadLevel();
    void HandleInput();
    void CheckPlayerState();
    void DrawHUD();
    void DrawPauseMenu();
};