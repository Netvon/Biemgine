#pragma once

#include "Biemgine.h"
#include "../globals/Difficulty.h"

using biemgine::Scene;
using biemgine::StateManager;

namespace spacebiem
{
    class WinScene :
        public Scene
    {
    public:
        void input() override;
        void update() override;
        void render(const float deltaTime) override;
        void created() override;

        WinScene(StateManager& manager, map<string, int> resources = map<string, int>()) : Scene(manager), resources(resources) {};
        ~WinScene() {};

    private:
        map<string, int> resources;
    };
}

