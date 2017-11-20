#pragma once

#include "stdafx.h"
#include <vector>

using std::string;
using std::vector;

#include "Biemgine.h"

using biemgine::Entity;

namespace spacebiem
{
    class SaveBlobFactory
    {
    public:
        vector<string> createFromEntities(const vector<Entity*> & entities);
        string createFromEntity(const Entity & entity);
    };
}
