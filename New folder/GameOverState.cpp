#include "GameOverState.h"
#include "MenuState.h"

GameOverState::GameOverState(Game* game, int score)
    : game(game), finalScore(score) {
}

GameOverState::~GameOverState() {
    UnloadTexture(background);
    UnloadTexture(gameOverTexture);
    UnloadSound(gameOverSound);
}

void GameOverState::Enter() {
    background = LoadTexture("background.png");
    gameOverTexture = LoadTexture("game_over.png");
    gameOverSound = LoadSound("game_over.wav");
    PlaySound(gameOverSound);
}

void GameOverState::Exit() {
}

void GameOverState::Update() {}

void GameOverState::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexture(background, 0, 0, Color{ 255, 255, 255, 128 });

    DrawTexture(
        gameOverTexture,
        Game::GetScreenWidth() / 2 - gameOverTexture.width / 2,
        Game::GetScreenHeight() / 2 - gameOverTexture.height / 2 - 50,
        WHITE
    );

    DrawText(
        TextFormat("FINAL SCORE: %08d", finalScore),
        Game::GetScreenWidth() / 2 - MeasureText(TextFormat("FINAL SCORE: %08d", finalScore), 30) / 2,
        Game::GetScreenHeight() / 2 + 50,
        30,
        YELLOW
    );

    DrawText(
        "Press ENTER to return to menu",
        Game::GetScreenWidth() / 2 - MeasureText("Press ENTER to return to menu", 20) / 2,
        Game::GetScreenHeight() - 100,
        20,
        LIGHTGRAY
    );

    EndDrawing();
}

bool GameOverState::ShouldTransition() {
    return IsKeyPressed(KEY_ENTER);
}

GameState* GameOverState::GetNextState() {
    return new MenuState(game);
}