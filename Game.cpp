#include "Game.h"
#include "MenuState.h"

Game::Game() : currentState(nullptr), isRunning(false) {}

Game::~Game() {
    if (currentState) delete currentState;
}

void Game::Initialize() {
    InitWindow(screenWidth, screenHeight, "Metal Slug OOP");
    SetTargetFPS(60);
    InitAudioDevice();

    currentState = new MenuState(this);
    isRunning = true;
}

void Game::Update() {
    if (currentState) {
        currentState->Update();

        if (currentState->ShouldTransition()) {
            GameState* newState = currentState->GetNextState();
            delete currentState;
            currentState = newState;
        }
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    if (currentState) {
        currentState->Draw();
    }

    EndDrawing();
}

void Game::Shutdown() {
    if (currentState) delete currentState;
    CloseAudioDevice();
    CloseWindow();
}

bool Game::ShouldClose() const {
    return WindowShouldClose();
}

int Game::GetScreenWidth() { return screenWidth; }
int Game::GetScreenHeight() { return screenHeight; }

void Game::ChangeState(GameState* newState) {
    if (currentState) delete currentState;
    currentState = newState;
}