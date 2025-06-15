#include "Grenade.h"

Grenade::Grenade(float x, float y, float velX, float velY)
    : Bullet(x, y, velX, velY, 200.0f, 30, "grenade.png"),
    explosionTimer(2.0f) {
}

void Grenade::Update(float deltaTime) {
    Bullet::Update(deltaTime);

    explosionTimer -= deltaTime;
    if (explosionTimer <= 0) {
        SetActive(false);
    }
}