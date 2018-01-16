#pragma once

#include "Biemgine.h"
#include "../globals/Difficulty.h"

using biemgine::Scene;
using biemgine::StateManager;

namespace spacebiem
{
    class StoryScene :
        public Scene
    {
    public:
        void input() override;
        void update() override;
        void render(const float deltaTime) override;
        void created() override;

        StoryScene(StateManager& manager, Difficulty pNextDifficulty, bool pFromLevel = false)
            : Scene(manager), nextDifficulty(pNextDifficulty), fromLevel(pFromLevel){};
        ~StoryScene() {};

    private:
        Difficulty nextDifficulty;
        bool fromLevel;
    };
}

