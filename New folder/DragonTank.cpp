#include "DragonTank.h"
#include "Bullet.h"
#include <cmath>

DragonTank::DragonTank(float x, float y)
    : BossEnemy(x, y, 320, 320, 800, 100.0f, 40, 2000),
    fireballCooldown(0) {

    std::string phase1Frames[] = { "phase1_dragontank.png" };
    std::string phase2Frames[] = { "phase2_dragontank.png" };
    std::string phase3Frames[] = { "phase3_dragontank.png" };

    animations[0] = new Animation(phase1Frames, 1, 1.0f, true);
    animations[1] = new Animation(phase2Frames, 1, 1.0f, true);
    animations[2] = new Animation(phase3Frames, 1, 1.0f, true);

    currentAnimation = animations[0];
}

void DragonTank::Update(float deltaTime) {
    if (health < 500 && phase == 1) {
        phase = 2;
        currentAnimation = animations[1];
        moveSpeed *= 0.5f;
    }
    else if (health < 200 && phase == 2) {
        phase = 3;
        currentAnimation = animations[2];
    }

    fireballCooldown -= deltaTime;

    switch (phase) {
    case 1:
        if (fireballCooldown <= 0) {
            Attack();
            fireballCooldown = 1.5f;
        }
        break;

    case 2:
        velocity.x = -moveSpeed * 0.3f;
        if (fireballCooldown <= 0) {
            Attack();
            fireballCooldown = 3.0f;
        }
        break;

    case 3:
        velocity.x = -moveSpeed * (sin(GetTime() * 2) * 2.0f);
        if (fireballCooldown <= 0) {
            Attack();
            fireballCooldown = 0.5f;
        }
        break;
    }

    BossEnemy::Update(deltaTime);
}

void DragonTank::Patrol() {
    velocity.x = -moveSpeed * 0.4f;
}

void DragonTank::Attack() {
    switch (phase) {
    case 1:
        for (int i = 0; i < 8; i++) {
            float angle = i * (360.0f / 8) * DEG2RAD;
            bullets[bulletCount++] = new Bullet(
                position.x + width / 2, position.y + height / 2,
                cos(angle) * 300.0f, sin(angle) * 300.0f,
                300.0f, 15, "fireball.png"
            );
        }
        break;

    case 2:
        for (int i = 0; i < GetScreenWidth(); i += 50) {
            bullets[bulletCount++] = new Bullet(
                i, GetScreenHeight() - 30,
                0, -400.0f, 400.0f, 10,
                "lava_blob.png"
            );
        }
        break;

    case 3:
        for (int i = 0; i < 3; i++) {
            bullets[bulletCount++] = new Bullet(
                position.x, position.y + (i * 100),
                -400.0f, 0, 400.0f, 25,
                "grenade.png"
            );
        }
        break;
    }

    if (bulletCount >= maxBullets) bulletCount = 0;
}