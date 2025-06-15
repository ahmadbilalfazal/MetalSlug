#include "Entity.h"
#include "Animation.h"

Entity::Entity(float x, float y, float w, float h, int hp)
    : position{ x, y }, velocity{ 0, 0 }, width(w), height(h),
    health(hp), isActive(true), animation(nullptr) {
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
    if (animation && isActive) {
        Texture2D frame = animation->GetCurrentFrame();
        DrawTexture(frame, position.x, position.y, WHITE);
    }
}

void Entity::TakeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        isActive = false;
    }
}

Rectangle Entity::GetCollisionRect() const {
    return { position.x, position.y, width, height };
}

bool Entity::IsActive() const { return isActive; }

bool Entity::CheckCollision(const Entity& other) const {
    return CheckCollisionRecs(GetCollisionRect(), other.GetCollisionRect());
}
void Entity::SetPosition(const Vector2& newPosition) { position = newPosition; }

Vector2 Entity::GetPosition() const { return position; }
Vector2 Entity::GetVelocity() const { return velocity; }
float Entity::GetWidth() const { return width; }
float Entity::GetHeight() const { return height; }
int Entity::GetHealth() const { return health; }