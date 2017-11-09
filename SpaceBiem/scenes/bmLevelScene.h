#pragma once

#include "Biemgine.h"

using biemgine::bmScene;
using biemgine::bmStateManager;

namespace spacebiem
{
    class bmLevelScene :
        public bmScene
    {
    public:
        void input() override;
        void update() override;
        void render(const float deltaTime) override;
        void created() override;
        void sceneEnd() override;

        bmLevelScene(bmStateManager& manager) :
            bmScene(manager) {};

        ~bmLevelScene() {}

    private:
        bool isPauseButtonDown = false;
    };
}
