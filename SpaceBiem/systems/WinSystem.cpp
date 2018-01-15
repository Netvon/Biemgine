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
        bool resourceCheck = false;

        for (const PlayerEntry& player : playerEntries)
        {
            bool win = false;

            if (player.groundedComponent->isGrounded())
            {
                auto resources = player.resourceComponent->getAllResources();

                int metal = resources["metal"] - winConditions[difficulty]["metal"];
                int diamond = resources["diamond"] - winConditions[difficulty]["diamond"];
                int uranium = resources["uranium"] - winConditions[difficulty]["uranium"];
                int antimatter = resources["anti-matter"] - winConditions[difficulty]["anti-matter"];


                cout <<  difficulty << endl;

                cout << "Metal: " + std::to_string(metal) + " Diamond: " + std::to_string(diamond) + " Uranium: " + std::to_string(uranium) + " Anti-Matter: " + std::to_string(antimatter) << endl;

                if (metal >= 0 && diamond >= 0 && uranium >= 0 && antimatter >= 0) {
                    win = true;
                }

                auto ground = player.groundedComponent->getGroundedOn();
                if (ground->getTag() == "wormhole" && resourceCheck) win = true;
            }
        }
    }
}
