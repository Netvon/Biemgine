#include <algorithm>

#include "WinSystem.h"

using biemgine::FileHandler;

namespace spacebiem
{
    void WinSystem::onAddEntity(Entity & entity)
    {
        if (!entity.hasComponent("ui") && entity.hasComponent("oxygen") && entity.hasComponent("score") && entity.hasComponent("resources") && entity.hasComponent("collidable") && entity.hasComponent("grounded"))
        {
            auto pc = entity.getComponent<PositionComponent>("position");
            auto gc = entity.getComponent<GroundedComponent>("grounded");
            auto rc = entity.getComponent<ResourceComponent>("resources");
            auto cc = entity.getComponent<CollidableComponent>("collidable");

            PlayerEntry playerEntry;
            playerEntry.entity = &entity;
            playerEntry.positionComponent = pc;
            playerEntry.groundedComponent = gc;
            playerEntry.resourceComponent = rc;
            playerEntry.collidableComponent = cc;

            playerEntries.push_back(std::move(playerEntry));
        }
    }

    void WinSystem::update()
    {
        for (const PlayerEntry& player : playerEntries)
        {
            bool win = false;

            if (player.groundedComponent->isGrounded())
            {
                auto ground = player.groundedComponent->getGroundedOn();
                if (ground->getTag() == "wormhole") win = true;
            }
        }
    }
}
