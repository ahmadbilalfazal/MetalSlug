#include "Enemy.h"

Enemy::Enemy(float x, float y, float w, float h, int hp, float speed, int dmg, int score)
    : Entity(x, y, w, h, hp), moveSpeed(speed), damage(dmg),
    scoreValue(score), bulletCount(0) {

    for (int i = 0; i < maxBullets; i++) {
        bullets[i] = nullptr;
    }
}

Enemy::~Enemy() {
    for (int i = 0; i < maxBullets; i++) {
        if (bullets[i]) delete bullets[i];
    }
}

void Enemy::Update(float deltaTime) {
    Entity::Update(deltaTime);

    for (int i = 0; i < bulletCount; i++) {
        if (bullets[i] && bullets[i]->IsActive()) {
            bullets[i]->Update(deltaTime);
        }
    }

    if (position.x < -width || position.x > GetScreenWidth() + width) {
        isActive = false;
    }
}

int Enemy::GetScoreValue() const {
    return scoreValue;
}

Bullet** Enemy::GetBullets() {
    return bullets;
}

int Enemy::GetBulletCount() const {
    return bulletCount;
}