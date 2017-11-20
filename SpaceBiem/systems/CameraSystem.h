#pragma once

#include "Biemgine.h"
#include "..\Camera.h"

using biemgine::System;
using biemgine::GraphicsDevice;
using biemgine::Entity;
using std::map;

namespace spacebiem
{
    class CameraSystem
        : public System
    {
    public:

        CameraSystem() {};
        ~CameraSystem() {};

        void before(const float deltaTime) override;
        void update(const Entity& entity, const float deltaTime) override;
        void after(const float deltaTime) override;

        void onSceneSwitch() override;

    private:
        Camera* camera = nullptr;
    };
}
