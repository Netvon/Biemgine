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
        void sceneEnd() override;

        HelpScene(StateManager& manager, bool fromLevel = false, int slide = 1)
            : Scene(manager),
            fromLevel(fromLevel),
            currentSlide(slide)
        {};
        ~HelpScene() {};

    private:
        bool fromLevel;
        int currentSlide;
        int maxSlides = 9;

    };
}

