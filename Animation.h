#pragma once
#include "raylib.h"
#include <string>

class Animation {
private:
    Texture2D* frames;
    int frameCount;
    float frameDuration;
    float currentTime;
    int currentFrame;
    bool isLooping;
    bool isPlaying;

public:
    Animation(const std::string* framePaths, int count, float duration, bool looping);
    ~Animation();

    void Update(float deltaTime);
    void Play();
    void Stop();
    void Reset();

    Texture2D GetCurrentFrame() const;
    bool IsPlaying() const;
    bool IsFinished() const;
};