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

        StoryScene(StateManager& manager, Difficulty pNextDifficulty)
            : Scene(manager), nextDifficulty(pNextDifficulty){};
        ~StoryScene() {};

    private:
        Difficulty nextDifficulty;
    };
}

