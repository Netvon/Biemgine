#pragma once

#include "Biemgine.h"

#include "..\globals\Difficulty.h";

using biemgine::Scene;
using biemgine::StateManager;

namespace spacebiem
{
    class DifficultyScene :
        public Scene
    {
    public:
        void input() override;
        void update() override;
        void render(const float deltaTime) override;
        void created() override;

        DifficultyScene(StateManager& manager)
            : Scene(manager)
        {};
        ~DifficultyScene() {};

    private:
        map<Difficulty, bool> progress;

    };
}

