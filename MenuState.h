#pragma once
#include "Game.h"
#include "GameState.h"
#include "raylib.h"

class MenuState : public GameState {
private:
    Game* game;
    int selectedOption;
    const char* options[3] = { "Start Game", "Controls", "Exit" };
    Texture2D background;
    Texture2D logo;
    Sound selectSound;
    Sound confirmSound;

public:
    MenuState(Game* game);
    ~MenuState() override;

    void Enter() override;
    void Exit() override;
    void Update() override;
    void Draw() override;

    bool ShouldTransition() override;
    GameState* GetNextState() override;
};