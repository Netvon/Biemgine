#include "AnimationComponent.h"

namespace biemgine
{
    AnimationComponent::AnimationComponent(float pStartValue, float pEndValue, float pTotalTime, std::function<void(float)> pOnUpdate, std::function<void()> pOnFinished, bool play)
        : startValue(pStartValue), endValue(pEndValue), totalTime(pTotalTime), onUpdate(pOnUpdate), onFinished(pOnFinished), isPlaying(play), isReversed(false), currentTime(0)
    {}


    AnimationComponent::~AnimationComponent()
    {}

    void AnimationComponent::play()
    {
        currentTime = 0;
        isReversed = false;
        isPlaying = true;

        update(0);
    }

    void AnimationComponent::playReversed()
    {
        currentTime = totalTime;
        isReversed = true;
        isPlaying = true;

        update(0);
    }

    void AnimationComponent::resume()
    {
        isPlaying = true;
    }

    void AnimationComponent::stop()
    {
        isPlaying = false;
    }

    void AnimationComponent::update(float deltaTime)
    {
        if (isPlaying)
        {
            bool done = false;
            if (!isReversed)
            {
                currentTime += deltaTime;

                if (currentTime >= totalTime)
                {
                    currentTime = totalTime;
                    done = true;
                }
            }
            else
            {
                currentTime -= deltaTime;

                if (currentTime <= 0)
                {
                    currentTime = 0;
                    done = true;
                }
            }

            float percentage = currentTime / totalTime;
            currentValue = (1 - percentage) * startValue + percentage * endValue;

            if(onUpdate)
                onUpdate(currentValue);

            if (done)
            {
                if(onFinished)
                    onFinished();

                isPlaying = false;
            }

        }
    }

    void AnimationComponent::setOnUpdate(std::function<void(float)> function)
    {
        onUpdate = function;
    }

    void AnimationComponent::setOnFinished(std::function<void()> function)
    {
        onFinished = function;
    }
}

