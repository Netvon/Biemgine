#include "stdafx.h"
#include "ResourceUISystem.h"

namespace spacebiem
{
    void ResourceUISystem::onAddEntity(Entity & entity)
    {
        if (entity.hasComponent("resources"))
        {
            PlayerEntry playerEntry;
            playerEntry.entity = &entity;
            playerEntry.resourceComponent = entity.getComponent<ResourceComponent>("resources");;
            playerEntries.push_back(std::move(playerEntry));

            return;
        }


        if (entity.hasComponent("resourcebonus") && entity.hasComponent("color") && entity.hasComponent("text") && entity.getTag() == "" )
        {
            ResourceTextEntry resourceTextEntry;
            resourceTextEntry.entity = &entity;
            resourceTextEntry.resourceBonusComponent = entity.getComponent<ResourceBonusComponent>("resourcebonus");
            resourceTextEntry.colorComponent = entity.getComponent<ColorComponent>("color");
            resourceTextEntry.textComponent = entity.getComponent<TextComponent>("text");

            resourceTextEntries.push_back(std::move(resourceTextEntry));
        }
    }

    void ResourceUISystem::update()
    {
        if (!playerEntries.empty())
        {
            for (const PlayerEntry& player : playerEntries)
            {
                for (auto& x : player.resourceComponent->getResources())
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
        else
        {
            for (const ResourceTextEntry& resourceTextEntry : resourceTextEntries)
            {
                resourceTextEntry.textComponent->setText(std::to_string(resourceTextEntry.resourceBonusComponent->getAmount()), resourceTextEntry.textComponent->getColor());
            }
        }  
    }
}
