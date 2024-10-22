#include "stdafx.h"
#include "..\globals\Player.h"
#include "ScoreUISystem.h"

namespace spacebiem
{
    void ScoreUISystem::onAddEntity(Entity & entity)
    {
        if (!entity.hasComponent("score")) return;

        auto sc = entity.getComponent<ScoreComponent>("score");

        if (!entity.hasComponent("ui"))
        {
            PlayerEntry playerEntry;
            playerEntry.entity = &entity;
            playerEntry.scoreComponent = sc;

            playerEntries.push_back(std::move(playerEntry));
        }
        else
        {
            ScoreUIEntry scoreUIEntry;
            scoreUIEntry.entity = &entity;
            scoreUIEntry.scoreComponent = sc;
            scoreUIEntry.textComponent = entity.getComponent<TextComponent>("text");

            scoreUIEntries.push_back(std::move(scoreUIEntry));
        }
    }

    void ScoreUISystem::update()
    {
        if (playerEntries.empty())
        {
            for (const ScoreUIEntry& score : scoreUIEntries)
            {
               
                string name = Player::current().getName();

                Color highlightColor{255, 255, 255};

                if (name == score.scoreComponent->getName())
                {
                    highlightColor = {232, 228, 41};
                }

                score.textComponent->setText(score.scoreComponent->getName() + ": " + std::to_string((int)score.scoreComponent->getScore()), highlightColor);
            }
        }
        else
        {
            for (const PlayerEntry& player : playerEntries)
            {
                for (const ScoreUIEntry& score : scoreUIEntries)
                {
                    score.textComponent->setText(player.scoreComponent->getName() + ": " + std::to_string((int)player.scoreComponent->getScore()), {255, 255, 255});
                }
            }
        }
    }
}
