#include "CollidableComponent.h"

namespace biemgine
{
    bool CollidableComponent::collides(const Entity & entity) const
    {
        bool collision = collisions.find(entity.getId()) != collisions.end();

        return collision && &collision != false;
    }

    void CollidableComponent::add(const Entity & entity)
    {
        collisions.insert_or_assign(entity.getId(), true);
    }

    void CollidableComponent::remove(const Entity & entity)
    {
        collisions.insert_or_assign(entity.getId(), false);
    }

    bool CollidableComponent::visited(const Entity & entity) const
    {
        return collisions.find(entity.getId()) != collisions.end();
    }

    map<int, bool>& CollidableComponent::getCollisions()
    {
        return collisions;
    }
}
