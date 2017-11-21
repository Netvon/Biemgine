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

namespace spacebiem
{
    class SaveBlobFactory
    {
    public:
        vector<string> createFromEntities(const vector<Entity*> & entities);
        string createFromEntity(const Entity & entity);

    private:
        TextureComponent& getTextureComponentByTag(const Entity & pEntity, const string & pTag);
    };
}
