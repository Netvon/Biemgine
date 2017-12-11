#pragma once

#include "Biemgine.h"

using biemgine::Scene;
using biemgine::StateManager;

namespace spacebiem
{
    class CreditsScene :
        public Scene
    {
    public:
        void input() override;
        void update() override;
        void render(const float deltaTime) override;
        void created() override;

        CreditsScene(StateManager& manager)
            : Scene(manager) {};
        ~CreditsScene() {};
    };
}

