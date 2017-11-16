#include "stdafx.h"
#include "..\components\ScoreComponent.h"
#include "..\components\ScoreBonusComponent.h"
#include "ScoreSystem.h"

using biemgine::GroundedComponent;

namespace spacebiem
{
    ScoreSystem::ScoreSystem()
    {
    }

    ScoreSystem::~ScoreSystem()
    {
    }

    void ScoreSystem::update(const Entity& entity)
    {
        if (!entity.hasComponent("score")
            || entity.hasComponent("ui")
            || !entity.hasComponent("grounded")) return;

        auto gc = entity.getComponent<GroundedComponent*>("grounded");

        if (gc->isGrounded()) {
            auto sc = entity.getComponent<ScoreComponent*>("score");

            auto ground = gc->getGroundedOn();
            if (!ground->hasComponent("scorebonus")) return;

            auto sbc = ground->getComponent<ScoreBonusComponent*>("scorebonus");

            sc->addScore(sbc->getScoreBonus());
        }
    }

    void ScoreSystem::onSceneSwitch()
    {
    }
}
