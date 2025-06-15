#include "MenuState.h"
#include "PlayState.h"
#include "ControlsState.h"
#include <iostream>

MenuState::MenuState(Game* game)
    : game(game), selectedOption(0) {
}

MenuState::~MenuState() {
    UnloadTexture(background);
    UnloadTexture(logo);
    UnloadSound(selectSound);
    UnloadSound(confirmSound);
}

void MenuState::Enter() {
    background = LoadTexture("background.png");
    logo = LoadTexture("logo.png");
    selectSound = LoadSound("select.wav");
    confirmSound = LoadSound("confirm.wav");
}

void MenuState::Exit() {}

void MenuState::Update() {
    if (IsKeyPressed(KEY_DOWN)) {
        selectedOption = (selectedOption + 1) % 3;
        PlaySound(selectSound);
    }
    else if (IsKeyPressed(KEY_UP)) {
        selectedOption = (selectedOption - 1 + 3) % 3;
        PlaySound(selectSound);
    }
}

void MenuState::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexture(background, 0, 0, WHITE);

    int logoWidth = logo.width;
    int logoHeight = logo.height;
    float scale = 0.7f;
    DrawTextureEx(logo,
        Vector2{ (float)(Game::GetScreenWidth() / 2 - (logoWidth * scale) / 2), 50 },
        0.0f, scale, WHITE);

    for (int i = 0; i < 3; i++) {
        Color color = (i == selectedOption) ? YELLOW : WHITE;
        const char* text = options[i];
        int textWidth = MeasureText(text, 30);

        DrawText(text,
            Game::GetScreenWidth() / 2 - textWidth / 2,
            300 + i * 50,
            30, color);
    }

    DrawText("Use ARROW KEYS to navigate, ENTER to select",
        Game::GetScreenWidth() / 2 - MeasureText("Use ARROW KEYS to navigate, ENTER to select", 20) / 2,
        Game::GetScreenHeight() - 50,
        20, LIGHTGRAY);

    EndDrawing();
}

bool MenuState::ShouldTransition() {
    return IsKeyPressed(KEY_ENTER);
}

GameState* MenuState::GetNextState() {
    PlaySound(confirmSound);

    switch (selectedOption) {
    case 0: return new PlayState(game);
    case 1: return new ControlsState(game);
    case 2: game->Shutdown(); return nullptr;
    default: return nullptr;
    }
}