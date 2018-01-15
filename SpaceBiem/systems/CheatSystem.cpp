#include <algorithm>

#include "CheatSystem.h"

using biemgine::Color;

namespace spacebiem
{
    void CheatSystem::onAddEntity(Entity & entity)
    {
        if (entity.hasComponent("oxygen") && entity.hasComponent("score") && entity.hasComponent("movement"))
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

            if (entity.getTag() == "godmode")
            {
                auto tc = entity.getComponent<TextComponent>("text");

                CheatTextEntry cheatText;
                cheatText.entity = &entity;
                cheatText.textComponent = tc;

                godModeTextEntry = std::move(cheatText);
            }

            if (entity.getTag() == "ai_bounce")
            {
                auto tc = entity.getComponent<TextComponent>("text");

                CheatTextEntry cheatText;
                cheatText.entity = &entity;
                cheatText.textComponent = tc;

                aibounceTextEntry = std::move(cheatText);
            }
        }
    }

    void CheatSystem::update()
    {
        for (const PlayerEntry& player : playerEntries)
        {
            if (getStateManager()->getInputManager()->isKeyDown("Left Shift")) {
                if (getStateManager()->getInputManager()->isKeyDown("-")) {
                    player.movementComponent->setJumpForce(player.movementComponent->getJumpForce() - 0.1f);
                    cheatTextEntry.textComponent->setText("Jump Force: " + std::to_string(static_cast<int>(player.movementComponent->getJumpForce())), Color{ 255, 255, 255 });
                }

                if (getStateManager()->getInputManager()->isKeyDown("=")) {
                    player.movementComponent->setJumpForce(player.movementComponent->getJumpForce() + 0.1f);
                    cheatTextEntry.textComponent->setText("Jump Force: " + std::to_string(static_cast<int>(player.movementComponent->getJumpForce())), Color{ 255, 255, 255 });
                }

                if (getStateManager()->getInputManager()->isKeyDown(",")) {
                    player.oxygenComponent->setOxygenAmount(player.oxygenComponent->getOxygenAmount() - 10.f);
                    cheatTextEntry.textComponent->setText("Oxygen: " + std::to_string(static_cast<int>(player.oxygenComponent->getOxygenAmount())), Color{ 255, 255, 255 });
                }

                if (getStateManager()->getInputManager()->isKeyDown(".")) {
                    player.oxygenComponent->setOxygenAmount(player.oxygenComponent->getOxygenAmount() + 10.f);
                    cheatTextEntry.textComponent->setText("Oxygen: " + std::to_string(static_cast<int>(player.oxygenComponent->getOxygenAmount())), Color{ 255, 255, 255 });
                }

                if (getStateManager()->getInputManager()->isKeyDown("'")) {
                    player.scoreComponent->setScore(player.scoreComponent->getScore() + 10.f);
                }

                if (getStateManager()->getInputManager()->isKeyDown(";")) {
                    player.scoreComponent->setScore(player.scoreComponent->getScore() - 10.f);
                }

                if (getStateManager()->getInputManager()->isKeyDown("K")) {
                    player.oxygenComponent->setOxygenAmount(0);
                }
            }
            else {
                cheatTextEntry.textComponent->setText("", Color{ 255, 255, 255 });
            }

            if (getStateManager()->getInputManager()->isKeyDown("G")) {
                if (!Cheat::Instance().isEnabled("god")) {
                    godModeTextEntry.textComponent->setText("God mode: ON", Color{ 255, 255, 255 });
                    Cheat::Instance().setEnabled("god", true);
                }
                else {
                    godModeTextEntry.textComponent->setText("", Color{ 255, 255, 255 });
                    Cheat::Instance().setEnabled("god", false);
                }
            }

            if (getStateManager()->getInputManager()->isKeyDown("B")) {
                if (!Cheat::Instance().isEnabled("ai_bounce")) {
                    aibounceTextEntry.textComponent->setText("AI bounce: OFF", Color{ 255, 255, 255 });
                    Cheat::Instance().setEnabled("ai_bounce", true);
                }
                else {
                    aibounceTextEntry.textComponent->setText("", Color{ 255, 255, 255 });
                    Cheat::Instance().setEnabled("ai_bounce", false);
                }
            }
        }
    }
}
