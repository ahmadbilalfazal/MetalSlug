#include "Animation.h"
#include <stdexcept>

Animation::Animation(const std::string* framePaths, int count, float duration, bool looping, float scale)
    : frameDuration(duration), currentTime(0), currentFrame(0),
    isLooping(looping), isPlaying(false), scale(scale) {

    if (count <= 0) throw std::runtime_error("Animation: Frame count must be > 0");
    if (duration <= 0) throw std::runtime_error("Animation: Duration must be > 0");

    frames.reserve(count);
    for (int i = 0; i < count; i++) {
        Texture2D tex = LoadTexture(framePaths[i].c_str());
        if (tex.id == 0) {
            TraceLog(LOG_WARNING, "Animation: Failed to load %s", framePaths[i].c_str());
        }
        frames.push_back(tex);
    }
}

Animation::~Animation() {
    for (auto& frame : frames) {
        UnloadTexture(frame);
    }
}

void Animation::Update(float deltaTime) {
    if (!isPlaying || frames.empty()) return;

    currentTime += deltaTime;
    while (currentTime >= frameDuration && frameDuration > 0) {
        currentTime -= frameDuration;
        currentFrame++;

        if (currentFrame >= (int)frames.size()) {
            currentFrame = isLooping ? 0 : (int)frames.size() - 1;
            if (!isLooping) isPlaying = false;
        }
    }
}

Texture2D Animation::GetCurrentFrame() const {
    return frames.empty() ? Texture2D{ 0 } : frames[currentFrame];
}

void Animation::SetScale(float newScale) {
    if (newScale <= 0) {
        TraceLog(LOG_WARNING, "Animation: Invalid scale (must be >0)");
        return;
    }
    scale = newScale;
}