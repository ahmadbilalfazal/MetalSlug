#include "BossEnemy.h"

BossEnemy::BossEnemy(float x, float y, float w, float h, int hp, float speed, int dmg, int score)
    : Enemy(x, y, w, h, hp, speed, dmg, score), phase(1) {

    for (int i = 0; i < 3; i++) {
        animations[i] = nullptr;
    }
    currentAnimation = nullptr;
}

BossEnemy::~BossEnemy() {
    for (int i = 0; i < 3; i++) {
        if (animations[i]) delete animations[i];
    }
}

void BossEnemy::Update(float deltaTime) {
    Enemy::Update(deltaTime);

    if (currentAnimation) {
        currentAnimation->Update(deltaTime);
    }
}

void BossEnemy::Draw() {
    if (currentAnimation && isActive) {
        Texture2D frame = currentAnimation->GetCurrentFrame();
        DrawTexture(frame, position.x, position.y, WHITE);
    }

    float healthWidth = 200 * (health / (float)maxHealth);
    DrawRectangle(position.x + width / 2 - 100, position.y - 20, healthWidth, 10, RED);
}