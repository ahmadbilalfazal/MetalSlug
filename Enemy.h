#pragma once
#include "Entity.h"
#include "Bullet.h"

class Enemy : public Entity {
protected:
    float moveSpeed;
    int damage;
    int scoreValue;
    Bullet* bullets[5];
    int bulletCount;
    int maxBullets = 5;
	int maxHealth = 100;
public:
    Enemy(float x, float y, float w, float h, int hp, float speed, int dmg, int score);
    virtual ~Enemy();

    virtual void Update(float deltaTime) override;
    virtual void Patrol() = 0;
    virtual void Attack() = 0;

    int GetScoreValue() const;
    Bullet** GetBullets();
    int GetBulletCount() const;
    int GetDamage() const { return damage; }
};