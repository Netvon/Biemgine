#include "stdafx.h"
#include "..\components\ScoreComponent.h"
#include "ScoreSystem.h"

using biemgine::Loop;

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
        if (!entity.hasComponent("score")) return;
        if (entity.hasComponent("ui")) return;
        auto sc = entity.getComponent<ScoreComponent*>("score");

        //sc->addScore(Loop::BM_GAMELOOP_UPDATE_MS / 100);
    }

    void ScoreSystem::onSceneSwitch()
    {
    }
}
