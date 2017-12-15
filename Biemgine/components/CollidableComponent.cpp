#include "CollidableComponent.h"

using biemgine::CollideInfo;

#include <algorithm>

namespace biemgine
{
    CollidableComponent::CollidableComponent(int pCategoryBits, int pMaskBits) :
        categoryBits(pCategoryBits), maskBits(pMaskBits) {}

    bool CollidableComponent::collides(const Entity & pEntity) const
    {
        auto iterator = std::find_if(collisions.begin(), collisions.end(), [pEntity](const CollideInfo & pCollideInfo) {
            return pCollideInfo.entity->getId() == pEntity.getId();
        });

        if (iterator == collisions.end()) return false;

        auto collideInfo = *iterator;
        return collideInfo.colliding;
    }

    void CollidableComponent::add(const Entity & pEntity, bool colliding)
    {
        auto it = std::find_if(collisions.begin(), collisions.end(), [pEntity](const CollideInfo & pCollideInfo) {
            return pCollideInfo.entity->getId() == pEntity.getId();
        });

        if (it != collisions.end()) (*it).colliding = colliding;
        else collisions.push_back(createCollideInfo(&pEntity, colliding));

    }

    void CollidableComponent::remove(const Entity & pEntity)
    {
        auto iterator = std::find_if(collisions.begin(), collisions.end(), [pEntity](const CollideInfo & pCollideInfo) {
            return pCollideInfo.entity->getId() == pEntity.getId();
        });

        if (iterator != collisions.end()) {
            (*iterator).colliding = false;
        }
    }

    vector<CollideInfo> CollidableComponent::getCollisions()
    {
        vector<CollideInfo> coll{};

        for (CollideInfo i : collisions) {
            if (i.colliding) coll.push_back(i);
        }

        return std::move(coll);
    }
    vector<CollideInfo> CollidableComponent::getAllCollisions()
    {
        return std::move(collisions);
    }

    int CollidableComponent::getCategoryBits() const
    {
        return categoryBits;
    }

    int CollidableComponent::getMaskBits() const
    {
        return maskBits;
    }

    CollideInfo CollidableComponent::createCollideInfo(const Entity * pEntity, bool pColliding) const
    {
        CollideInfo collideInfo{};
        collideInfo.entity = pEntity;
        collideInfo.colliding = pColliding;

        return collideInfo;
    }
}
