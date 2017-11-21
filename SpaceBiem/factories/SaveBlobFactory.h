#pragma once

#include "stdafx.h"
#include <vector>
#include <typeindex>

using std::string;
using std::vector;
using std::type_index;

#include "Biemgine.h"

using biemgine::Entity;

namespace spacebiem
{
    class SaveBlobFactory
    {
    public:
        vector<string> createFromEntities(vector<const Entity *> & entities);
        string createFromEntity(const Entity & entity);
    };
}
