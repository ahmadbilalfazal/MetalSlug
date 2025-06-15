#include "Level.h"
#include "SoldierEnemy.h"
#include "HelicopterEnemy.h"
#include "TankEnemy.h"
#include "SnowTrooper.h"
#include "LavaCrab.h"
#include "YetiMech.h"
#include "DragonTank.h"

Level::Level(int number, const char* bgPath, const char* fgPath, float scroll)
    : levelNumber(number), scrollSpeed(scroll), player(nullptr),
    enemies(nullptr), enemyCount(0), maxEnemies(20),
    enemiesToSpawn(8 + (number * 4)), enemiesSpawned(0),
    spawnTimer(0), spawnInterval(2.0f) {

    background = LoadTexture(bgPath);
    foreground = LoadTexture(fgPath);
    backgroundScroll = { 0, 0 };
    foregroundScroll = { 0, 0 };

    enemies = new Enemy * [maxEnemies];
    for (int i = 0; i < maxEnemies; i++) {
        enemies[i] = nullptr;
    }
}

Level::~Level() {
    Unload();
}

void Level::Load() {
    player = new Player(100, GetScreenHeight() - 150);
    spawnTimer = spawnInterval;
}

void Level::Unload() {
    UnloadTexture(background);
    UnloadTexture(foreground);

    if (player) {
        delete player;
        player = nullptr;
    }

    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i]) {
            delete enemies[i];
            enemies[i] = nullptr;
        }
    }

    delete[] enemies;
    enemies = nullptr;
    enemyCount = 0;
}

void Level::Update(float deltaTime) {
    backgroundScroll.x -= scrollSpeed * deltaTime;
    foregroundScroll.x -= scrollSpeed * 1.5f * deltaTime;

    if (backgroundScroll.x <= -background.width) {
        backgroundScroll.x = 0;
    }
    if (foregroundScroll.x <= -foreground.width) {
        foregroundScroll.x = 0;
    }

    if (player) {
        player->HandleInput();
        player->Update(deltaTime);

        if (player->GetPosition().x < 50) {
            Vector2 playerPosition = player->GetPosition();
            playerPosition.x = 50;
            player->SetPosition(playerPosition);

        }
        else if (player->GetPosition().x > GetScreenWidth() - player->GetWidth()) {
            Vector2 playerPosition = player->GetPosition();
            playerPosition.x = GetScreenWidth() - player->GetWidth();
            player->SetPosition(playerPosition);
        }
    }

    spawnTimer -= deltaTime;
    if (spawnTimer <= 0 && enemiesSpawned < enemiesToSpawn) {
        SpawnEnemies();
        spawnTimer = spawnInterval;
    }

    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i] && enemies[i]->IsActive()) {
            enemies[i]->Update(deltaTime);

            if (player && player->IsActive() &&
                enemies[i]->CheckCollision(*player)) {
                player->TakeDamage(enemies[i]->GetDamage());
            }

            Bullet** playerBullets = player->GetBullets();
            for (int j = 0; j < player->GetBulletCount(); j++) {
                if (playerBullets[j] && playerBullets[j]->IsActive() &&
                    CheckCollisionRecs(enemies[i]->GetCollisionRect(),
                        playerBullets[j]->GetCollisionRect())) {
                    enemies[i]->TakeDamage(playerBullets[j]->GetDamage());
                    playerBullets[j]->SetActive(false);
                }
            }
        }
    }
}

void Level::Draw() {
    DrawTextureEx(background, backgroundScroll, 0.0f, 1.0f, WHITE);
    DrawTextureEx(background, Vector2{ backgroundScroll.x + background.width, backgroundScroll.y },
        0.0f, 1.0f, WHITE);

    DrawTextureEx(foreground, foregroundScroll, 0.0f, 1.0f, WHITE);
    DrawTextureEx(foreground, Vector2{ foregroundScroll.x + foreground.width, foregroundScroll.y },
        0.0f, 1.0f, WHITE);

    if (player && player->IsActive()) {
        player->Draw();
    }

    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i] && enemies[i]->IsActive()) {
            enemies[i]->Draw();

            Bullet** enemyBullets = enemies[i]->GetBullets();
            for (int j = 0; j < enemies[i]->GetBulletCount(); j++) {
                if (enemyBullets[j] && enemyBullets[j]->IsActive()) {
                    enemyBullets[j]->Draw();

                    if (player && player->IsActive() &&
                        CheckCollisionRecs(player->GetCollisionRect(),
                            enemyBullets[j]->GetCollisionRect())) {
                        player->TakeDamage(enemyBullets[j]->GetDamage());
                        enemyBullets[j]->SetActive(false);
                    }
                }
            }
        }
    }

    if (player) {
        Bullet** playerBullets = player->GetBullets();
        for (int i = 0; i < player->GetBulletCount(); i++) {
            if (playerBullets[i] && playerBullets[i]->IsActive()) {
                playerBullets[i]->Draw();
            }
        }
    }
}

void Level::SpawnEnemies() {
    if (enemyCount >= maxEnemies || enemiesSpawned >= enemiesToSpawn) return;

    float spawnX = GetScreenWidth() + 100;
    float spawnY = GetScreenHeight() - 150;

    if (enemiesSpawned == enemiesToSpawn - 1) {
        switch (levelNumber) {
        case 4:
            enemies[enemyCount++] = new YetiMech(spawnX, spawnY);
            break;
        case 5:
            enemies[enemyCount++] = new DragonTank(spawnX, spawnY);
            break;
        default:
            break;
        }
        enemiesSpawned++;
        return;
    }

    switch (levelNumber) {
    case 1:
        if (rand() % 100 < 70) {
            enemies[enemyCount++] = new SoldierEnemy(spawnX, spawnY);
        }
        else {
            enemies[enemyCount++] = new HelicopterEnemy(spawnX, spawnY - 100);
        }
        break;

    case 2:
        if (rand() % 100 < 60) {
            enemies[enemyCount++] = new SoldierEnemy(spawnX, spawnY);
        }
        else {
            enemies[enemyCount++] = new TankEnemy(spawnX, spawnY);
        }
        break;

    case 3:
        if (rand() % 100 < 50) {
            enemies[enemyCount++] = new SoldierEnemy(spawnX, spawnY);
        }
        else {
            enemies[enemyCount++] = new HelicopterEnemy(spawnX, spawnY - 100);
        }
        break;

    case 4:
        if (rand() % 100 < 70) {
            enemies[enemyCount++] = new SnowTrooper(spawnX, spawnY);
        }
        else {
            enemies[enemyCount++] = new TankEnemy(spawnX, spawnY);
        }
        break;

    case 5:
        if (rand() % 100 < 60) {
            enemies[enemyCount++] = new LavaCrab(spawnX, GetScreenHeight() - 50);
        }
        else {
            enemies[enemyCount++] = new HelicopterEnemy(spawnX, spawnY - 100);
        }
        break;
    }
    enemiesSpawned++;
}

void Level::SpawnEnemy(Enemy* enemy) {
    if (enemyCount < maxEnemies) {
        enemies[enemyCount++] = enemy;
    }
}

bool Level::IsComplete() const {
    return enemiesSpawned >= enemiesToSpawn && enemyCount == 0;
}

int Level::GetLevelNumber() const {
    return levelNumber;
}

Player* Level::GetPlayer() const {
    return player;
}