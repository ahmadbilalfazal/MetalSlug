#pragma once
#include "Entity.h"
#include "Bullet.h"

class Player : public Entity {
private:
    bool isJumping;
    bool isShooting;
    bool isFacingRight;
    float moveSpeed;
    float jumpForce;
    float gravity;
    float friction;
    Bullet* bullets[10];
    int bulletCount;
    float shootCooldown;
    float currentShootTime;

public:
    Player(float x, float y);
    ~Player() override;

    void Update(float deltaTime) override;
    void Draw() override;
    void HandleInput();

    void Shoot();
    void Jump();
    void MoveLeft();
    void MoveRight();
    void StopMoving();

    Bullet** GetBullets();
    int GetBulletCount() const;
};