#pragma once
#include "BossEnemy.h"

class YetiMech : public BossEnemy {
private:
    float chargeCooldown;

public:
    YetiMech(float x, float y);
    void Update(float deltaTime) override;
    void Patrol() override;
    void Attack() override;
};