#include "LavaCrab.h"

LavaCrab::LavaCrab(float x, float y)
    : Enemy(x, y, 64, 64, 25, 180.0f, 20, 100),
    diveTimer(0) {

    std::string crawlFrames[] = {
        "assets/enemies/lavacrab/crawl_1.png",
        "assets/enemies/lavacrab/crawl_2.png"
    };
    animation = new Animation(crawlFrames, 2, 0.15f, true);
}

void LavaCrab::Update(float deltaTime) {
    diveTimer += deltaTime;

    if (diveTimer >= 2.0f) {
        position.y += 50;
        diveTimer = 0;
    }

    Enemy::Update(deltaTime);
}

void LavaCrab::Patrol() {
    velocity.x = -moveSpeed;
}

void LavaCrab::Attack() {}