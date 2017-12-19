#pragma once

#include "Biemgine.h"

using biemgine::Scene;
using biemgine::StateManager;

namespace spacebiem
{
    class LevelLoadScene :
        public Scene
    {
    public:
        void input() override;
        void update() override;
        void render(const float deltaTime) override;
        void created() override;

        LevelLoadScene(StateManager& manager)
            : Scene(manager)
        {};
        ~LevelLoadScene() {};

    private:


    };
}

