#pragma once

#include "Biemgine.h"

using biemgine::Scene;
using biemgine::StateManager;

namespace spacebiem
{
    class HelpScene :
        public Scene
    {
    public:
        void input() override;
        void update() override;
        void render(const float deltaTime) override;
        void created() override;

        HelpScene(StateManager& manager, bool fromLevel = false, int slide = 1)
            : Scene(manager),
            fromLevel(fromLevel)
        {};
        ~HelpScene() {};

    private:
        bool fromLevel;
        int currentSlide;
        int maxSlides = 9;

        void updateSlide();

    };
}

