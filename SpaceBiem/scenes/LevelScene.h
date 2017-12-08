#pragma once

#include "Biemgine.h"
#include "../globals/Difficulty.h"

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

        LevelScene(StateManager& manager, bool newGame = true, Difficulty difficulty = Difficulty::NORMAL) :
            Scene(manager),
            newGame(newGame),
            difficulty(difficulty)
        {};

        ~LevelScene() {}

    private:
        bool isPauseButtonDown = false;
        bool isPaused = false;
        bool newGame;
        int FPSId;
        float timeout;
        int counter = 0;
        int totalDeltaTime = 0;

        void updateMenu();

        Difficulty difficulty;
    };
}
