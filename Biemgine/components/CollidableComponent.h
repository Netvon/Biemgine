#pragma once

#include "dlldef.h"
#include "stdafx.h"
#include <map>

#include "Component.h"
#include "..\entities\Entity.h"

using std::map;

namespace biemgine
{
    class BIEMGINE CollidableComponent
        : public Component
    {
    public:
        bool collides(const Entity & entity) const;
        void add(const Entity & entity);
        void remove(const Entity & entity);

        bool visited(const Entity & entity) const;
        map<int, bool>& getCollisions();

    private:
        map<int, bool> collisions;
    };
}
