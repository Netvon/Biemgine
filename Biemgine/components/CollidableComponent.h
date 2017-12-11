#pragma once

#include "dlldef.h"
#include "stdafx.h"
#include <map>

#include "Component.h"
#include "..\entities\Entity.h"

using std::map;

enum CollisionCategory
{
    NONE = 0x0001,
    PLANET = 0x0002,
    PLAYER = 0x0004,
    AI = 0x0008,
    RESOURCE = 0x0010
};

namespace biemgine
{
    struct CollideInfo
    {
        const Entity * entity;
        bool colliding = false;
    };

    class BIEMGINE CollidableComponent
        : public Component
    {
    public:
        CollidableComponent(int pCategoryBits = CollisionCategory::NONE, int pMaskBits = CollisionCategory::NONE);

        bool collides(const Entity & entity) const;
        void add(const Entity & entity);
        void remove(const Entity & entity);

        vector<CollideInfo>& getCollisions();

        int getCategoryBits() const;
        int getMaskBits() const;

    private:
        vector<CollideInfo> collisions;

        int categoryBits = CollisionCategory::NONE;
        int maskBits = CollisionCategory::NONE;

        CollideInfo createCollideInfo(const Entity * entity, bool colliding = false) const;
    };
}
