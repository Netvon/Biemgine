#pragma once

#include "stdafx.h"
#include <vector>
#include <typeindex>

using std::string;
using std::vector;
using std::type_index;

#include "Biemgine.h"

using biemgine::Entity;
using biemgine::TextureComponent;
using biemgine::TextComponent;
using biemgine::EntityManager;

namespace spacebiem
{
    class SaveBlobFactory
    {
    public:
        vector<string> createFromEntities(shared_ptr<EntityManager> entities);
        string createFromEntity(const Entity & entity);

    private:
        TextureComponent & getTextureComponentByTag(const Entity & pEntity, const string & pTag);
        TextComponent & getTextComponentByTag(const Entity & pEntity, const string & pTag);
    };
}
