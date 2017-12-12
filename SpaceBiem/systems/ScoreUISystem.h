#pragma once

#include "Biemgine.h"
#include "..\components\ScoreComponent.h"

using biemgine::GraphicsDevice;
using biemgine::System;
using biemgine::Entity;

namespace spacebiem
{
    class ScoreUISystem : public System
    {
    public:
        ~ScoreUISystem() {};

        void update(const Entity& entity) override;

    private:
        std::map<std::shared_ptr<ScoreComponent>, bool> scoreMap;
    };
}
