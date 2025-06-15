#pragma once
#include "raylib.h"
#include <vector>
#include <string>

class Animation {
private:
    std::vector<Texture2D> frames;
    float frameDuration;
    float currentTime;
    int currentFrame;
    bool isLooping;
    bool isPlaying;
    float scale;

public:
    Animation(const std::string* framePaths, int count, float duration, bool looping, float scale = 1.0f);
    ~Animation();

    void Update(float deltaTime);
    void Play() { isPlaying = true; }
    void Stop() { isPlaying = false; }
    void Reset() { currentFrame = 0; currentTime = 0; }

    Texture2D GetCurrentFrame() const;
    float GetScale() const { return scale; }
    void SetScale(float newScale);

    bool IsPlaying() const { return isPlaying; }
    bool IsFinished() const { return !isLooping && currentFrame >= (int)frames.size() - 1; }
};