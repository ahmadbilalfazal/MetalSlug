#include "YetiMech.h"
#include "Bullet.h"

YetiMech::YetiMech(float x, float y)
    : BossEnemy(x, y, 256, 256, 500, 150.0f, 30, 1000),
    chargeCooldown(0) {

    std::string phase1Frames[] = { "phase1_yetimech.png" };
    std::string phase2Frames[] = { "phase2_yetimech.png" };
    std::string phase3Frames[] = { "phase3_yetimech.png" };

    animations[0] = new Animation(phase1Frames, 1, 1.0f, true);
    animations[1] = new Animation(phase2Frames, 1, 1.0f, true);
    animations[2] = new Animation(phase3Frames, 1, 1.0f, true);

    currentAnimation = animations[0];
}

void YetiMech::Update(float deltaTime) {
    if (health < 300 && phase == 1) {
        phase = 2;
        currentAnimation = animations[1];
        moveSpeed *= 1.5f;
    }
    else if (health < 150 && phase == 2) {
        phase = 3;
        currentAnimation = animations[2];
    }

    switch (phase) {
    case 1:
        chargeCooldown -= deltaTime;
        if (chargeCooldown <= 0) {
            velocity.x = -moveSpeed * 2.0f;
            chargeCooldown = 5.0f;
        }
        break;

    case 2:
        if (rand() % 100 < 2) {
            Attack();
        }
        break;

    case 3:
        velocity.x = -moveSpeed * 0.5f;
        if (rand() % 100 < 10) {
            Attack();
        }
        break;
    }

    BossEnemy::Update(deltaTime);
}

void YetiMech::Patrol() {
    switch (phase) {
    case 1:
        velocity.x = -moveSpeed * 0.7f;
        break;
    case 2:
        velocity.x = -moveSpeed * 0.5f;
        break;
    case 3:
        velocity.x = -moveSpeed * 0.3f;
        break;
    }
}

void YetiMech::Attack() {
    switch (phase) {
    case 1:
        bullets[bulletCount++] = new Bullet(
            position.x, position.y + height / 2,
            -500.0f, 0, 500.0f, 20,
            "ice_shard.png"
        );
        break;

    case 2:
        bullets[bulletCount++] = new Bullet(
            position.x, position.y + height,
            0, 300.0f, 300.0f, 0,
            "ice_shard.png"
        );
        break;

    case 3:
        for (int i = 0; i < 5; i++) {
            bullets[bulletCount++] = new Bullet(
                position.x, position.y + (i * 50),
                -400.0f, 0, 400.0f, 10,
                "ice_shard.png"
            );
        }
        break;
    }

    if (bulletCount >= maxBullets) bulletCount = 0;
}