#include "Entity.h"

Entity::Entity(float x, float y, float w, float h, int hp, float scale)
    : position{ x, y }, velocity{ 0, 0 }, width(w), height(h),
    health(hp), isActive(true), animation(nullptr), scale(scale) {
}

Entity::~Entity() {
    if (animation) delete animation;
}

void Entity::Update(float deltaTime) {
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    if (animation) {
        animation->Update(deltaTime);
    }
}

void Entity::Draw() {
    if (animation && IsActive()) {
        Texture2D frame = animation->GetCurrentFrame();
        DrawTextureEx(
            frame,
            position,
            0.0f,
            animation->GetScale() * scale,
            WHITE
        );
    }
}

void Entity::TakeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        isActive = false;
    }
}

Rectangle Entity::GetCollisionRect() const {
    return {
        position.x,
        position.y,
        width * scale,
        height * scale
    };
}

bool Entity::IsActive() const { return isActive; }

bool Entity::CheckCollision(const Entity& other) const {
    return CheckCollisionRecs(GetCollisionRect(), other.GetCollisionRect());
}

void Entity::SetPosition(const Vector2& newPosition) { position = newPosition; }
void Entity::SetScale(float newScale) { scale = newScale; }

Vector2 Entity::GetPosition() const { return position; }
Vector2 Entity::GetVelocity() const { return velocity; }
float Entity::GetWidth() const { return width; }
float Entity::GetHeight() const { return height; }
int Entity::GetHealth() const { return health; }
float Entity::GetScale() const { return scale; }