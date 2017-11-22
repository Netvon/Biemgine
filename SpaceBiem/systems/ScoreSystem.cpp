#include "stdafx.h"
#include "..\components\ScoreComponent.h"
#include "..\components\ScoreBonusComponent.h"
#include "ScoreSystem.h"
#include "..\entities\PlanetEntity.h"

using biemgine::GroundedComponent;
using biemgine::CollidableComponent;
using biemgine::TextureComponent;
using biemgine::TextComponent;
using biemgine::PositionComponent;

namespace spacebiem
{
    void ScoreSystem::update(const Entity& entity)
    {
        if (!entity.hasComponent("score")
            || entity.hasComponent("ui")
            || !entity.hasComponent("grounded")) return;

        auto gc = entity.getComponent<GroundedComponent>("grounded");
        auto pc = entity.getComponent<PositionComponent>("position");

        if (gc->isGrounded()) {
            auto ground = gc->getGroundedOn();
            if (!ground->hasComponent("scorebonus")) return;

            auto sbc = ground->getComponent<ScoreBonusComponent>("scorebonus");
            if (sbc->isScoreGiven()) return;

            auto sc = entity.getComponent<ScoreComponent>("score");
            sc->addScore(sbc->getScoreBonus());

            sbc->setScoreGiven(true);
            auto texts = ground->getComponents<TextComponent>("text");
            for (auto text : texts) {
                text->setVisible(true);
            }


            auto components = ground->getComponents<TextureComponent>("texture");

            for (auto it = components.begin(); it != components.end(); ++it)
            {
                auto component = (*it);
                if (component->getTag() != "flag") continue;

                auto planetP = ground->getComponent<PositionComponent>("position");

                component->setOffsetX(pc->getX() - planetP->getX());
                component->setOffsetY(pc->getY() - planetP->getY());
                component->setRotation(pc->getRotation());
                component->setVisible(true);
            }
        }
    }
}
