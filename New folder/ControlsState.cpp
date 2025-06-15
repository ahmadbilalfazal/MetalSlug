#include "ControlsState.h"
#include "MenuState.h"

ControlsState::ControlsState(Game* game) : game(game) {
}

ControlsState::~ControlsState() {
    UnloadTexture(controlsTexture);
    UnloadTexture(background);
    UnloadSound(backSound);
}

void ControlsState::Enter() {
    controlsTexture = LoadTexture("controls.png");
    background = LoadTexture("background.png");
    backSound = LoadSound("back.wav");
}

void ControlsState::Exit() {}

void ControlsState::Update() {
    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_B)) {
        PlaySound(backSound);
    }
}

void ControlsState::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexture(background, 0, 0, Color{ 255, 255, 255, 128 });

    DrawTexture(controlsTexture,
        Game::GetScreenWidth() / 2 - controlsTexture.width / 2,
        Game::GetScreenHeight() / 2 - controlsTexture.height / 2,
        WHITE);

    DrawText("Press ESC or B to go back",
        Game::GetScreenWidth() / 2 - MeasureText("Press ESC or B to go back", 20) / 2,
        Game::GetScreenHeight() - 50,
        20, LIGHTGRAY);

    EndDrawing();
}

bool ControlsState::ShouldTransition() {
    return IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_B);
}

GameState* ControlsState::GetNextState() {
    PlaySound(backSound);
    return new MenuState(game);
}