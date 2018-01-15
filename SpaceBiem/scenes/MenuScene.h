#pragma once

#include "Biemgine.h"

using biemgine::Scene;
using biemgine::StateManager;

namespace spacebiem
{
    class MenuScene :
        public Scene
    {
    public:
        void input() override;
        void update() override;
        void render(const float deltaTime) override;
        void created() override;

        MenuScene(StateManager& manager, bool pFadeIn = false)
            : Scene(manager), fadeIn(pFadeIn) {};

        ~MenuScene() {}

    private:
        bool fadeIn;
    };
}
