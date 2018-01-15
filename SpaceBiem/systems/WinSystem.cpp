#include <algorithm>

#include "WinSystem.h"
#include "../scenes/StoryScene.h"

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

        if (entity.hasComponent("resourcebonus") && entity.hasComponent("color") && entity.hasComponent("text") && entity.getTag() == "resource-needed")
        {
            ResourceTextEntry resourceTextEntry;
            resourceTextEntry.entity = &entity;
            resourceTextEntry.resourceBonusComponent = entity.getComponent<ResourceBonusComponent>("resourcebonus");
            resourceTextEntry.colorComponent = entity.getComponent<ColorComponent>("color");
            resourceTextEntry.textComponent = entity.getComponent<TextComponent>("text");

            resourceTextEntries.push_back(std::move(resourceTextEntry));
        }
    }

    void WinSystem::update()
    {
        for (const PlayerEntry& player : playerEntries)
        {
            if (player.groundedComponent->isGrounded())
            {
                auto ground = player.groundedComponent->getGroundedOn();
                if (ground->getTag() == "wormhole")
                {
                    auto resources = player.resourceComponent->getAllResources();
                    auto neededResources = player.resourceComponent->getNeededResources();

                    int metal = resources["metal"] - winConditions[difficulty]["metal"];
                    int diamond = resources["diamond"] - winConditions[difficulty]["diamond"];
                    int uranium = resources["uranium"] - winConditions[difficulty]["uranium"];
                    int antimatter = resources["anti-matter"] - winConditions[difficulty]["anti-matter"];

                    neededResources["metal"] = metal;
                    neededResources["diamond"] = diamond;
                    neededResources["uranium"] = uranium;
                    neededResources["anti-matter"] = antimatter;

                    if (metal >= 0 && diamond >= 0 && uranium >= 0 && antimatter >= 0)
                    {
                        Difficulty diff = static_cast<Difficulty>(static_cast<int>(difficulty) + 1);
                        getStateManager()->navigateTo<StoryScene>(diff);
                    }
                    else
                    {
                        for (auto& x : neededResources)
                        {
                            for (ResourceTextEntry resourceTextEntry : resourceTextEntries)
                            {
                                if (x.first == resourceTextEntry.resourceBonusComponent->getName())
                                {
                                    resourceTextEntry.textComponent->setText(std::to_string(x.second), resourceTextEntry.textComponent->getColor());
                                }
                            }
                        } 
                    }
                }
            }
        }
    }
}
