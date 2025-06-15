#include "SoldierEnemy.h"

SoldierEnemy::SoldierEnemy(float x, float y)
    : Enemy(x, y, 64, 64, 30, 100.0f, 10, 100),
    patrolDistance(200.0f), currentPatrolDistance(0.0f),
    movingRight(false) {

    std::string walkFrames[] = { "walk_1_soldier.png",
                               "walk_2_soldier.png" };
    animation = new Animation(walkFrames, 2, 0.3f, true);
}

SoldierEnemy::~SoldierEnemy() {
}

void SoldierEnemy::Update(float deltaTime) {
    Enemy::Update(deltaTime);
    Patrol();

    static float attackTimer = 0.0f;
    attackTimer += deltaTime;
    if (attackTimer >= 2.0f) {
        Attack();
        attackTimer = 0.0f;
    }
}

void SoldierEnemy::Patrol() {
    if (movingRight) {
        velocity.x = moveSpeed;
        currentPatrolDistance += moveSpeed * GetFrameTime();
        if (currentPatrolDistance >= patrolDistance) {
            movingRight = false;
        }
    }
    else {
        velocity.x = -moveSpeed;
        currentPatrolDistance -= moveSpeed * GetFrameTime();
        if (currentPatrolDistance <= 0) {
            movingRight = true;
        }
    }
}

void SoldierEnemy::Attack() {
    if (bulletCount >= maxBullets) return;

    bullets[bulletCount] = new Bullet(
        position.x + width / 2,
        position.y + height / 2,
        (position.x < GetScreenWidth() / 2) ? 300.0f : -300.0f,
        0,
        300.0f,
        5,
        "enemy_bullet.png"
    );
    bulletCount++;

    bool allUsed = true;
    for (int i = 0; i < maxBullets; i++) {
        if (bullets[i] && bullets[i]->IsActive()) {
            allUsed = false;
            break;
        }
    }

    if (allUsed) {
        bulletCount = 0;
    }
}