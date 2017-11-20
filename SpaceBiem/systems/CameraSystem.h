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
        ~CameraSystem() {};

        void update(const Entity& entity) override;

    private:
        Camera* camera = nullptr;
    };
}
