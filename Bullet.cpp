#include "Bullet.h"

Bullet::Bullet(float x, float y, float velX, float velY, float spd, int dmg, const char* texturePath)
    : position{ x, y }, velocity{ velX, velY }, speed(spd),
    damage(dmg), isActive(true) {

    texture = LoadTexture(texturePath);
}

Bullet::~Bullet() {
    UnloadTexture(texture);
}

void Bullet::Update(float deltaTime) {
    if (!isActive) return;

    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    if (position.x < -texture.width || position.x > GetScreenWidth() + texture.width ||
        position.y < -texture.height || position.y > GetScreenHeight() + texture.height) {
        isActive = false;
    }
}

void Bullet::Draw() {
    if (isActive) {
        DrawTexture(texture, position.x, position.y, WHITE);
    }
}

bool Bullet::IsActive() const {
    return isActive;
}

void Bullet::SetActive(bool active) {
    isActive = active;
}

Rectangle Bullet::GetCollisionRect() const {
    return { position.x, position.y, (float)texture.width, (float)texture.height };
}

int Bullet::GetDamage() const {
    return damage;
}