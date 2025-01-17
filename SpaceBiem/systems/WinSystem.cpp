#include <algorithm>

#include "WinSystem.h"
#include "../scenes/StoryScene.h"
#include "../scenes/WinScene.h"

using biemgine::FileHandler;
using biemgine::Color;

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

                    if (metal <= 0 && diamond <= 0 && uranium <= 0 && antimatter <= 0)
                    {
                        FileHandler fileHandler{ "" };
                        fileHandler.remove(Player::current().saveLocation());

                        Difficulty diff = static_cast<Difficulty>(static_cast<int>(difficulty) + 1);

                        FileParser fp;
                        map<Difficulty, bool> progress = fp.progressContent();
                        progress[diff] = true;
                        fp.writeProgress(progress);

                        getStateManager()->navigateTo<StoryScene>(diff, true);
                        if (diff == Difficulty::DONE)
                        {
                            getStateManager()->navigateTo<WinScene>(resources);
                        }
                        else
                        {
                            getStateManager()->navigateTo<StoryScene>(diff, true, resources);
                        }                    
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
                                    Color color = Color{ 0, 255, 0, 255 };
                                    if (x.second > 0)
                                    {
                                        color = Color{ 255, 255, 255, 255 };
                                    }

                                    resourceTextEntry.textComponent->setText(std::to_string(x.second), color);
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
