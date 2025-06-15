#pragma once
#include "Enemy.h"

class BossEnemy : public Enemy {
protected:
    Animation* animations[3];
    Animation* currentAnimation;
    int phase;

public:
    BossEnemy(float x, float y, float w, float h, int hp, float speed, int dmg, int score);
    virtual ~BossEnemy();

    void Update(float deltaTime) override;
    void Draw() override;
    virtual void Attack() = 0;

    int GetPhase() const { return phase; }
};