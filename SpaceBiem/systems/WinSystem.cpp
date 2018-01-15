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

        if (entity.isTag("resource-needed-background"))
        {
            ResourceTextureEntry resourceTextureEntry;
            resourceTextureEntry.entity = &entity;

            resourceTextureEntries.push_back(std::move(resourceTextureEntry));
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
                    auto resources = player.resourceComponent->getResources();
                    auto allResources = player.resourceComponent->getAllResources();
                    auto neededResources = player.resourceComponent->getNeededResources();

                    int metal = winConditions[difficulty]["metal"] - (resources["metal"] + allResources["metal"]);
                    int diamond = winConditions[difficulty]["diamond"] - (resources["diamond"] + allResources["diamond"]);
                    int uranium = winConditions[difficulty]["uranium"] - (resources["uranium"] + allResources["uranium"]);
                    int antimatter = winConditions[difficulty]["anti-matter"] - (resources["anti-matter"] + allResources["anti-matter"]);

                    neededResources["metal"] = metal < 0 ? 0 : metal;
                    neededResources["diamond"] = diamond < 0 ? 0 : diamond;
                    neededResources["uranium"] = uranium < 0 ? 0 : uranium;
                    neededResources["anti-matter"] = antimatter < 0 ? 0 : antimatter;

                    if (metal == 0 && diamond == 0 && uranium == 0 && antimatter == 0)
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
                                    resourceTextEntry.entity->rise();
                                    resourceTextEntry.textComponent->setText(std::to_string(x.second), resourceTextEntry.textComponent->getColor());
                                }
                            }
                        }

                        for (ResourceTextureEntry resourceTextureEntry : resourceTextureEntries)
                        {
                            resourceTextureEntry.entity->rise();
                        }
                    }

                    return;
                }
            }

            for (ResourceTextEntry resourceTextEntry : resourceTextEntries)
            {
                resourceTextEntry.entity->die();
            }

            for (ResourceTextureEntry resourceTextureEntry : resourceTextureEntries)
            {
                resourceTextureEntry.entity->die();
            }
        }
    }
}
