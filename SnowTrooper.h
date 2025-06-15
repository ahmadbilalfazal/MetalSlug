#pragma once
#include "Enemy.h"

class SnowTrooper : public Enemy {
private:
    float grenadeCooldown;

public:
    SnowTrooper(float x, float y);
    void Update(float deltaTime) override;
    void Patrol() override;
    void Attack() override;
};