#pragma once
#include "Enemy.h"

class HelicopterEnemy : public Enemy {
private:
    float altitude;
    float maxAltitude;
    float minAltitude;
    bool ascending;
    float shootCooldown;
    float currentShootCooldown;

public:
    HelicopterEnemy(float x, float y);
    ~HelicopterEnemy() override;

    void Update(float deltaTime) override;
    void Patrol() override;
    void Attack() override;
};