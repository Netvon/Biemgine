#pragma once

#include "Biemgine.h"

using biemgine::Scene;
using biemgine::StateManager;

namespace spacebiem
{
    class LevelEditorScene :
        public Scene
    {
    public:
        void input() override;
        void update() override;
        void render(const float deltaTime) override;
        void created() override;

        void fillMenuEntitySpace();

        LevelEditorScene(StateManager& manager)
            : Scene(manager)
        {};
        ~LevelEditorScene() {};

    private:


    };
}

