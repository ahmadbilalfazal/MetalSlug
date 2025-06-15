#include "TankEnemy.h"

TankEnemy::TankEnemy(float x, float y)
    : Enemy(x, y, 128, 96, 100, 50.0f, 20, 300),
    attackDelay(3.0f), currentAttackTime(0) {

    std::string idleFrames[] = { "idle_tank.png" };
    animation = new Animation(idleFrames, 1, 1.0f, true);
}

TankEnemy::~TankEnemy() {
}

void TankEnemy::Update(float deltaTime) {
    Enemy::Update(deltaTime);
    Patrol();

    currentAttackTime += deltaTime;
    if (currentAttackTime >= attackDelay) {
        Attack();
        currentAttackTime = 0;
    }
}

void TankEnemy::Patrol() {
    velocity.x = -moveSpeed;
}

void TankEnemy::Attack() {
    if (bulletCount >= maxBullets) return;

    bullets[bulletCount] = new Bullet(
        position.x,
        position.y + height / 2,
        -200.0f,
        0,
        200.0f,
        20,
        "enemy_bullet.png"
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