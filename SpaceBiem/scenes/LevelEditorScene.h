#pragma once

#include "Biemgine.h"
#include "../factories/SaveBlobFactory.h"
#include "../factories/NameGenerator.h"

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

        void end() override;

        void fillMenuEntitySpace();

        LevelEditorScene(StateManager& manager, string slotFileName)
            : Scene(manager),
            slotFileName(slotFileName)

        {};
        ~LevelEditorScene() {};

    private:

        string slotFileName;

        NameGenerator nameGenerator;


    };
}
