#pragma once
#include "BossEnemy.h"

class DragonTank : public BossEnemy {
private:
    float fireballCooldown;

public:
    DragonTank(float x, float y);
    void Update(float deltaTime) override;
    void Patrol() override;
    void Attack() override;
};