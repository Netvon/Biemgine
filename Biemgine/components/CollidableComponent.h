#pragma once

#include "dlldef.h"
#include "stdafx.h"
#include <vector>

#include "Component.h"
#include "..\entities\Entity.h"

namespace biemgine
{
    class BIEMGINE CollidableComponent
        : public Component
    {
    public:
        bool collides(const Entity& entity);
        void add(const Entity& entity);
        void remove(const Entity& entity);

    private:
        vector<int> entityIds;
    };
}
