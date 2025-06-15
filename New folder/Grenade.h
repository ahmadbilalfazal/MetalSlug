#pragma once
#include "Bullet.h"

class Grenade : public Bullet {
private:
    float explosionTimer;

public:
    Grenade(float x, float y, float velX, float velY);
    void Update(float deltaTime) override;
};