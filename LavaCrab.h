#pragma once
#include "Enemy.h"

class LavaCrab : public Enemy {
private:
    float diveTimer;

public:
    LavaCrab(float x, float y);
    void Update(float deltaTime) override;
    void Patrol() override;
    void Attack() override;
};