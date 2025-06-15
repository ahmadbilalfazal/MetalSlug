#pragma once
#include "raylib.h"
#include "Player.h"
#include "Enemy.h"

class Level {
private:
    int levelNumber;
    Texture2D background;
    Texture2D foreground;
    Vector2 backgroundScroll;
    Vector2 foregroundScroll;
    float scrollSpeed;

    Player* player;
    Enemy** enemies;
    int enemyCount;
    int maxEnemies;

    int enemiesToSpawn;
    int enemiesSpawned;
    float spawnTimer;
    float spawnInterval;

public:
    Level(int number, const char* bgPath, const char* fgPath, float scroll);
    ~Level();

    void Load();
    void Unload();
    void Update(float deltaTime);
    void Draw();

    void SpawnEnemies();
    void SpawnEnemy(Enemy* enemy);

    bool IsComplete() const;
    int GetLevelNumber() const;

    Player* GetPlayer() const;
};