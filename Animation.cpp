#include "Animation.h"

Animation::Animation(const std::string* framePaths, int count, float duration, bool looping)
    : frameCount(count), frameDuration(duration), currentTime(0),
    currentFrame(0), isLooping(looping), isPlaying(false) {

    frames = new Texture2D[frameCount];
    for (int i = 0; i < frameCount; i++) {
        frames[i] = LoadTexture(framePaths[i].c_str());
    }
}

Animation::~Animation() {
    for (int i = 0; i < frameCount; i++) {
        UnloadTexture(frames[i]);
    }
    delete[] frames;
}

void Animation::Update(float deltaTime) {
    if (!isPlaying) return;

    currentTime += deltaTime;
    if (currentTime >= frameDuration) {
        currentTime = 0;
        currentFrame++;

        if (currentFrame >= frameCount) {
            if (isLooping) {
                currentFrame = 0;
            }
            else {
                currentFrame = frameCount - 1;
                isPlaying = false;
            }
        }
    }
}

void Animation::Play() {
    isPlaying = true;
    if (currentFrame == frameCount - 1 && !isLooping) {
        Reset();
    }
}

void Animation::Stop() {
    isPlaying = false;
}

void Animation::Reset() {
    currentFrame = 0;
    currentTime = 0;
}

Texture2D Animation::GetCurrentFrame() const {
    return frames[currentFrame];
}

bool Animation::IsPlaying() const {
    return isPlaying;
}

bool Animation::IsFinished() const {
    return !isLooping && currentFrame == frameCount - 1;
}