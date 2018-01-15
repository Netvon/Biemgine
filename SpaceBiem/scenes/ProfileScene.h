#pragma once
#include "Biemgine.h"
#include "../entities/PlanetEarthEntity.h"
#include "../entities/PlanetMoonEntity.h"
#include "../entities/ButtonUIEntity.h"
#include "../globals/Player.h"

using biemgine::Scene;
using biemgine::StateManager;
using biemgine::Color;
using biemgine::SpriteEntity;
using biemgine::AnimationComponent;
using biemgine::TextureComponent;
using biemgine::Size;

namespace spacebiem
{
    class ProfileScene
        : public Scene
    {
    public:
        void input() override {};
        void update() override;
        void render(const float deltaTime) override;
        void created() override;

        ProfileScene(StateManager& manager)
            : Scene(manager) {};
        ~ProfileScene() {};
    private:
        bool fadeIn{ true };
    };
}

