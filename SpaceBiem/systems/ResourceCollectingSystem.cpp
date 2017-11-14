
#include "ResourceCollectingSystem.h"


namespace spacebiem
{
    void ResourceCollectingSystem::before()
    {
    }

    void ResourceCollectingSystem::update(const Entity & entity)
    {

        // player
        if (entity.hasComponent("resources"))
        {

        }

        // resource
        if (entity.hasComponent("resourcebonus"))
        {

        }

        // checken of er contact is
        // tussen resource en player
        // resource verwijderen
        // resources optellen bij player

    }

    void ResourceCollectingSystem::after()
    {
    }

    void ResourceCollectingSystem::onSceneSwitch()
    {
    }
}
