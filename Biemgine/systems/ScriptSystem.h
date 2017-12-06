#pragma once
#include "System.h"
#include "../entities/Entity.h"
#include "../components/TextComponent.h"
#include "../devices/graphics/GraphicsDevice.h"
#include "../devices/graphics/TextureFlip.h"
#include "../components/ScriptComponent.h"

#include <list>

using std::string;
using std::list;

namespace biemgine
{
    class ScriptSystem
        : public System
    {
    public:
        void update(const Entity& entity, const float deltaTime);
    };
}
