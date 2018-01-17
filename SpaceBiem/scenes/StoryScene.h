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

        StoryScene(StateManager& manager, Difficulty pNextDifficulty, bool pFromLevel = false, map<string, int> resources = map<string, int>())
            : Scene(manager), nextDifficulty(pNextDifficulty), fromLevel(pFromLevel), resources(resources){};
        ~StoryScene() {};

    private:
        Difficulty nextDifficulty;
        bool fromLevel;

        map<string, int> resources;
    };
}

