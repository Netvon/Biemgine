#pragma once

#include "dlldef.h"
#include "components\Component.h"

#include <String>
#include <functional>

using std::function;

namespace biemgine
{
    class BIEMGINE AnimationComponent :
        public Component
    {
    public:
        AnimationComponent(float pStartValue, float pEndValue, float pTotalTime, std::function<void(float)> pOnUpdate, std::function<void()> pOnFinished, bool play = true);
        ~AnimationComponent();

        void play();
        void playReversed();
        void resume();
        void stop();
        void update(float deltaTime);

        void setOnFinished(std::function<void()> function);

    private:
        float startValue;
        float endValue;
        float totalTime;

        std::function<void(float)> onUpdate;
        std::function<void()> onFinished;

        float currentValue;
        float currentTime;
        bool isPlaying;
        bool isReversed;
    };
}
