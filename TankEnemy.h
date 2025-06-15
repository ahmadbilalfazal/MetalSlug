#pragma once
#include "Enemy.h"

class TankEnemy : public Enemy {
private:
    float attackDelay;
    float currentAttackTime;

public:
    TankEnemy(float x, float y);
    ~TankEnemy() override;

    void Update(float deltaTime) override;
    void Patrol() override;
    void Attack() override;
};