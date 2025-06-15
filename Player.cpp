#include "Player.h"
#include <iostream>

Player::Player(float x, float y)
    : Entity(x, y, 64, 64, 100), isJumping(false), isShooting(false),
    isFacingRight(true), moveSpeed(300.0f), jumpForce(600.0f),
    gravity(1500.0f), friction(1.0f), bulletCount(0) {

    for (int i = 0; i < 10; i++) {
        bullets[i] = nullptr;
    }

    std::string idleFrames[] = { "assets/player/idle_1.png", "assets/player/idle_2.png" };
    animation = new Animation(idleFrames, 2, 0.2f, true);
}

Player::~Player() {
    for (int i = 0; i < 10; i++) {
        if (bullets[i]) delete bullets[i];
    }
}

void Player::Update(float deltaTime) {
    velocity.x *= friction;

    if (isJumping) {
        velocity.y += gravity * deltaTime;
    }

    for (int i = 0; i < bulletCount; i++) {
        if (bullets[i] && bullets[i]->IsActive()) {
            bullets[i]->Update(deltaTime);
        }
    }

    if (position.y >= GetScreenHeight() - height) {
        position.y = GetScreenHeight() - height;
        velocity.y = 0;
        isJumping = false;
    }
}

void Player::Draw() {
    Entity::Draw();

    for (int i = 0; i < bulletCount; i++) {
        if (bullets[i] && bullets[i]->IsActive()) {
            bullets[i]->Draw();
        }
    }
}

void Player::HandleInput() {
    if (IsKeyDown(KEY_LEFT)) {
        MoveLeft();
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        MoveRight();
    }
    else {
        StopMoving();
    }

    if (IsKeyPressed(KEY_SPACE)) {
        Jump();
    }

    if (IsKeyPressed(KEY_Z)) {
        Shoot();
    }
}

void Player::Shoot() {
    if (bulletCount >= 10) return;

    float direction = isFacingRight ? 1.0f : -1.0f;
    bullets[bulletCount] = new Bullet(
        position.x + (isFacingRight ? width : 0),
        position.y + height / 2,
        direction * 500.0f,
        0,
        500.0f,
        10,
        "assets/bullets/player_bullet.png"
    );
    bulletCount++;

    bool allUsed = true;
    for (int i = 0; i < 10; i++) {
        if (bullets[i] && bullets[i]->IsActive()) {
            allUsed = false;
            break;
        }
    }

    if (allUsed) {
        bulletCount = 0;
    }
}

void Player::Jump() {
    if (!isJumping) {
        velocity.y = -jumpForce;
        isJumping = true;
    }
}

void Player::MoveLeft() {
    velocity.x = -moveSpeed;
    isFacingRight = false;
}

void Player::MoveRight() {
    velocity.x = moveSpeed;
    isFacingRight = true;
}

void Player::StopMoving() {
    velocity.x = 0;
}

Bullet** Player::GetBullets() {
    return bullets;
}

int Player::GetBulletCount() const {
    return bulletCount;
}