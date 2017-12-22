#include <algorithm>

#include "CheatSystem.h"

using biemgine::Color;

namespace spacebiem
{
    void CheatSystem::onAddEntity(Entity & entity)
    {
        if (entity.hasComponent("oxygen") && entity.hasComponent("score"))
        {
            auto oc = entity.getComponent<OxygenComponent>("oxygen");
            auto sc = entity.getComponent<ScoreComponent>("score");
            auto mc = entity.getComponent<MovementComponent>("movement");

            PlayerEntry playerEntry;
            playerEntry.entity = &entity;
            playerEntry.oxygenComponent = oc;
            playerEntry.scoreComponent = sc;
            playerEntry.movementComponent = mc;

            playerEntries.push_back(std::move(playerEntry));
        }

        if (entity.hasComponent("text"))
        {
            if (entity.getTag() == "cheat")
            {
                auto tc = entity.getComponent<TextComponent>("text");

                CheatTextEntry cheatText;
                cheatText.entity = &entity;
                cheatText.textComponent = tc;

                cheatTextEntry = std::move(cheatText);
            }
        }
    }

    void CheatSystem::update()
    {
        for (const PlayerEntry& player : playerEntries)
        {
            if (getStateManager()->getInputManager()->isKeyDown("Left Shift")) {
                if (getStateManager()->getInputManager()->isKeyDown("=")) {
                    player.scoreComponent->setScore(player.scoreComponent->getScore() + 10.f);
                }
                if (getStateManager()->getInputManager()->isKeyDown("-")) {
                    player.scoreComponent->setScore(player.scoreComponent->getScore() - 10.f);
                }

                if (getStateManager()->getInputManager()->isKeyDown("K")) {
                    player.oxygenComponent->setOxygenAmount(0);
                }
            }

            if (getStateManager()->getInputManager()->isKeyDown("=")) {
                player.movementComponent->setJumpForce(player.movementComponent->getJumpForce() + 0.1f);
            }

            if (getStateManager()->getInputManager()->isKeyDown("-")) {
                player.movementComponent->setJumpForce(player.movementComponent->getJumpForce() - 0.1f);
            }

            if (getStateManager()->getInputManager()->isKeyDown(",")) {
                player.oxygenComponent->setOxygenAmount(player.oxygenComponent->getOxygenAmount() - 10.f);
            }

            if (getStateManager()->getInputManager()->isKeyDown(".")) {
                player.oxygenComponent->setOxygenAmount(player.oxygenComponent->getOxygenAmount() + 10.f);
            }

            if (getStateManager()->getInputManager()->isKeyDown("G")) {
                if (!player.oxygenComponent->getIsGod()) {
                    cheatTextEntry.textComponent->setText("HOI", Color{ 255, 255, 255 });
                    player.oxygenComponent->setIsGod(true);
                }
                else {
                    player.oxygenComponent->setIsGod(false);
                }
            }
        }
    }
}
