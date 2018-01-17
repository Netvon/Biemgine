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
        struct Entry {
            Entity* entity;
            std::shared_ptr<ScriptComponent> scriptComponent;
        };

        void onAddEntity(Entity & entity);
        void update(const float deltaTime);

    private:
        vector<Entry> entries;
    };
}
