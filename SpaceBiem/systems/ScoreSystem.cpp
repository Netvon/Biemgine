#include "stdafx.h"
#include "..\components\ScoreComponent.h"
#include "..\components\ScoreBonusComponent.h"
#include "ScoreSystem.h"
#include "..\entities\PlanetEntity.h"



namespace spacebiem
{
    void ScoreSystem::onAddEntity(Entity & entity)
    {
        if (!entity.hasComponent("score") || entity.hasComponent("ui") || !entity.hasComponent("grounded")) return;

        PlayerEntry playerEntry;
        playerEntry.entity = &entity;
        playerEntry.positionComponent = entity.getComponent<PositionComponent>("position");
        playerEntry.groundedComponent = entity.getComponent<GroundedComponent>("grounded");
        playerEntry.scoreComponent = entity.getComponent<ScoreComponent>("score");

        playerEntries.push_back(std::move(playerEntry));
    }

    void ScoreSystem::update()
    {
        for (PlayerEntry player : playerEntries)
        {
            if (player.groundedComponent->isGrounded())
            {
                auto ground = player.groundedComponent->getGroundedOn();
                if (!ground->hasComponent("scorebonus")) return;

                auto sbc = ground->getComponent<ScoreBonusComponent>("scorebonus");
                if (sbc->isScoreGiven()) return;

                auto sc = player.scoreComponent;
                sc->addScore(sbc->getScoreBonus());

                sbc->setScoreGiven(true);
                auto texts = ground->getComponents<TextComponent>("text");

                for (auto text : texts)
                {
                    text->setVisible(true);
                }

                auto components = ground->getComponents<TextureComponent>("texture");

                for (auto it = components.begin(); it != components.end(); ++it)
                {
                    auto component = (*it);
                    if (component->getTag() != "flag") continue;
                    if (component->isVisible()) break;

                    auto planetP = ground->getComponent<PositionComponent>("position");

                    component->setOffsetX(player.positionComponent->getX() - planetP->getX());
                    component->setOffsetY(player.positionComponent->getY() - planetP->getY());
                    component->setRotation(player.positionComponent->getRotation());
                    component->setVisible(true);

                    getStateManager()->getAudioDevice().playSoundEffect("audio/flag.mp3");
                }
            }
        }
    }
}
