#pragma once
#include "raylib.h"

class GameState {
public:
    virtual ~GameState() = default;

    virtual void Enter() = 0;
    virtual void Exit() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;

    virtual bool ShouldTransition() = 0;
    virtual GameState* GetNextState() = 0;
};