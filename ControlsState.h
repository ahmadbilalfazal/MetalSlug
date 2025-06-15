#pragma once
#include "Game.h"
#include "GameState.h"
#include "raylib.h"

class ControlsState : public GameState {
private:
    Game* game;
    Texture2D controlsTexture;
    Texture2D background;
    Sound backSound;

public:
    ControlsState(Game* game);
    ~ControlsState() override;

    void Enter() override;
    void Exit() override;
    void Update() override;
    void Draw() override;

    bool ShouldTransition() override;
    GameState* GetNextState() override;
};