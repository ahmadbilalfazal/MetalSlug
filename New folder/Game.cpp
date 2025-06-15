#include "Game.h"
#include "MenuState.h"

Game::Game() : currentState(nullptr), isRunning(false) {}

Game::~Game() {
    if (currentState) delete currentState;
}

void Game::Initialize() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Metal Slug OOP");
    SetTargetFPS(60);
    InitAudioDevice();

    currentState = new MenuState(this);
    currentState->Enter();
    isRunning = true;
    renderTarget = LoadRenderTexture(screenWidth, screenHeight);

}

void Game::Update() {
    if (currentState) {
        currentState->Update();

        if (currentState->ShouldTransition()) {
            GameState* newState = currentState->GetNextState();
            if (newState) {
                currentState->Exit();
                delete currentState;
                currentState = newState;
                currentState->Enter();
            }
        }
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    BeginTextureMode(renderTarget);
    ClearBackground(BLANK);

    if (currentState) {
        currentState->Draw();
    }

    EndTextureMode();

    Rectangle sourceRec = { 0, 0, (float)renderTarget.texture.width, (float)-renderTarget.texture.height };
    Rectangle destRec = { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() };
    Vector2 origin = { 0, 0 };

    DrawTexturePro(
        renderTarget.texture,
        sourceRec,
        destRec,
        origin,
        0.0f,
        WHITE
    );

    EndDrawing();
}


void Game::Shutdown() {
    UnloadRenderTexture(renderTarget);
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
    if (currentState) {
        currentState->Exit();
        delete currentState;
    }
    currentState = newState;
    if (currentState) {
        currentState->Enter();
    }
}