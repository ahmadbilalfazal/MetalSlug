#include "SnowTrooper.h"

SnowTrooper::SnowTrooper(float x, float y)
    : Enemy(x, y, 64, 64, 40, 120.0f, 15, 150),
    grenadeCooldown(3.0f) {

    std::string walkFrames[] = {
        "walk_1_snowtrooper.png",
        "walk_2_snowtrooper.png"
    };
    animation = new Animation(walkFrames, 2, 0.3f, true);
}

void SnowTrooper::Update(float deltaTime) {
    Enemy::Update(deltaTime);

    grenadeCooldown -= deltaTime;
    if (grenadeCooldown <= 0) {
        Attack();
        grenadeCooldown = 3.0f;
    }
}

void SnowTrooper::Patrol() {
    if (rand() % 100 < 90) {
        velocity.x = -moveSpeed;
    }
    else {
        velocity.x = 0;
    }
}

void SnowTrooper::Attack() {
    if (bulletCount >= maxBullets) return;

    bullets[bulletCount] = new Bullet(
        position.x + width / 2,
        position.y + height,
        0,
        200.0f,
        200.0f,
        15,
        "grenade.png"
    );
    bulletCount++;

    if (bulletCount >= maxBullets) bulletCount = 0;
}