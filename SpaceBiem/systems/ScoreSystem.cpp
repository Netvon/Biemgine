#include "stdafx.h"
#include "..\components\ScoreComponent.h"
#include "..\components\ScoreBonusComponent.h"
#include "ScoreSystem.h"

using biemgine::GroundedComponent;
using biemgine::CollidableComponent;

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

            auto cc = entity.getComponent<CollidableComponent*>("collidable");
            if (cc->visited(*ground)) return;

            auto sc = entity.getComponent<ScoreComponent*>("score");
            auto sbc = ground->getComponent<ScoreBonusComponent*>("scorebonus");

            sc->addScore(sbc->getScoreBonus());
        }
    }

    void ScoreSystem::onSceneSwitch()
    {
    }
}
