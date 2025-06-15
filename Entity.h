#pragma once
#include "raylib.h"
#include "Animation.h"

class Entity {
protected:
    Vector2 position;
    Vector2 velocity;
    float width;
    float height;
    int health;
    bool isActive;
    Animation* animation;

public:
    Entity(float x, float y, float w, float h, int hp);
    virtual ~Entity();

    virtual void Update(float deltaTime);
    virtual void Draw();
    virtual void TakeDamage(int damage);

    Rectangle GetCollisionRect() const;
    bool IsActive() const;
    bool CheckCollision(const Entity& other) const;

    void SetPosition(const Vector2& newPosition);

    Vector2 GetPosition() const;
    Vector2 GetVelocity() const;
    float GetWidth() const;
    float GetHeight() const;
    int GetHealth() const;
};