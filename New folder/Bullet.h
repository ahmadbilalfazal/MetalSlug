#pragma once
#include "raylib.h"

class Bullet {
private:
    Vector2 position;
    Vector2 velocity;
    float speed;
    int damage;
    bool isActive;
    Texture2D texture;
    float scale;

public:
    Bullet(float x, float y, float velX, float velY, float speed, int damage, const char* texturePath);
    ~Bullet();

    virtual void Update(float deltaTime);
    void Draw();

    bool IsActive() const;
    void SetActive(bool active);

    Rectangle GetCollisionRect() const;
    int GetDamage() const;
};