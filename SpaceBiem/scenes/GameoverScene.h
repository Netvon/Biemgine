#pragma once

#include "Biemgine.h"

using biemgine::Scene;
using biemgine::StateManager;

namespace spacebiem
{
    class GameoverScene :
        public Scene
    {
    public:
        void input() override;
        void update() override;
        void render(const float deltaTime) override;
        void created() override;

        GameoverScene(StateManager& manager, int score = 0, map<string, int> resources = map<string, int>(), map<string, int> planetsScore = map<string, int>())
            : Scene(manager),
            score(score),
            resources(resources),
            planetsScore(planetsScore)
        {};
        ~GameoverScene() {};

    private:
        int score;
        map<string, int> resources;
        map<string, int> planetsScore;

    };
}

