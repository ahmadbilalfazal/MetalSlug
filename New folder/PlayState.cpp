#include "PlayState.h"
#include "GameOverState.h"
#include "LevelCompleteState.h"
#include "MenuState.h"

PlayState::PlayState(Game* game)
    : game(game), currentLevel(nullptr), currentLevelNumber(1),
    playerScore(0), isPaused(false) {
    LoadLevel(currentLevelNumber);
}

PlayState::~PlayState() {
    UnloadLevel();
    if (pauseTexture.id) UnloadTexture(pauseTexture);
    if (levelStartSound.frameCount > 0) UnloadSound(levelStartSound);
    if (gameOverSound.frameCount > 0) UnloadSound(gameOverSound);
}

void PlayState::Enter() {
    pauseTexture = LoadTexture("pause.png");
    levelStartSound = LoadSound("level_start.wav");
    gameOverSound = LoadSound("game_over.wav");
    PlaySound(levelStartSound);
}

void PlayState::Exit() {
    UnloadLevel();
}

void PlayState::Update() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        isPaused = !isPaused;
    }

    if (!isPaused && currentLevel) {
        HandleInput();
        currentLevel->Update(GetFrameTime());
        CheckPlayerState();
    }
}

void PlayState::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    if (currentLevel) {
        currentLevel->Draw();
        DrawHUD();
    }

    if (isPaused) {
        DrawPauseMenu();
    }

    EndDrawing();
}

bool PlayState::ShouldTransition() {
    if (IsKeyPressed(KEY_ESCAPE)) return true;
    if (currentLevel && currentLevel->GetPlayer()->GetHealth() <= 0) return true;
    if (currentLevel && currentLevel->IsComplete()) return true;
    return false;
}

GameState* PlayState::GetNextState() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        return new MenuState(game);
    }

    if (currentLevel && currentLevel->GetPlayer()->GetHealth() <= 0) {
        PlaySound(gameOverSound);
        return new GameOverState(game, playerScore);
    }

    if (currentLevel && currentLevel->IsComplete()) {
        currentLevelNumber++;
        if (currentLevelNumber > 5) {
            return new LevelCompleteState(game, playerScore, true);
        }
        else {
            return new LevelCompleteState(game, playerScore, false);
        }
    }

    return nullptr;
}

void PlayState::LoadLevel(int levelNumber) {
    const char* bgPath = "";
    const char* fgPath = "";
    float scrollSpeed = 50.0f;

    switch (levelNumber) {
    case 1:
        bgPath = "level1_bg.png";
        fgPath = "level1_fg.png";
        break;
    case 2:
        bgPath = "level2_bg.png";
        fgPath = "level2_fg.png";
        scrollSpeed = 60.0f;
        break;
    case 3:
        bgPath = "level3_bg.png";
        fgPath = "level3_fg.png";
        scrollSpeed = 70.0f;
        break;
    case 4:
        bgPath = "level4_bg.png";
        fgPath = "level4_fg.png";
        scrollSpeed = 80.0f;
        break;
    case 5:
        bgPath = "level5_bg.png";
        fgPath = "level5_fg.png";
        scrollSpeed = 100.0f;
        break;
    }

    if (currentLevel) {
        UnloadLevel();
    }
    currentLevel = new Level(levelNumber, bgPath, fgPath, scrollSpeed);
    if (currentLevel) {
        currentLevel->Load();
    }
}

void PlayState::UnloadLevel() {
    if (currentLevel) {
        currentLevel->Unload();
        delete currentLevel;
        currentLevel = nullptr;
    }
}

void PlayState::HandleInput() {
    if (IsKeyPressed(KEY_R)) {
        UnloadLevel();
        LoadLevel(currentLevelNumber);
    }
}

void PlayState::CheckPlayerState() {
    if (currentLevel && currentLevel->GetPlayer()->GetHealth() <= 0) {
        PlaySound(gameOverSound);
    }
}

void PlayState::DrawHUD() {
    DrawText(TextFormat("SCORE: %08d", playerScore), 20, 20, 20, WHITE);

    int health = currentLevel->GetPlayer()->GetHealth();
    Color healthColor = (health > 50) ? GREEN : (health > 20) ? YELLOW : RED;
    DrawText(TextFormat("HEALTH: %d", health), 20, 50, 20, healthColor);

    DrawText(TextFormat("LEVEL: %d", currentLevelNumber), 20, 80, 20, BLUE);
}

void PlayState::DrawPauseMenu() {
    DrawRectangle(0, 0, Game::GetScreenWidth(), Game::GetScreenHeight(), Color{ 0, 0, 0, 200 });

    DrawTexture(pauseTexture,
        Game::GetScreenWidth() / 2 - pauseTexture.width / 2,
        Game::GetScreenHeight() / 2 - pauseTexture.height / 2 - 50,
        WHITE);

    DrawText("PAUSED",
        Game::GetScreenWidth() / 2 - MeasureText("PAUSED", 40) / 2,
        Game::GetScreenHeight() / 2 + 50,
        40, WHITE);

    DrawText("Press ESC to resume",
        Game::GetScreenWidth() / 2 - MeasureText("Press ESC to resume", 20) / 2,
        Game::GetScreenHeight() / 2 + 100,
        20, LIGHTGRAY);

    DrawText("Press M to return to menu",
        Game::GetScreenWidth() / 2 - MeasureText("Press M to return to menu", 20) / 2,
        Game::GetScreenHeight() / 2 + 130,
        20, LIGHTGRAY);
}