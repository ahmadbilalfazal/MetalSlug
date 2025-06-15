#include "HelicopterEnemy.h"

HelicopterEnemy::HelicopterEnemy(float x, float y)
    : Enemy(x, y, 128, 64, 50, 150.0f, 15, 200),
    altitude(y), maxAltitude(y - 100), minAltitude(y + 100),
    ascending(true), shootCooldown(1.5f), currentShootCooldown(0) {

    std::string flyFrames[] = { "fly_1_helicopter.png",
                              "fly_2_helicopter.png" };
    animation = new Animation(flyFrames, 2, 0.2f, true);
}

HelicopterEnemy::~HelicopterEnemy() {
}

void HelicopterEnemy::Update(float deltaTime) {
    Enemy::Update(deltaTime);
    Patrol();

    currentShootCooldown += deltaTime;
    if (currentShootCooldown >= shootCooldown) {
        Attack();
        currentShootCooldown = 0;
    }
}

void HelicopterEnemy::Patrol() {
    velocity.x = -moveSpeed;

    if (ascending) {
        position.y -= moveSpeed * 0.5f * GetFrameTime();
        if (position.y <= maxAltitude) {
            ascending = false;
        }
    }
    else {
        position.y += moveSpeed * 0.5f * GetFrameTime();
        if (position.y >= minAltitude) {
            ascending = true;
        }
    }
}

void HelicopterEnemy::Attack() {
    for (int i = 0; i < maxBullets; i++) {
        if (!bullets[i] || !bullets[i]->IsActive()) {
            if (!bullets[i]) {
                bullets[i] = new Bullet(
                    position.x + width / 2,
                    position.y + height,
                    0,
                    300.0f,
                    300.0f,
                    10,
                    "enemy_bullet.png"
                );
            }
            else {
                bullets[i]->SetActive(true);
            }

            if (i >= bulletCount) {
                bulletCount = i + 1;
            }
            break;
        }
    }
}