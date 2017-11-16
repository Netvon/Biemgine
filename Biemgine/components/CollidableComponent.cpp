#include "CollidableComponent.h"

namespace biemgine
{
    bool CollidableComponent::collides(const Entity& entity)
    {
        for (auto &entityId = entityIds.begin(); entityId != entityIds.end(); ++entityId)
        {
            if (*entityId == entity.getId()) return true;
        }

        return false;
    }

    void CollidableComponent::add(const Entity & entity)
    {
        if (collides(entity)) return;

        entityIds.push_back(entity.getId());
    }

    void CollidableComponent::remove(const Entity & entity)
    {
        if (!collides(entity)) return;

        for (auto &entityId = entityIds.begin(); entityId != entityIds.end(); ++entityId)
        {
            if (*entityId == entity.getId()) {
                entityIds.erase(entityId);
                break;
            }
        }
    }
}
