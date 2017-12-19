#include "AnimationComponent.h"

biemgine::AnimationComponent::AnimationComponent(float pStartValue, float pEndValue, float pTotalTime, std::function<void(float)> pOnUpdate, std::function<void> pOnFinished)
    : startValue(pStartValue), endValue(pEndValue), totalTime(pTotalTime), onUpdate(pOnUpdate), onFinished(pOnFinished), currentTime(0)
{}

biemgine::AnimationComponent::~AnimationComponent()
{}

void biemgine::AnimationComponent::play()
{
    isPlaying = true;
}

void biemgine::AnimationComponent::stop()
{
    isPlaying = false;
}

void biemgine::AnimationComponent::update(float deltaTime)
{
    if (isPlaying)
    {
        currentTime += deltaTime;

        if (currentTime > totalTime)
        {
            currentTime = totalTime;
            onFinished;
            isPlaying = false;
        }

        float percentage = currentTime / totalTime;
        currentValue = (1 - percentage) * startValue + percentage * endValue;

        onUpdate(currentValue);
    }
}
