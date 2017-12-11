#pragma once

#include "Biemgine.h"

using biemgine::Entity;
using biemgine::Color;

namespace spacebiem
{
    class AIEntity :
        public Entity
    {
    public:
        AIEntity(float x, float y, Color color, float w = -1, float h = -1, float mass = 1.0f, const std::string animatedTexture = "textures/PlayerSpriteSheet.png", size_t textureCount = 9llu);
    };
}