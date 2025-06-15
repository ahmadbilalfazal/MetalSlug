#include "LevelCompleteState.h"
#include "PlayState.h"
#include "MenuState.h"

LevelCompleteState::LevelCompleteState(Game* game, int score, bool gameComplete)
    : game(game), currentScore(score), isGameComplete(gameComplete) {
}

LevelCompleteState::~LevelCompleteState() {
    UnloadTexture(background);
    UnloadTexture(completeTexture);
    UnloadSound(completeSound);
}

void LevelCompleteState::Enter() {
    background = LoadTexture("background.png");
    completeTexture = LoadTexture(isGameComplete ? "game_complete.png" : "level_complete.png");
    completeSound = LoadSound("level_complete.wav");
    PlaySound(completeSound);
}

void LevelCompleteState::Exit() {}

void LevelCompleteState::Update() {}

void LevelCompleteState::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexture(background, 0, 0, Color{ 255, 255, 255, 128 });

    DrawTexture(
        completeTexture,
        Game::GetScreenWidth() / 2 - completeTexture.width / 2,
        Game::GetScreenHeight() / 2 - completeTexture.height / 2 - 50,
        WHITE
    );

    DrawText(
        TextFormat("SCORE: %08d", currentScore),
        Game::GetScreenWidth() / 2 - MeasureText(TextFormat("SCORE: %08d", currentScore), 30) / 2,
        Game::GetScreenHeight() / 2 + 50,
        30,
        YELLOW
    );

    if (isGameComplete) {
        DrawText(
            "Press ENTER to return to menu",
            Game::GetScreenWidth() / 2 - MeasureText("Press ENTER to return to menu", 20) / 2,
            Game::GetScreenHeight() - 100,
            20,
            LIGHTGRAY
        );
    }
    else {
        DrawText(
            "Press ENTER to continue to next level",
            Game::GetScreenWidth() / 2 - MeasureText("Press ENTER to continue to next level", 20) / 2,
            Game::GetScreenHeight() - 100,
            20,
            LIGHTGRAY
        );
    }

    EndDrawing();
}

bool LevelCompleteState::ShouldTransition() {
    return IsKeyPressed(KEY_ENTER);
}

GameState* LevelCompleteState::GetNextState() {
    if (isGameComplete) {
        return new MenuState(game);
    }
    else {
        return new PlayState(game);
    }
}