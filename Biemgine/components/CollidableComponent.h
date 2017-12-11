#pragma once

#include "dlldef.h"
#include "stdafx.h"
#include <map>

#include "Component.h"
#include "..\entities\Entity.h"

using std::map;

enum CollisionType
{
    NONE = 0x0001,
    BOUNDRY = 0x0002,
    PLANET = 0x0004,
    PLAYER = 0x0008,
    AI = 0x0010,
    RESOURCE = 0x0020
};

namespace biemgine
{
    class BIEMGINE CollidableComponent
        : public Component
    {
    public:
        CollidableComponent() {};
        CollidableComponent(int pCategoryBits, int pMaskBits = CollisionType::NONE);

        bool collides(const Entity & entity) const;
        void add(const Entity & entity);
        void remove(const Entity & entity);

        bool visited(const Entity & entity) const;
        map<int, bool>& getCollisions();

        int getCategoryBits() const;
        int getMaskBits() const;

    private:
        map<int, bool> collisions;

        int categoryBits = CollisionType::NONE;
        int maskBits = CollisionType::NONE;
    };
}
