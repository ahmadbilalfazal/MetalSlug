#include "Player.h"
#include <iostream>

Player::Player(float x, float y)
    : Entity(x, y, 64, 64, 100, 2.0f),
    isJumping(false),
    isShooting(false),
    isFacingRight(true),
    moveSpeed(500.0f),
    jumpForce(800.0f),
    gravity(2000.0f),
    friction(0.85f),
    bulletCount(0),
    shootCooldown(0.2f),
    currentShootTime(0) {

    for (int i = 0; i < 10; i++) {
        bullets[i] = nullptr;
    }

    std::string idleFrames[] = { "idle_1.png", "idle_2.png" };
    animation = new Animation(idleFrames, 2, 0.2f, true, 1.0f);
}

Player::~Player() {
    for (int i = 0; i < 10; i++) {
        if (bullets[i]) delete bullets[i];
    }
}

void Player::Update(float deltaTime) {
    if (currentShootTime > 0) {
        currentShootTime -= deltaTime;
    }

    if (isJumping) {
        velocity.y += gravity * deltaTime;
    }

    if (!(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT))) {
        velocity.x *= friction;
    }

    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    if (position.y >= GetScreenHeight() - height * GetScale()) {
        position.y = GetScreenHeight() - height * GetScale();
        velocity.y = 0;
        isJumping = false;
    }

    for (int i = 0; i < bulletCount; i++) {
        if (bullets[i] && bullets[i]->IsActive()) {
            bullets[i]->Update(deltaTime);
        }
    }
}

void Player::Draw() {
    if (animation && isActive) {
        Texture2D frame = animation->GetCurrentFrame();

        Rectangle sourceRec;
        sourceRec.x = 0;
        sourceRec.y = 0;
        sourceRec.width = (float)frame.width;
        sourceRec.height = (float)frame.height;

        Rectangle destRec;
        destRec.x = position.x;
        destRec.y = position.y;
        destRec.width = width * 2.0f;
        destRec.height = height * 2.0f;

        Vector2 origin;
        origin.x = 0;
        origin.y = 0;

        DrawTexturePro(
            frame,
            sourceRec,
            destRec,
            origin,
            0.0f,
            WHITE
        );
    }

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

    if (IsKeyDown(KEY_Z) && currentShootTime <= 0) {
        Shoot();
        currentShootTime = shootCooldown;
    }
}

void Player::Shoot() {
    int freeIndex = -1;
    for (int i = 0; i < bulletCount; i++) {
        if (bullets[i] && !bullets[i]->IsActive()) {
            freeIndex = i;
            break;
        }
    }

    if (freeIndex == -1 && bulletCount < 10) {
        freeIndex = bulletCount++;
    }

    if (freeIndex != -1) {
        if (bullets[freeIndex]) {
            delete bullets[freeIndex];
        }

        float direction = isFacingRight ? 1.0f : -1.0f;
        bullets[freeIndex] = new Bullet(
            position.x + (isFacingRight ? width : -20),
            position.y + height / 2,
            direction * 800.0f,
            0,
            800.0f,
            20,
            "player_bullet.png"
        );
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