#include "Bullet.h"

Bullet::Bullet(float x, float y, float velX, float velY, float spd, int dmg, const char* texturePath)
    : position{ x, y }, velocity{ velX, velY }, speed(spd),
    damage(dmg), isActive(true), scale(2.0f) {

    texture = LoadTexture(texturePath);
    if (texture.id == 0) {
        TraceLog(LOG_WARNING, "Failed to load bullet texture: %s", texturePath);
    }
}

Bullet::~Bullet() {
    if (texture.id != 0) {
        UnloadTexture(texture);
    }
}

void Bullet::Update(float deltaTime) {
    if (!isActive) return;

    position.x += velocity.x * speed * deltaTime;
    position.y += velocity.y * speed * deltaTime;

    if (position.x < -texture.width * scale ||
        position.x > GetScreenWidth() + texture.width * scale ||
        position.y < -texture.height * scale ||
        position.y > GetScreenHeight() + texture.height * scale) {
        isActive = false;
    }
}

void Bullet::Draw() {
    if (isActive && texture.id != 0) {
        DrawTextureEx(texture, position, 0, scale, WHITE);
    }
}

bool Bullet::IsActive() const {
    return isActive;
}

void Bullet::SetActive(bool active) {
    isActive = active;
}

Rectangle Bullet::GetCollisionRect() const {
    return {
        position.x,
        position.y,
        texture.width * scale,
        texture.height * scale
    };
}

int Bullet::GetDamage() const {
    return damage;
}