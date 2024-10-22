#pragma once

#include "Biemgine.h"

using biemgine::Scene;
using biemgine::StateManager;

namespace spacebiem
{
    class HighScoreScene :
        public Scene
    {
    public:
        void input() override;
        void update() override;
        void render(const float deltaTime) override;
        void created() override;

        HighScoreScene(StateManager& manager, int lastScore = -1)
            : Scene(manager),
            lastScore(lastScore){};
        ~HighScoreScene() {};

    private:
        int lastScore;

    };
}

