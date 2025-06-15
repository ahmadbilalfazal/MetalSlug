#include "HelicopterEnemy.h"

HelicopterEnemy::HelicopterEnemy(float x, float y)
    : Enemy(x, y, 128, 64, 50, 150.0f, 15, 200),
    altitude(y), maxAltitude(y - 100), minAltitude(y + 100),
    ascending(true), shootCooldown(1.5f), currentShootCooldown(0) {

    std::string flyFrames[] = { "assets/enemies/helicopter/fly_1.png",
                              "assets/enemies/helicopter/fly_2.png" };
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
    if (bulletCount >= maxBullets) return;

    bullets[bulletCount] = new Bullet(
        position.x + width / 2,
        position.y + height,
        0,
        300.0f,
        300.0f,
        10,
        "assets/bullets/enemy_bullet.png"
    );
    bulletCount++;

    bool allUsed = true;
    for (int i = 0; i < maxBullets; i++) {
        if (bullets[i] && bullets[i]->IsActive()) {
            allUsed = false;
            break;
        }
    }

    if (allUsed) {
        bulletCount = 0;
    }
}