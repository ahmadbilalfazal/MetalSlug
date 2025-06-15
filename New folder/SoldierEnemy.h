#pragma once
#include "Enemy.h"

class SoldierEnemy : public Enemy {
private:
    float patrolDistance;
    float currentPatrolDistance;
    bool movingRight;

public:
    SoldierEnemy(float x, float y);
    ~SoldierEnemy() override;

    void Update(float deltaTime) override;
    void Patrol() override;
    void Attack() override;
};