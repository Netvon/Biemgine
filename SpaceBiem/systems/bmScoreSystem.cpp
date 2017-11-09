#include "stdafx.h"
#include "..\components\bmScoreComponent.h"
#include "bmScoreSystem.h"

namespace spacebiem
{
    bmScoreSystem::bmScoreSystem()
    {
    }

    bmScoreSystem::~bmScoreSystem()
    {
    }

    void bmScoreSystem::update(const bmEntity& entity)
    {
        if (!entity.hasComponent("score")) return;
        if (entity.hasComponent("ui")) return;
        auto sc = entity.getComponent<bmScoreComponent*>("score");

        sc->addScore(bmLoop::BM_GAMELOOP_UPDATE_MS / 100);
    }

    void bmScoreSystem::onSceneSwitch()
    {
    }
}
