#include "stdafx.h"
#include "..\components\ScoreComponent.h"
#include "..\components\ScoreBonusComponent.h"
#include "ScoreSystem.h"
#include "..\entities\PlanetEntity.h"

using biemgine::GroundedComponent;
using biemgine::CollidableComponent;
using biemgine::TextureComponent;

namespace spacebiem
{
    void ScoreSystem::update(const Entity& entity)
    {
        if (!entity.hasComponent("score")
            || entity.hasComponent("ui")
            || !entity.hasComponent("grounded")) return;

        auto gc = entity.getComponent<GroundedComponent*>("grounded");

        if (gc->isGrounded()) {
            auto ground = gc->getGroundedOn();
            if (!ground->hasComponent("scorebonus")) return;

            auto sbc = ground->getComponent<ScoreBonusComponent*>("scorebonus");
            if (sbc->isScoreGiven()) return;

            auto sc = entity.getComponent<ScoreComponent*>("score");
            sc->addScore(sbc->getScoreBonus());

            sbc->setScoreGiven(true);

            auto components = ground->getComponents<TextureComponent*>("texture");

            for (auto it = components.begin(); it != components.end(); ++it)
            {
                auto component = (*it);
                if (component->getTag() != "flag") continue;

                component->setVisible(true);
            }
        }
    }

    void ScoreSystem::onSceneSwitch()
    {
    }
}
