#pragma once

#include "Biemgine.h"

using biemgine::SpriteEntity;
using biemgine::Scene;
using biemgine::StateManager;

namespace spacebiem
{
    class LevelScene :
        public Scene
    {
    public:
        void input() override;
        void update() override;
        void render(const float deltaTime) override;
        void created() override;
        void sceneEnd() override;
        void resetFPScounters();

        LevelScene(StateManager& manager, bool newGame = true) :
            Scene(manager),
            newGame(newGame){};

        ~LevelScene() {}

    private:
        bool isPauseButtonDown = false;
        bool newGame;
        int FPSId;
        float timeout;
        int counter = 0;
        int totalDeltaTime = 0;
    };
}
