#pragma once

#include "Biemgine.h"

using namespace biemgine;

namespace spacebiem
{
    class bmMenuScene :
        public bmScene
    {
    public:
        void input() override;
        void update() override;
        void render(const float deltaTime) override;
        void created() override;

        bmMenuScene(bmStateManager& manager)
            : bmScene(manager) {};

        ~bmMenuScene() {}
    };
}
