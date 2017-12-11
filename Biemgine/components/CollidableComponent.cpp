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

    void CollidableComponent::add(const Entity & pEntity)
    {
        collisions.push_back(createCollideInfo(&pEntity, false));
    }

    void CollidableComponent::remove(const Entity & pEntity)
    {
        auto iterator = std::find_if(collisions.begin(), collisions.end(), [pEntity](const CollideInfo & pCollideInfo) {
            return pCollideInfo.entity->getId() == pEntity.getId();
        });

        collisions.erase(iterator);
    }

    vector<CollideInfo>& CollidableComponent::getCollisions()
    {
        return collisions;
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
